#include "new.h"

int tab[] =
{
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 1, 0, 0, 0, 0, 1,
    1, 0, 1, 0, 0, 0, 0, 1,
    1, 0, 1, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 1, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
};


int	deal_key(int key_symbole, t_game *game)
{
	if (key_symbole == XK_Escape)
	{
		mlx_loop_end(game->mlx);
		exit(0);
	}
	if (key_symbole == W)
		game->player_pos.y -= 5;
	if (key_symbole == S)
		game->player_pos.y += 5;
	if (key_symbole == A)
		game->player_pos.x -= 5;
	if (key_symbole == D)
		game->player_pos.x += 5;
	if (key_symbole == LEFT)
	{
		game->pa -= 0.1;
		if (game->pa < 0)
			game->pa += (2 * PI);
		game->pd.x = (cos(game->pa));
		game->pd.y = (sin(game->pa));
		// printf("pa = %f, joueur.x : %f y : %f\n", game->pa, game->player_pos.x, game->player_pos.y);
	}
	if (key_symbole == RIGHT)
	{
		game->pa += 0.1;
		if (game->pa >= (2 * PI))
			game->pa -= 2 * PI;
		game->pd.x = cos(game->pa);
		game->pd.y = sin(game->pa);
		// printf("pa = %f, joueur.x : %f y : %f\n", game->pa, game->player_pos.x, game->player_pos.y);
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

	while (y < game->map.width)
	{
		while (x < game->map.length)
		{
			if (tab[y * game->map.length + x] == 1)
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

void	simply_line(t_game *game, t_moh2f start, t_moh2f end, int color)
{
	int y;
	int x;

	y = start.y;
	x = start.x;
	while (x < start.x +4)
	{
		while (y <= end.y)
		{
			img_pixel_put((&game->img), x, y, color);
			y++;
		}
		y = start.y;
		x++;
	}
}
void	drawLine(t_game *game)
{
	t_moh2f next;

	next.x = game->player_pos.x + game->pd.x *10;
	next.y = game->player_pos.y + game->pd.y *10;
	// printf("x : %f, y = %f\n", next.x, next.y);
	bresenham(game->img, next, game->player_pos);
}

float	shorter_dist(double ax, double ay, double bx, double by)
{
	return (sqrt ((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}
void	drawRays2D(t_game *game)
{
	int r, mx, my, mp, dof;
	double rx, ry, ra, xo, yo, nTan, aTan;
	double disV, disH, disT;
	double hx, hy, vx, vy;
	double lineH, lineO; 
	double ca;
	int color;
	t_moh2f next, depart, fin;

	ra = game->pa - (DR * 30);
	if (ra < 0)
		ra += 2 * PI;
	else if (ra > 2 * PI)
		ra -= 2 * PI;
	r = 0;
	while (r < 60)
	{
		//CHECK HORIZONTAL LINES
		dof = 0;
		disH = 1000000;
		hx = game->player_pos.x;
		hy = game->player_pos.y;
		aTan = -1/tan(ra); 
		if (ra < PI)  //looking down
		{
			ry = (((int)game->player_pos.y / 64) *64) -0.0001;
			rx = (game->player_pos.y - ry) * aTan + game->player_pos.x;
			yo = -64;
			xo = -yo * aTan;
		}
		if (ra > PI)  //looking up
		{
			ry = (((int)game->player_pos.y / 64) *64) + 64;
			rx = (game->player_pos.y - ry) * aTan + game->player_pos.x;
			yo = 64;
			xo = -yo * aTan;
		}
		if (ra < 0.1 || ra == PI) //looking horizontally
		{
			rx = game->player_pos.x;
			ry = game->player_pos.y;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)rx / 64;
			my = (int)ry / 64;
			mp = my * game->map.length + mx;
			if (mp > 0 && mp < game->map.length * game->map.width && tab[mp] == 1)
			{
				hx = rx;
				hy = ry;
				disH = shorter_dist(game->player_pos.x, game->player_pos.y, hx, hy);
				dof = 8;
			}
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
	// VERTICAL LINE
	dof = 0;
	disV = 1000000;
	vx = game->player_pos.x;
	vy = game->player_pos.y;
	nTan = -tan(ra); 
	if (ra < P2 || ra > P3)  //looking right
	{
		rx = (((int)game->player_pos.x / 64) *64) -0.0001;
		ry = (game->player_pos.x - rx) * nTan + game->player_pos.y;
		xo = -64;
		yo = -xo * nTan;
	}
	if (ra > P2 && ra < P3)  //looking left
	{
		rx = (((int)game->player_pos.x / 64) *64) + 64;
		ry = (game->player_pos.x - rx) * nTan + game->player_pos.y;
		xo = 64;
		yo = -xo * nTan;
	}
	while (dof < 8)
	{
		mx = (int)rx / 64;
		my = (int)ry / 64;
		mp = my * game->map.width + mx;
		if (mp > 0 && mp < game->map.length * game->map.width && tab[mp] == 1)
		{
			vx = rx;
			vy = ry;
			disV = shorter_dist(game->player_pos.x, game->player_pos.y, vx, vy);
			dof = 8;
		}
		else
		{
			rx += xo;
			ry += yo;
			dof += 1;
		}
	}
	if (disV < disH)
	{
		rx = vx;
		ry = vy;
		disT = disV;
		color = 0x00DB1702;
	}
	if (disH < disV)
	{
		rx = hx;
		ry = hy;
		disT = disH;
		color = 0x00FF0000;
	}
	next.x = rx;
	next.y = ry;
	bresenham(game->img, next, game->player_pos);
	// DRAW 3D WALLS
	ca = game->pa - ra;
	if (ca < 0)
		ca += 2 * PI;
	else if (ca > 2 * PI)
		ca -= 2 * PI;
	disT = disT * cos(ca); // to fix fish eye
	lineH = (game->map.size * 320) /disT; //line height
	if (lineH > 320)
		lineH = 320;
	lineO = 160 - lineH / 2;   //line offset to be more central
	depart.x = r * 4 + 530;
	depart.y = lineO;
	fin.x = r * 4 + 530;
	fin.y = lineH + lineO;
	// drawCube(game, depart, 1, 0x0000FFFF);
	// printf("here\n");
	simply_line(game, depart, fin, color);
	ra += DR;
	if (ra < 0)
		ra += 2 * PI;
	else if (ra > 2 * PI)
		ra -= 2 * PI;
	r++;
	}
}

int	ddisplay(t_game *game)
{
	grey_screen(game);
	drawWall(game);
	drawPlayer(game);
	// drawLine(game);
	drawRays2D(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}

void	mlx(t_game game)
{
	game.mlx = mlx_init();
	printf("%f\n", cos(1));
	game.win = mlx_new_window(game.mlx, W_WIDTH, W_HEIGHT, "Cub3D");
	game.img.img = mlx_new_image(game.mlx, W_WIDTH, W_HEIGHT);
	game.img.addr = mlx_get_data_addr(game.img.img, &(game.img.bits_per_pixel),
			&(game.img.line_length), &(game.img.endian));
	mlx_loop_hook(game.mlx, ddisplay, &game);
	mlx_hook(game.win, KeyPress, KeyPressMask, &deal_key, &game);
	mlx_loop(game.mlx);
}

void	init_player(t_game *game)
{
	game->player_pos.x = 300;
	game->player_pos.y = 300;
	game->pa = 0;
	game->pd.x = cos(game->pa);
	game->pd.y = sin(game->pa);
}

void	init_map(t_game *game)
{
	game->map.length = 8;
	game->map.width = 8;
	game->map.size = 64;
}

int	main()
{
	t_game game;

	init_player(&game);
	init_map(&game);
	mlx(game);
}
