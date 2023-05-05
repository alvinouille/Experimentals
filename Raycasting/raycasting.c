#include "new.h"

float	shorter_dist(double ax, double ay, double bx, double by)
{
	return (sqrt ((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

void	simply_line(t_game *game, t_moh2f start, t_moh2f end, int color)
{
	int y;

	y = start.y;
	while (start.x <= end.x + 1)
	{
		while (y <= end.y)
		{
			img_pixel_put((&game->img), start.x, y, color);
			y++;
		}
		y = start.y;
		start.x++;
	}
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

	ra = game->pa - (DR4 * 120);
	if (ra < 0)
		ra += 2 * PI;
	else if (ra > 2 * PI)
		ra -= 2 * PI;
	r = 0;
	while (r < 240)
	{
		// CHECK HORIZONTAL LINES
		dof = 0;
		disH = 1000000;
		hx = game->player_pos.x;
		hy = game->player_pos.y;
		aTan = -1/tan(ra); 
		if (ra < PI)  //looking down
		{
			ry = (((int)game->player_pos.y / SIZE) *SIZE) -0.0001;	
			rx = (game->player_pos.y - ry) * aTan + game->player_pos.x;
			yo = -SIZE;
			xo = -yo * aTan;
		}
		if (ra > PI)  //looking up
		{
			ry = (((int)game->player_pos.y / SIZE) *SIZE) + SIZE;
			rx = (game->player_pos.y - ry) * aTan + game->player_pos.x;
			yo = SIZE;
			xo = -yo * aTan;
		}
		if (ra < 0.1 || ra == PI) //looking horizontally
		{
			rx = game->player_pos.x;
			ry = game->player_pos.y;
			dof = game->map.height;
		}
		while (dof < game->map.height)
		{
			mx = (int)rx / SIZE;
			my = (int)ry / SIZE;
			if (mx >= 0 && my >= 0 && mx < game->map.length && my < game->map.height && game->tab[my][mx] == '1')
			{
				hx = rx;
				hy = ry;
				disH = shorter_dist(game->player_pos.x, game->player_pos.y, hx, hy);
				dof = game->map.height;
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
		rx = (((int)game->player_pos.x / SIZE) *SIZE) -0.0001;
		ry = (game->player_pos.x - rx) * nTan + game->player_pos.y;
		xo = -SIZE;
		yo = -xo * nTan;
	}
	if (ra > P2 && ra < P3)  //looking left
	{
		rx = (((int)game->player_pos.x / SIZE) *SIZE) + SIZE;
		ry = (game->player_pos.x - rx) * nTan + game->player_pos.y;
		xo = SIZE;
		yo = -xo * nTan;
	}
	while (dof < game->map.length)
	{
		mx = (int)rx / SIZE;
		my = (int)ry / SIZE;
		if (mx >= 0 && my >= 0 && mx < game->map.length && my < game->map.height && game->tab[my][mx] == '1')
		{
			vx = rx;
			vy = ry;
			disV = shorter_dist(game->player_pos.x, game->player_pos.y, vx, vy);
			dof = game->map.length;
		}
		else
		{
			rx += xo;
			ry += yo;
			dof += 1;
		}
	}
	if (disV <= disH)
	{
		rx = vx;
		ry = vy;
		disT = disV;
		color = 0x00DB1702;
	}
	else if (disH < disV)
	{
		rx = hx;
		ry = hy;
		disT = disH;
		color = 0x00FF0000;
	}
	next.x = rx;
	next.y = ry;
	bresenham(game->img, game->player_pos, next, 0x000000FF);
	// DRAW 3D WALLS
	ca = game->pa - ra;
	if (ca < 0)
		ca += 2 * PI;
	else if (ca > 2 * PI)
		ca -= 2 * PI;
	disT = disT * cos(ca); // to fix fish eye
	lineH = (SIZE * 520) /disT; //line height
	if (lineH > 520)
		lineH = 520;
	lineO = 700 - lineH / 2;   //line offset to be more central
	depart.x = r * 2 + 250;
	depart.y = lineO;
	fin.x = r * 2 + 250;
	fin.y = lineH + lineO;
	simply_line(game, depart, fin, color);
	r++;
	ra += DR4;
	if (ra < 0)
		ra += 2 * PI;
	else if (ra > 2 * PI)
		ra -= 2 * PI;
	}
}