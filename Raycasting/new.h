#ifndef NEW_H
# define NEW_H

# include "mlx/mlx/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <float.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>

# define W_WIDTH 960
# define W_HEIGHT 800

# define ESC 65307
# define W 119
# define A 97
# define D 100
# define S 115
# define LEFT 65361
# define RIGHT 65363
# define PI 3.14159265
# define P2 PI / 2
# define P3 3 * PI / 2
# define DR16 0.00109083078
# define SIZE 8

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

typedef struct
{
	double	x;
	double	y;
}			t_moh2f;

typedef struct
{
	int		x;
	int		y;
}			t_moh2i;

typedef struct s_map
{
	int		length;
	int		height;
	int		size;
}			t_map;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	t_data	img;
	t_map	map;
	double	pa;
	char	**tab;
	t_moh2f	pd;
	t_moh2f	player_pos;
}			t_game;

typedef struct s_dda
{
	t_moh2f	ray;
	t_moh2f	pas;
	float	rot_angle;
	float	nTan;
	float	aTan;
}			t_dda;

typedef struct s_ray
{
	float	dis;
	t_moh2f	point;
}			t_ray;

typedef struct s_draw
{
	float	lineH;
	float	lineO;
	float	ca;
	int		color;
	t_moh2f	next;
	t_moh2f	depart;
	t_moh2f	fin;
	t_moh2f	ceil;
	t_moh2f	floor;
}			t_draw;

typedef struct s_raycast
{
	t_dda	dda;
	float	disT;
	t_ray	rayV;
	t_ray	rayH;
	t_moh2i	map;
	int		ray;
	int		dof;
	t_draw	draw;
}			t_raycast;

/*	MLX	*/
void		deplacement_key(int key_symbole, t_game *game);
int			deal_key(int key_symbole, t_game *game);
int			display_(t_game *game);
void		mlx(t_game game);

/*	INIT	*/
void		init_player_orientation(t_game *game, int i, int j);
void		init_player(t_game *game, int i, int j);
void		init_map(t_game *game);

/*	DRAW MINIMAP	*/
void		grey_screen(t_game *game);
void		draw_cube(t_game *game, t_moh2f pos, int size, int color);
void		draw_player(t_game *game);
void		draw_wall(t_game *game);
void		draw_pov(t_game *game);

/*	RAYCASTING	*/
void		raycasting(t_game *game);
void		dda_vert(t_game *game, t_raycast *rc);
void		spawn_vert(t_game *game, t_raycast *rc);
void		dda_horiz(t_game *game, t_raycast *rc);
void		spawn_horiz(t_game *game, t_raycast *rc);

/*	RAYCAST_UTILS	*/
float		shorter_dist(float ax, float ay, float bx, float by);
void		simply_line(t_game *game, t_moh2f start, t_moh2f end, int color);
void		draw_3d(t_game *game, t_raycast *rc);
void		shorter_ray(t_raycast *rc);

/*	BRESENHAM	*/
void		bresenham(t_data img, t_moh2f curr, t_moh2f next, int color);

/*	UTILS	*/
void		cleaner(t_game *game);
void		img_pixel_put(t_data *img, int x, int y, int color);
int			is_wall(t_game *game, t_moh2f pos);

/*	OPTION	*/
char		*gnl(int fd);
char		**ft_split(char const *s, char c);

#endif