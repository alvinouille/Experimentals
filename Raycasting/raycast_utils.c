/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:17:22 by ale-sain          #+#    #+#             */
/*   Updated: 2023/05/13 18:30:00 by alvina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "new.h"

void	ray_init(t_game *game, t_raycast *rc, int ray)
{
	rc->dof = 0;
	if (ray == VERTICAL)
	{
		rc->rayV.dis = 1000000;
		rc->rayV.point.x = game->player_pos.x;
		rc->rayV.point.y = game->player_pos.y;
		rc->dda.nTan = -tan(rc->dda.rot_angle);
	}
	else
	{
		rc->rayH.dis = 1000000;
		rc->rayH.point.x = game->player_pos.x;
		rc->rayH.point.y = game->player_pos.y;
		rc->dda.aTan = (float)-1 / tan(rc->dda.rot_angle);
	}
}

int	deter_tox(t_game *game, t_raycast *rc)
{
	if (rc->draw.orient == VERTICAL)
	{
		if (rc->draw.v_facing == RIGHTT)
			game->curr_txt = game->texture[0].tab;
		else
			game->curr_txt = game->texture[1].tab;
		return ((int)rc->dda.ray.y % SIZE);
	}
	else
	{
		if (rc->draw.h_facing == UP)
			game->curr_txt = game->texture[2].tab;
		else
			game->curr_txt = game->texture[3].tab;
		return ((int)rc->dda.ray.x % SIZE);
	}
}

void	build_wall(t_game *game, t_moh2i start, t_moh2i end, t_raycast *rc)
{
	int	y;
	int	dft;
	int	toy;
	int	tox;

	tox = deter_tox(game, rc);
	y = start.y;
	while (y < end.y)
	{
		dft = y + (((int)round((SIZE * W_HEIGHT) / rc->disT)) / 2)
			- round(W_HEIGHT / 2);
		toy = dft * (SIZE / ((float)round((SIZE * W_HEIGHT) / rc->disT)));
		if (toy > SIZE - 1)
			toy = SIZE - 1;
		if (toy < 0)
			toy = 0;
		rc->draw.color = game->curr_txt[toy * SIZE + tox];
		img_pixel_put((&game->img), start.x, y, rc->draw.color);
		y++;
	}
}

void	draw_3d(t_game *game, t_raycast *rc)
{
	rc->draw.ca = game->pa - rc->dda.rot_angle;
	if (rc->draw.ca < 0)
		rc->draw.ca += 2 * PI;
	else if (rc->draw.ca > 2 * PI)
		rc->draw.ca -= 2 * PI;
	rc->disT = rc->disT * cos(rc->draw.ca);
	rc->draw.lineH = round((SIZE * W_HEIGHT) / rc->disT);
	if (rc->draw.lineH > W_HEIGHT)
		rc->draw.lineH = W_HEIGHT;
	rc->draw.lineO = 400.0f - (float)rc->draw.lineH / 2.0f;
	rc->draw.depart.x = rc->ray * 1;
	rc->draw.depart.y = rc->draw.lineO;
	rc->draw.ceil.x = rc->ray * 1;
	rc->draw.ceil.y = 0;
	simply_line(game, rc->draw.ceil, rc->draw.depart, game->color_ceil);
	rc->draw.fin.x = rc->ray * 1;
	rc->draw.fin.y = rc->draw.lineH + rc->draw.lineO;
	build_wall(game, rc->draw.depart, rc->draw.fin, rc);
	rc->draw.floor.x = rc->ray * 1;
	rc->draw.floor.y = W_HEIGHT;
	simply_line(game, rc->draw.fin, rc->draw.floor, game->color_floor);
}

void	shorter_ray(t_raycast *rc)
{
	if (rc->rayV.dis < rc->rayH.dis)
	{
		rc->dda.ray.x = rc->rayV.point.x;
		rc->dda.ray.y = rc->rayV.point.y;
		rc->disT = rc->rayV.dis;
		rc->draw.orient = VERTICAL;
	}
	else if (rc->rayH.dis <= rc->rayV.dis)
	{
		rc->dda.ray.x = rc->rayH.point.x;
		rc->dda.ray.y = rc->rayH.point.y;
		rc->disT = rc->rayH.dis;
		rc->draw.orient = HORIZONTAL;
	}
	rc->draw.next.x = rc->dda.ray.x;
	rc->draw.next.y = rc->dda.ray.y;
}
