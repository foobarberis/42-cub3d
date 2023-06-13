#ifndef CUB3D_H
#define CUB3D_H

#include "mlc.h"
#include "mlx.h"
#include <X11/X.h>      /* event masks */
#include <X11/keysym.h> /* keycodes */
#include <math.h>

#define WINDOW_WIDTH	800
#define WINDOW_HEIGHT	600
#define texWidth 64
#define texHeight 64
#define mapWidth 24
#define mapHeight 24

typedef struct s_data   t_data;
typedef struct s_map    t_map;
typedef struct s_camera t_camera;

enum e_direction
{
	N,
	S,
	E,
	W
};

struct s_data
{
	void *mlx;
	void *win;
	void *img;
	char *addr;
	int   bpp;
	int   llen;
	int   end;
	int   win_x;
	int   win_y;
};

/*
 * pos_x : camera's x position.
 * pos_y : camera's y position.
 * dir_x : camera's x direction vector.
 * dir_y : camera's y direction vector.
*/
struct s_camera
{
	double pos_x;
	double pos_y;
	double dir_x;
	double dir_y;
	double plane_x;
	double plane_y;
};

/*
 * file		: array containing the map in ASCII form.
 * map		: 2D array containing the map in int form.
 * map_x	: map's width.
 * map_y	: map's height.
 * ceil		: ceiling color.
 * floor	: floor color.
 * tex		: array of pointers to the N, S, E, W textures.
*/
struct s_map
{
	char   *file;
	int    **map;
	int      map_x;
	int      map_y;
	uint32_t ceil;
	uint32_t floor;
	void    *tex[4];
};

#endif
