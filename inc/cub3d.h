#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h> /* DEBUG */

# include "mlc.h"
# include "mlx.h"
# include <math.h>
# include <X11/X.h>			/* event masks */
# include <X11/keysym.h>	/* keycodes */

# define WINDOW_WIDTH	1920
# define WINDOW_HEIGHT	1080
# define FILL 'x'

typedef struct s_data   t_data;
typedef struct s_mlx	t_mlx;
typedef struct s_map    t_map;
typedef struct s_tex	t_tex;
typedef struct s_cam	t_cam;
typedef struct s_ray	t_ray;
typedef struct s_pix	t_pix;

enum e_direction
{
	N,
	S,
	E,
	W
};

enum e_key
{
	K_W,
	K_S,
	K_A,
	K_D,
	K_L,
	K_R
};

enum e_movement
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	ROT_L,
	ROT_R
};

struct s_data
{
	t_mlx	*mlx;
	t_cam	*cam;
	t_map	*map;
	t_ray	*ray;
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
	int key[6];
	double pos_x;
	double pos_y;
	double dir_x;
	double dir_y;
	double mospeed;
	double rospeed;
	double plane_x;
	double plane_y;
};

/*
 * map		: 2D array containing the map in int form.
 * map_x	: map's width.
 * map_y	: map's height.
 * ceil		: ceiling color.
 * floor	: floor color.
 * tex		: array of struct to the N, S, E, W textures.
*/
struct s_map
{
	int    **map;
	int      map_w;
	int      map_h;
	uint32_t ceil;
	uint32_t floor;
	t_tex    *tex;
};

struct s_tex
{
	void	*t;
	int		w;
	int		h;
	char *addr;
	int   bpp;
	int   llen;
	int   end;
};


struct s_ray
{
	// which box of the map we're in
	int map_x;
	int map_y;
	// calculate ray position and direction
	double cam_x;
	double dir_x;
	double dir_y;
	// length of ray from current position to next x or y-side
	double sdist_x;
	double sdist_y;
	// length of ray from one x or y-side to next x or y-side
	double ddist_x;
	double ddist_y;
	double perp_wall_dist;

	// what direction to step in x or y-direction (either +1 or -1)
	int step_x;
	int step_y;

	int hit; // was there a wall hit?
	int side;    // was a NS or a EW wall hit?
};

struct s_pix
{
	int32_t color;
	int line_h;
	int pitch;
	int draw_start;
	int draw_end;
	int tex_n;
	int tex_y;
	int tex_x;
	double wall_x;
	double step;
	double tex_pos;
};

t_data	*data_init(char *file);
int		**matrix_create(int w, int h);
void	matrix_destroy(int **m, int h);
void	data_destroy(t_data *d);
void	mlx_destroy(t_mlx *mlx);
void	map_destroy(t_data *d, t_map *map);
int		cub_exit(t_data *d, int code);

int		parsing(t_data *d, char *file);
int		parse_map(t_data *d, char **map);
int		parse_header(t_data *d, char **map);

int		islegal(int c);
int		get_map_width(char **map);
int		get_map_height(char **map);

int		parse_color(char *s, uint32_t *color);

void	get_player_pos(char **map, int *x, int *y);
void	get_player_dir(char c, double *dx, double *dy);
int		map_has_multiple_players(char **map, int x, int y);


void	setup_hooks(t_data *d);
int 	hook_keypress(int key, t_data *d);
int 	hook_keypress_release(int key, t_data *d);

int		move(t_data *d);
void	rotate_left(t_data *d);
void	rotate_right(t_data *d);

void	dda(t_data *d, t_ray *r);
void	ray_init(t_data *d, t_ray *r, int x);

int		draw_frame(t_data *d);
void	draw_pixel(t_data *d, t_pix *p, int x);
void	mlx_pixel_put_img(t_data *d, int x, int y, int color);

#endif

