/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:17:22 by ale-sain          #+#    #+#             */
/*   Updated: 2023/05/10 17:47:42 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "new.h"

float	shorter_dist(float ax, float ay, float bx, float by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

void	simply_line(t_game *game, t_moh2f start, t_moh2f end, int color)
{
	int	y;

	y = start.y;
	while (y <= end.y)
	{
		img_pixel_put((&game->img), start.x, y, color);
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
	rc->draw.lineH = (SIZE * W_HEIGHT) / rc->disT;
	if (rc->draw.lineH > W_HEIGHT)
		rc->draw.lineH = W_HEIGHT;
	rc->draw.lineO = 400 - rc->draw.lineH / 2;
	rc->draw.depart.x = rc->ray * 1;
	rc->draw.depart.y = rc->draw.lineO;
	rc->draw.ceil.x = rc->ray * 1;
	rc->draw.ceil.y = 0;
	simply_line(game, rc->draw.ceil, rc->draw.depart, 0x00808080);
	rc->draw.fin.x = rc->ray * 1;
	rc->draw.fin.y = rc->draw.lineH + rc->draw.lineO;
	simply_line(game, rc->draw.depart, rc->draw.fin, rc->draw.color);
	rc->draw.floor.x = rc->ray * 1;
	rc->draw.floor.y = W_HEIGHT;
	simply_line(game, rc->draw.fin, rc->draw.floor, 0x00E1C699);
}

void	shorter_ray(t_raycast *rc)
{
	if (rc->rayV.dis < rc->rayH.dis)
	{
		rc->dda.ray.x = rc->rayV.point.x;
		rc->dda.ray.y = rc->rayV.point.y;
		rc->disT = rc->rayV.dis;
		rc->draw.color = 0x00DB1702;
	}
	else if (rc->rayH.dis <= rc->rayV.dis)
	{
		rc->dda.ray.x = rc->rayH.point.x;
		rc->dda.ray.y = rc->rayH.point.y;
		rc->disT = rc->rayH.dis;
		rc->draw.color = 0x00FF0000;
	}
	rc->draw.next.x = rc->dda.ray.x;
	rc->draw.next.y = rc->dda.ray.y;
}
