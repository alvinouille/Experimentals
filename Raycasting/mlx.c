/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:55:39 by ale-sain          #+#    #+#             */
/*   Updated: 2023/05/10 17:45:08 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "new.h"

void	deplacement_key(int key_symbole, t_game *game)
{
	t_moh2f	next_pos;

	next_pos = game->player_pos;
	if (key_symbole == W)
	{
		next_pos.y -= game->pd.y;
		next_pos.x -= game->pd.x;
	}
	if (key_symbole == S)
	{
		next_pos.y += game->pd.y;
		next_pos.x += game->pd.x;
	}
	if (key_symbole == A)
	{
		next_pos.x -= game->pd.y;
		next_pos.y += game->pd.x;
	}
	if (key_symbole == D)
	{
		next_pos.x += game->pd.y;
		next_pos.y -= game->pd.x;
	}
	if (!is_wall(game, next_pos))
		game->player_pos = next_pos;
}

int	deal_key(int key_symbole, t_game *game)
{
	if (key_symbole == XK_Escape)
	{
		mlx_loop_end(game->mlx);
		cleaner(game);
	}
	if (key_symbole == W || key_symbole == A || key_symbole == S
		|| key_symbole == D)
		deplacement_key(key_symbole, game);
	if (key_symbole == LEFT)
	{
		game->pa -= 0.1;
		if (game->pa < 0)
			game->pa += (2 * PI);
		game->pd.x = (cos(game->pa)) * 5;
		game->pd.y = (sin(game->pa)) * 5;
	}
	if (key_symbole == RIGHT)
	{
		game->pa += 0.1;
		if (game->pa >= (2 * PI))
			game->pa -= 2 * PI;
		game->pd.x = cos(game->pa) * 5;
		game->pd.y = sin(game->pa) * 5;
	}
	return (0);
}

int	display_(t_game *game)
{
	grey_screen(game);
	raycasting(game);
	draw_wall(game);
	draw_player(game);
	draw_pov(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}

void	mlx(t_game game)
{
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, W_WIDTH, W_HEIGHT, "Cub3D");
	game.img.img = mlx_new_image(game.mlx, W_WIDTH, W_HEIGHT);
	game.img.addr = mlx_get_data_addr(game.img.img, &(game.img.bits_per_pixel),
			&(game.img.line_length), &(game.img.endian));
	mlx_loop_hook(game.mlx, display_, &game);
	mlx_hook(game.win, KeyPress, KeyPressMask, &deal_key, &game);
	mlx_loop(game.mlx);
}

int	main(int ac, char **av)
{
	t_game	game;
	int		fd;
	char	*str;
	int		i;

	(void)ac;
	fd = open(av[1], O_RDONLY);
	str = gnl(fd);
	game.tab = ft_split(str, '\n');
	free(str);
	i = 0;
	while (game.tab[i])
		printf("%s \n", game.tab[i++]);
	init_player(&game, 0, 0);
	init_map(&game);
	mlx(game);
}
