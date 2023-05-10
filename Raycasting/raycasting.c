/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:45:54 by ale-sain          #+#    #+#             */
/*   Updated: 2023/05/10 17:48:05 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "new.h"

/*looking down then up then horizontally*/
void	spawn_horiz(t_game *game, t_raycast *rc)
{
	rc->rayH.point.x = game->player_pos.x;
	rc->rayH.point.y = game->player_pos.y;
	rc->dda.aTan = (float)-1 / tan(rc->dda.rot_angle);
	if (rc->dda.rot_angle < PI)
	{
		rc->dda.ray.y = (((int)game->player_pos.y / SIZE) * SIZE) - 0.0001;
		rc->dda.ray.x = (game->player_pos.y - rc->dda.ray.y) * rc->dda.aTan
			+ game->player_pos.x;
		rc->dda.pas.y = -SIZE;
		rc->dda.pas.x = -rc->dda.pas.y * rc->dda.aTan;
	}
	if (rc->dda.rot_angle > PI)
	{
		rc->dda.ray.y = (((int)game->player_pos.y / SIZE) * SIZE) + SIZE;
		rc->dda.ray.x = (game->player_pos.y - rc->dda.ray.y) * rc->dda.aTan
			+ game->player_pos.x;
		rc->dda.pas.y = SIZE;
		rc->dda.pas.x = -rc->dda.pas.y * rc->dda.aTan;
	}
	if (rc->dda.rot_angle < 0 || rc->dda.rot_angle == PI)
	{
		rc->dda.ray.x = game->player_pos.x;
		rc->dda.ray.y = game->player_pos.y;
		rc->dof = game->map.height;
	}
}

void	dda_horiz(t_game *game, t_raycast *rc)
{
	while (rc->dof < game->map.height)
	{
		rc->map.x = (int)rc->dda.ray.x / SIZE;
		rc->map.y = (int)rc->dda.ray.y / SIZE;
		if (rc->map.x >= 0 && rc->map.y >= 0 && rc->map.x < game->map.length
			&& rc->map.y < game->map.height
			&& game->tab[rc->map.y][rc->map.x] == '1')
		{
			rc->rayH.point.x = rc->dda.ray.x;
			rc->rayH.point.y = rc->dda.ray.y;
			rc->rayH.dis = shorter_dist(game->player_pos.x, game->player_pos.y,
					rc->rayH.point.x, rc->rayH.point.y);
			rc->dof = game->map.height;
		}
		else
		{
			rc->dda.ray.x += rc->dda.pas.x;
			rc->dda.ray.y += rc->dda.pas.y;
			rc->dof += 1;
		}
	}
}

/*looking right, then looking left*/
void	spawn_vert(t_game *game, t_raycast *rc)
{
	rc->rayV.point.x = game->player_pos.x;
	rc->rayV.point.y = game->player_pos.y;
	rc->dda.nTan = -tan(rc->dda.rot_angle);
	if (rc->dda.rot_angle < P2 || rc->dda.rot_angle > P3)
	{
		rc->dda.ray.x = (((int)game->player_pos.x / SIZE) * SIZE) - 0.0001;
		rc->dda.ray.y = (game->player_pos.x - rc->dda.ray.x) * rc->dda.nTan
			+ game->player_pos.y;
		rc->dda.pas.x = -SIZE;
		rc->dda.pas.y = -rc->dda.pas.x * rc->dda.nTan;
	}
	if (rc->dda.rot_angle > P2 && rc->dda.rot_angle < P3)
	{
		rc->dda.ray.x = (((int)game->player_pos.x / SIZE) * SIZE) + SIZE;
		rc->dda.ray.y = (game->player_pos.x - rc->dda.ray.x) * rc->dda.nTan
			+ game->player_pos.y;
		rc->dda.pas.x = SIZE;
		rc->dda.pas.y = -rc->dda.pas.x * rc->dda.nTan;
	}
}

void	dda_vert(t_game *game, t_raycast *rc)
{
	while (rc->dof < game->map.length)
	{
		rc->map.x = (int)rc->dda.ray.x / SIZE;
		rc->map.y = (int)rc->dda.ray.y / SIZE;
		if (rc->map.x >= 0 && rc->map.y >= 0 && rc->map.x < game->map.length
			&& rc->map.y < game->map.height
			&& game->tab[rc->map.y][rc->map.x] == '1')
		{
			rc->rayV.point.x = rc->dda.ray.x;
			rc->rayV.point.y = rc->dda.ray.y;
			rc->rayV.dis = shorter_dist(game->player_pos.x, game->player_pos.y,
					rc->rayV.point.x, rc->rayV.point.y);
			rc->dof = game->map.length;
		}
		else
		{
			rc->dda.ray.x += rc->dda.pas.x;
			rc->dda.ray.y += rc->dda.pas.y;
			rc->dof += 1;
		}
	}
}

/*Spawn horizontal rays, then verticals, then choose the shorter,
	then draw the pixel columns*/
void	raycasting(t_game *game)
{
	t_raycast	rc;

	rc.dda.rot_angle = game->pa - (DR16 * 480);
	rc.ray = 0;
	while (rc.ray < 960)
	{
		if (rc.dda.rot_angle < 0)
			rc.dda.rot_angle += 2 * PI;
		else if (rc.dda.rot_angle > 2 * PI)
			rc.dda.rot_angle -= 2 * PI;
		rc.dof = 0;
		rc.rayH.dis = 1000000;
		spawn_horiz(game, &rc);
		dda_horiz(game, &rc);
		rc.dof = 0;
		rc.rayV.dis = 1000000;
		spawn_vert(game, &rc);
		dda_vert(game, &rc);
		shorter_ray(&rc);
		draw_3d(game, &rc);
		bresenham(game->img, game->player_pos, rc.draw.next, 0x000000FF);
		rc.ray++;
		rc.dda.rot_angle += DR16;
	}
}
