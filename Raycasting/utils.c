/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:25:56 by ale-sain          #+#    #+#             */
/*   Updated: 2023/05/10 17:46:45 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "new.h"

void	cleaner(t_game *game)
{
	int	i;

	i = 0;
	if (game->tab)
	{
		while (game->tab[i])
			free(game->tab[i++]);
		free(game->tab);
	}
	if (game->win && game->mlx)
	{
		mlx_clear_window(game->mlx, game->win);
		mlx_destroy_window(game->mlx, game->win);
	}
	if (game->img.img)
		mlx_destroy_image(game->mlx, game->img.img);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	exit(0);
}

void	img_pixel_put(t_data *img, int x, int y, int color)
{
	char	*px;

	px = img->addr + (int)(y * img->line_length + x * (img->bits_per_pixel
				/ 8));
	*(unsigned int *)px = color;
}

int	is_wall(t_game *game, t_moh2f pos)
{
	int	x;
	int	y;

	x = (int)pos.x / SIZE;
	y = (int)pos.y / SIZE;
	if (game->tab[y][x] == '1')
		return (1);
	else
		return (0);
}
