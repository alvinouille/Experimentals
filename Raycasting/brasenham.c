/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brasenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 19:38:10 by alvina            #+#    #+#             */
/*   Updated: 2023/05/04 19:44:07 by alvina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "new.h"

void	first(t_data img, t_moh2f curr, t_moh2f next, int color)
{
	int		dy;
	int		dx;
	float	e;
	int		x;
	int		y;

	x = curr.x;
	y = curr.y;
	e = next.x - curr.x;
	dx = 2 * e;
	dy = 2 * (next.y - curr.y);
	// printf("1\n");
	while (1)
	{
		if (x < W_HEIGHT && x > 0 && y < W_WIDTH && y > 0)
			img_pixel_put(&img, x, y, color);
		if (x >= next.x)
			break ;
		x++;
		e -= dy;
		if (e < 0)
		{
			y++;
			e += dx;
		}
	}
}

void	second(t_data img, t_moh2f curr, t_moh2f next, int color)
{
	int		dy;
	int		dx;
	float	e;
	int		x;
	int		y;

	x = curr.x;
	y = curr.y;
	e = next.y - curr.y;
	dy = 2 * e;
	dx = 2 * (next.x - curr.x);
	// printf("2\n");
	while (1)
	{
		if (x < W_HEIGHT && x > 0 && y < W_WIDTH && y > 0)
			img_pixel_put(&img, x, y, color);
		if (y >= next.y)
			break ;
		y++;
		e -= dx;
		if (e < 0)
		{
			x++;
			e += dy;
		}
	}
}

void	vertical(t_data img, t_moh2f curr, t_moh2f next, int color)
{
	int		x;
	int		y;

	x = curr.x;
	y = curr.y;
	if (y <= next.y)
	{
		while (y <= next.y)
		{
			if (x < W_HEIGHT && x > 0 && y < W_WIDTH && y > 0)
				img_pixel_put(&img, x, y, color);
			y++;
		}
	}
	else
	{
		while (y >= next.y)
		{
			if (x < W_HEIGHT && x > 0 && y < W_WIDTH && y > 0)
				img_pixel_put(&img, x, y, color);
			y--;
		}
	}
}

void	fifth(t_data img, t_moh2f curr, t_moh2f next, int color)
{
	int		dy;
	int		dx;
	float	e;
	int		x;
	int		y;

	x = curr.x;
	y = curr.y;
	e = next.y - curr.y;
	dy = 2 * e;
	dx = 2 * (next.x - curr.x);
	// printf("5\n");
	while (1)
	{
		if (x < W_HEIGHT && x > 0 && y < W_WIDTH && y > 0)
			img_pixel_put(&img, x, y, color);
		if (x <= next.x)
			break ;
		x--;
		e -= dy;
		if (e >= 0)
		{
			y--;
			e += dx;
		}
	}
}

void	sixth(t_data img, t_moh2f curr, t_moh2f next, int color)
{
	int		dy;
	int		dx;
	float	e;
	int		x;
	int		y;

	x = curr.x;
	y = curr.y;
	e = next.y - curr.y;
	dy = 2 * e;
	dx = 2 * (next.x - curr.x);
	// printf("6\n");
	while (1)
	{
		if (x < W_HEIGHT && x > 0 && y < W_WIDTH && y > 0)
			img_pixel_put(&img, x, y, color);
		if (y <= next.y)
			break ;
		y--;
		e -= dx;
		if (e >= 0)
		{
			x--;
			e += dy;
		}
	}
}


void	third(t_data img, t_moh2f curr, t_moh2f next, int color)
{
	int		dy;
	int		dx;
	float	e;
	int		x;
	int		y;

	x = curr.x;
	y = curr.y;
	e = next.y - curr.y;
	dy = 2 * e;
	dx = 2 * (next.x - curr.x);
	// printf("3\n");
	while (1)
	{
		if (x < W_HEIGHT && x > 0 && y < W_WIDTH && y > 0)
			img_pixel_put(&img, x, y, color);
		if (y >= next.y)
			break ;
		y++;
		e += dx;
		if (e <= 0)
		{
			x--;
			e += dy;
		}
	}
}

void	fourth(t_data img, t_moh2f curr, t_moh2f next, int color)
{
	int		dy;
	int		dx;
	float	e;
	int		x;
	int		y;

	x = curr.x;
	y = curr.y;
	e = next.x - curr.x;
	dx = 2 * e;
	dy = 2 * (next.y - curr.y);
	// printf("4\n");
	while (1)
	{
		if (x < W_HEIGHT && x > 0 && y < W_WIDTH && y > 0)
			img_pixel_put(&img, x, y, color);
		if (x <= next.x)
			break ;
		x--;
		e += dy;
		if (e >= 0)
		{
			y++;
			e += dx;
		}
	}
}

void	eight(t_data img, t_moh2f curr, t_moh2f next, int color)
{
	int		dy;
	int		dx;
	float	e;
	int		x;
	int		y;

	x = curr.x;
	y = curr.y;
	e = next.x - curr.x;
	dx = 2 * e;
	dy = 2 * (next.y - curr.y);
	// printf("8\n");
	while (1)
	{
		if (x < W_HEIGHT && x > 0 && y < W_WIDTH && y > 0)
			img_pixel_put(&img, x, y, color);
		if (x >= next.x)
			break ;
		x++;
		e += dy;
		if (e < 0)
		{
			y--;
			e += dx;
		}
	}
}

void	seventh(t_data img, t_moh2f curr, t_moh2f next, int color)
{
	int		dy;
	int		dx;
	float	e;
	int		x;
	int		y;

	x = curr.x;
	y = curr.y;
	e = next.y - curr.y;
	dy = 2 * e;
	dx = 2 * (next.x - curr.x);
	// printf("7\n");
	while (1)
	{
		if (x < W_HEIGHT && x > 0 && y < W_WIDTH && y > 0)
			img_pixel_put(&img, x, y, color);
		if (y <= next.y)
			break ;
		y--;
		e += dx;
		if (e > 0)
		{
			x++;
			e += dy;
		}
	}
}


static void	going_up(t_data img, t_moh2f curr, t_moh2f next, float pente, int color)
{
	int	x;

	x = curr.x;
	if (x < next.x)
	{
		if (pente >= 1)
			second(img, curr, next, color);
		else
			first(img, curr, next, color);
	}
	else if (x == next.x)
		vertical(img, curr, next, color);
	else
	{
		if (pente < 1)
			fifth(img, curr, next, color);
		else
			sixth(img, curr, next, color);
	}
}

static void	going_down(t_data img, t_moh2f curr, t_moh2f next, float pente, int color)
{
	int	x;

	x = curr.x;
	if (x < next.x)
	{
		if (pente >= -1)
			eight(img, curr, next, color);
		else
			seventh(img, curr, next, color);
	}
	else
	{
		if (pente < -1)
			third(img, curr, next, color);
		else
			fourth(img, curr, next, color);
	}
}

void	bresenham(t_data img, t_moh2f curr, t_moh2f next, int color)
{
	int		dy;
	int		dx;
	float	pente;

	dy = next.y - curr.y;
	dx = next.x - curr.x;
	if (dx != 0)
		pente = (float)dy / (float)dx;
	else
	{
		pente = (float)dy;
		if (dy < 0)
			pente = -pente;
	}
	if (pente >= 0)
		going_up(img, curr, next, pente, color);
	else
		going_down(img, curr, next, pente, color);
}
