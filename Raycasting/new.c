#include "new.h"

int tab[] =
{
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 1, 0, 0, 0, 1, 1,
    1, 0, 1, 0, 0, 0, 0, 1,
    1, 0, 1, 0, 1, 1, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 1, 0, 1,
    1, 0, 0, 0, 0, 1, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
};

int	is_wall(t_game *game, t_moh2f pos)
{
	int	x;
	int	y;

	x = (int)pos.x / 64;
	y = (int)pos.y / 64;
	if (game->tab[y][x] == '1')
		return (1);
	else
		return (0);
}

int	deal_key(int key_symbole, t_game *game)
{
	t_moh2f next_pos;

	next_pos = game->player_pos;
	if (key_symbole == XK_Escape)
	{
		mlx_loop_end(game->mlx);
		exit(0);
	}
	if (key_symbole == W)
	{
		next_pos.y -= game->pd.y; next_pos.x -= game->pd.x;
		if (is_wall(game, next_pos))
			return (0);
		else
			game->player_pos = next_pos;
	}
	if (key_symbole == S)
	{
		next_pos.y += game->pd.y; next_pos.x += game->pd.x;
		if (is_wall(game, next_pos))
			return (0);
		else
			game->player_pos = next_pos;
	}
	if (key_symbole == A)
	{
		next_pos.x -= game->pd.y; next_pos.y += game->pd.x;
		if (is_wall(game, next_pos))
			return (0);
		else
			game->player_pos = next_pos;
	}
	if (key_symbole == D)
	{
		next_pos.x += game->pd.y; next_pos.y -= game->pd.x;
		if (is_wall(game, next_pos))
			return (0);
		else
			game->player_pos = next_pos;
	}
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

void	img_pixel_put(t_data *img, int x, int y, int color)
{
	char	*px;

	px = img->addr + (int)(y * img->line_length
				+ x * (img->bits_per_pixel / 8));
	*(unsigned int *)px = color;
}

void	grey_screen(t_game *game)
{
	int	x;
	int	y;

	x = 1;
	y = 1;
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

void	drawCube(t_game *game, t_moh2f pos, int size, int color)
{
	int i;
	int j;

	i = 0;
	j = -1;
	while (++j < size)
	{
		while (i < size)
		{
			if (i && j)
				img_pixel_put((&game->img), pos.x + j -1, pos.y + i -1, color);
			else
				img_pixel_put((&game->img), pos.x + j, pos.y + i, color);
			i++;
		}
		i = 0;
	}
}

void	drawPlayer(t_game *game)
{
	drawCube(game, game->player_pos, 2, 0x00FFFF00);
}

void	drawWall(t_game *game)
{
	int	x = 0;
	int	y = 0;
	t_moh2f o;
	int color;

	while (y < game->map.height)
	{
		while (x < game->map.length)
		{
			if (game->tab[y][x] == '1')
				color = 0x00FFFFFF;
			else
				color = 0x00000000;
			o.x = x * game->map.size;
			o.y = y * game->map.size;
			drawCube(game, o, game->map.size, color);
			x++;
		}
		x = 0;
		y++;
	}
}


void	drawPov(t_game *game)
{
	t_moh2f next;

	next.x = game->player_pos.x - (game->pd.x * 2);
	next.y = game->player_pos.y - (game->pd.y * 2);
	bresenham(game->img, game->player_pos, next, 0X00FFFF00);
}

int	display_(t_game *game)
{
	grey_screen(game);
	drawWall(game);
	drawPlayer(game);
	drawRays2D(game);
	drawPov(game);
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

void	init_player(t_game *game)
{
	// int	i;
	// int	j;

	// i = 0;
	// j = 0;
	// while (game->tab[i])
	// {
	// 	while (tab[i][j])
	// 	{
	// 		if (tab[i][j] == 'N' || tab[i][j] == 'E' || tab[i][j] == 'O' || tab[i][j] == 'S')
	// 			game->player_pos.x = i
	// 	}
	// 	j = 0;
	// 	i++;
	// }
	game->player_pos.x = 300;
	game->player_pos.y = 300;
	game->pa = 0;
	game->pd.x = cos(game->pa);
	game->pd.y = sin(game->pa);
}

void	init_map(t_game *game)
{
	game->map.length = 8;
	game->map.height = 8;
	game->map.size = game->map.length * game->map.height;
}

char	**create(void)
{
	char **tab;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tab = malloc(sizeof(char *) * (8 + 1));
	while (i < 8)
	{
		tab[i] = malloc(sizeof(char) * (8 + 1));
		while (j < 8)
		{
			if (i == 0 || i == 7)
				tab[i][j] = '1';
			else
			{
				if (j == 0 || j == 7 || (j == 2 && i == 4) || (j == 2 && i == 3)
					|| (j == 2 && i == 2) || (j == 2 && i == 1) || (j == 5 && i == 5))
					tab[i][j] = '1';
				else 
					tab[i][j] = '0';
			}
			j++;
		}
		tab[i][j] = 0;
		j = 0;
		i++;
	}
	tab[i] = 0;
	i = 0;
	while (tab[i])
		printf("%s \n", tab[i++]);
	return (tab);
}

int	main()
{
	t_game game;

	game.tab = create();
	init_player(&game);
	init_map(&game);
	mlx(game);
}
