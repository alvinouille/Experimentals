#ifndef NEW_H
# define NEW_H

# include <fcntl.h>
# include "mlx/mlx/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <limits.h>
# include <float.h>
# include <math.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>

# define W_WIDTH	1024
# define W_HEIGHT	512

# define ESC 65307
# define W 119
# define A 97
# define D 100
# define S 115
# define LEFT 65361
# define RIGHT 65363
# define PI 3.14159265
# define P2 PI/2
# define P3 3*PI/2
# define DR 0.0174533

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct {
    double x;
    double y;
} t_moh2f;

typedef struct {
    int x;
    int y;
} t_moh2i;

typedef struct s_map
{
    int length;
    int width;
    int size;
}   t_map;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_data		img;
	t_map       map;
    double       pa;
    t_moh2f     pd;
	t_moh2f		player_pos;
}	t_game;


void	bresenham(t_data img, t_moh2f curr, t_moh2f next);
void	img_pixel_put(t_data *img, int x, int y, int color);

#endif