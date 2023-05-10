/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:24:04 by ale-sain          #+#    #+#             */
/*   Updated: 2023/05/10 17:43:46 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "new.h"

void	grey_screen(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < W_HEIGHT)
	{
		while (x < W_WIDTH)
		{
			img_pixel_put((&game->img), x, y, 0x00808080);
			x++;
		}
		x = 0;
		y++;
	}
}

void	draw_cube(t_game *game, t_moh2f pos, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (++j < size)
	{
		while (i < size)
		{
			if (i && j)
				img_pixel_put((&game->img), pos.x + j - 1, pos.y + i - 1,
					color);
			else
				img_pixel_put((&game->img), pos.x + j, pos.y + i, color);
			i++;
		}
		i = 0;
	}
}

void	draw_player(t_game *game)
{
	draw_cube(game, game->player_pos, 2, 0x00FFFF00);
}

void	draw_wall(t_game *game)
{
	int		x;
	int		y;
	t_moh2f	o;
	int		color;

	x = 0;
	y = 0;
	while (y < game->map.height)
	{
		while (x < game->map.length)
		{
			if (game->tab[y][x] == '1')
				color = 0x00FFFFFF;
			else if (game->tab[y][x] == 'X')
				color = 0x00808080;
			else
				color = 0x00000000;
			o.x = x * SIZE;
			o.y = y * SIZE;
			draw_cube(game, o, SIZE, color);
			x++;
		}
		x = 0;
		y++;
	}
}

void	draw_pov(t_game *game)
{
	t_moh2f	next;

	next.x = game->player_pos.x - game->pd.x;
	next.y = game->player_pos.y - game->pd.y;
	bresenham(game->img, game->player_pos, next, 0X00FFFF00);
}
