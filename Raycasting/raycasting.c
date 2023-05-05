#include "new.h"

extern int tab;

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
			if (mx >= 0 && my >= 0 && mx < game->map.height && my < game->map.length && game->tab[my][mx] == '1')
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
		if (mx >= 0 && my >= 0 && mx < game->map.height && my < game->map.length && game->tab[my][mx] == '1')
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
	bresenham(game->img, game->player_pos, next, 0x000000FF);
	// DRAW 3D WALLS
	ca = game->pa - ra;
	// if (ca < 0)
	// 	ca += 2 * PI;
	// else if (ca > 2 * PI)
	// 	ca -= 2 * PI;
	disT = disT * cos(ca); // to fix fish eye
	lineH = (game->map.size * 320) /disT; //line height
	if (lineH > 320)
		lineH = 320;
	lineO = 160 - lineH / 2;   //line offset to be more central
	depart.x = r * 2 + 530;
	depart.y = lineO;
	fin.x = r * 2 + 530;
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