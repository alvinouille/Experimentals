/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:17:22 by ale-sain          #+#    #+#             */
/*   Updated: 2023/05/12 17:38:29 by alvina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "new.h"

float	shorter_dist(float ax, float ay, float bx, float by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

void	simply_line(t_game *game, t_moh2i start, t_moh2i end, int color)
{
	int	y;

	y = start.y;
	while (y <= end.y)
	{
		img_pixel_put((&game->img), start.x, y, color);
		y++;
	}
}

void	build_wall(t_game *game, t_moh2i start, t_moh2i end, t_raycast *rc)
{
	int	y;
	int toY, toX;
	int dft;

	if (rc->draw.orient == VERTICAL)
	{
		toX = (int)rc->dda.ray.y % SIZE;
		if (rc->draw.v_facing == RIGHTT)
			game->curr_txt = game->texture[0].tab;
		else
			game->curr_txt = game->texture[1].tab;
	}
	else
	{
		toX = (int)rc->dda.ray.x % SIZE;
		if (rc->draw.h_facing == UP)
			game->curr_txt = game->texture[2].tab;
		else
			game->curr_txt = game->texture[3].tab;
	}
	y = start.y;
	while (y < end.y)
	{
		dft = y + (((int)round((SIZE * W_HEIGHT) / rc->disT)) / 2) - round(W_HEIGHT / 2);
		toY = dft * (SIZE / ((float)round((SIZE * W_HEIGHT) / rc->disT)));
		if (toY > SIZE - 1)
			toY = SIZE - 1;
		if (toY < 0)
			toY = 0;
		rc->draw.color = game->curr_txt[toY * SIZE + toX];
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
