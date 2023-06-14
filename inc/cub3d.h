#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h> /* DEBUG */

# include "mlc.h"
# include "mlx.h"
# include <math.h>
# include <X11/X.h>			/* event masks */
# include <X11/keysym.h>	/* keycodes */

# define WINDOW_WIDTH	800
# define WINDOW_HEIGHT	600

typedef struct s_data   t_data;
typedef struct s_mlx	t_mlx;
typedef struct s_map    t_map;
typedef struct s_cam	t_cam;

enum e_direction
{
	N = 1,
	S,
	E,
	W
};

struct s_data
{
	t_mlx	*mlx;
	t_cam	*cam;
	t_map	*map;
};

/*
 * mlx		: pointer to the mlx context.
 * win		: pointer to the mlx window.
 * img		:
 * addr		:
 * bpp		: bits per pixel.
 * llen		: line length.
 * end		: endian type.
 * win_w	: window width
 * win_h 	: window height
*/
struct s_mlx
{
	void *mlx;
	void *win;
	void *img;
	char *addr;
	int   bpp;
	int   llen;
	int   end;
	int	  win_w;
	int	  win_h;
};

/*
 * pos_x : camera's x position.
 * pos_y : camera's y position.
 * dir_x : camera's x direction vector.
 * dir_y : camera's y direction vector.
*/
struct s_cam
{
	double pos_x;
	double pos_y;
	double dir_x;
	double dir_y;
	double plane_x;
	double plane_y;
};

/*
 * map		: 2D array containing the map in int form.
 * map_x	: map's width.
 * map_y	: map's height.
 * ceil		: ceiling color.
 * floor	: floor color.
 * tex		: array of pointers to the N, S, E, W textures.
*/
struct s_map
{
	int    **map;
	int      map_w;
	int      map_h;
	uint32_t ceil;
	uint32_t floor;
	void    *tex[4];
};

t_data		*data_create(char *file);
t_mlx		*mlx_create(void);
t_cam		*cam_create(t_data *d);
t_map		*map_create(char *file);
void		data_destroy(t_data *d);
void		mlx_destroy(t_mlx *mlx);
void		map_destroy(t_map *map);
int			cub_exit(t_data *d, int code);

int map_parsing(t_map *map, char *file);

void		mlx_pixel_put_img(t_data *d, int x, int y, int color);
int			hook_keypress(t_data *d, int key);
void		setup_hooks(t_data *d);

#endif
