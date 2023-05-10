/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:22:32 by ale-sain          #+#    #+#             */
/*   Updated: 2023/05/10 17:43:55 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "new.h"

void	init_player_orientation(t_game *game, int i, int j)
{
	game->player_pos.x = j * SIZE;
	game->player_pos.y = i * SIZE;
	if (game->tab[i][j] == 'N')
		game->pa = P2;
	if (game->tab[i][j] == 'E')
		game->pa = PI;
	if (game->tab[i][j] == 'O')
		game->pa = 0;
	if (game->tab[i][j] == 'S')
		game->pa = P3;
}

void	init_player(t_game *game, int i, int j)
{
	game->pa = -1;
	while (game->tab[i])
	{
		while (game->tab[i][j])
		{
			if (game->tab[i][j] == 'N' || game->tab[i][j] == 'E'
				|| game->tab[i][j] == 'O' || game->tab[i][j] == 'S')
			{
				init_player_orientation(game, i, j);
				break ;
			}
			j++;
		}
		if (game->pa != -1)
			break ;
		j = 0;
		i++;
	}
	game->pd.x = cos(game->pa) * 5;
	game->pd.y = sin(game->pa) * 5;
	printf("player at x:%f, y:%f, turned to %f \n", game->player_pos.x,
		game->player_pos.y, game->pa);
}

void	init_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (game->tab[i])
	{
		while (game->tab[i][j])
			j++;
		game->map.length = j;
		j = 0;
		i++;
	}
	game->map.height = i;
	game->map.size = game->map.length * game->map.height;
	printf("height : %d, length : %d, size : %d\n", game->map.height,
		game->map.length, game->map.size);
}
