#include "new.h"

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
}

int	deal_key(int key_symbole, t_game *game)
{
	t_moh2f next_pos;

	next_pos = game->player_pos;
	if (key_symbole == XK_Escape)
	{
		mlx_loop_end(game->mlx);
		cleaner(game);
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
			else if (game->tab[y][x] == 'X')
				color = 0x00808080;
			else
				color = 0x00000000;
			o.x = x * SIZE;
			o.y = y * SIZE;
			drawCube(game, o, SIZE, color);
			x++;
		}
		x = 0;
		y++;
	}
}


void	drawPov(t_game *game)
{
	t_moh2f next;

	next.x = game->player_pos.x - game->pd.x ;
	next.y = game->player_pos.y - game->pd.y;
	bresenham(game->img, game->player_pos, next, 0X00FFFF00);
}

int	display_(t_game *game)
{
	grey_screen(game);
	drawRays2D(game);
	drawWall(game);
	drawPlayer(game);
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
	int	i;
	int	j;

	i = 0;
	j = 0;
	game->pa = -1;
	while (game->tab[i])
	{
		while (game->tab[i][j])
		{
			if (game->tab[i][j] == 'N' || game->tab[i][j] == 'E'
				|| game->tab[i][j] == 'O' || game->tab[i][j] == 'S')
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
				break;
			}
			j++;
		}
		if (game->pa != -1)
			break;
		j = 0;
		i++;
	}
	game->pd.x = cos(game->pa) *5;
	game->pd.y = sin(game->pa) *5;
	printf("player at x:%f, y:%f, turned to %f \n", game->player_pos.x, game->player_pos.y, game->pa);
}

void	init_map(t_game *game)
{
	int i = 0;
	int j = 0;

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
	printf("height : %d, length : %d, size : %d\n", game->map.height, game->map.length, game->map.size);
}

int	main(int ac, char **av)
{
	t_game game;

	int fd = open(av[1], O_RDONLY);
	char *str = gnl(fd);
	game.tab = ft_split(str, '\n');
	free(str);
	int i = 0;
	while (game.tab[i])
		printf("%s \n", game.tab[i++]);
	init_player(&game);
	init_map(&game);
	mlx(game);
}
