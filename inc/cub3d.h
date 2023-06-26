/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 13:19:48 by mbarberi          #+#    #+#             */
/*   Updated: 2023/06/26 13:28:29 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h> /* DEBUG */

# include "mlc.h"
# include "mlx.h"
# include <math.h>
# include <X11/X.h>			/* event masks */
# include <X11/keysym.h>	/* keycodes */

# define WINDOW_WIDTH	800
# define WINDOW_HEIGHT	600
# define FILL 'x'
# define R_MAP 5
# define ERR_FORBID "cub3d: line %d: map contains forbidden character (`%c')\n"
# define ERR_EMPTY "cub3d: line %d: map contains empty lines\n"
# define ERR_DUPID "cub3d: duplicate identifier\n"
# define ERR_TEX "cub3d: %s: texture could not be loaded\n"
# define ERR_UNREC_ID "cub3d: %s: unrecognized identifier\n"
# define ERR_RGB_RANGE "cub3d: %s: RGB value is not in range 0-255\n"

typedef struct s_data	t_data;
typedef struct s_mlx	t_mlx;
typedef struct s_map	t_map;
typedef struct s_tex	t_tex;
typedef struct s_cam	t_cam;
typedef struct s_ray	t_ray;
typedef struct s_pix	t_pix;
typedef struct s_mini	t_mini;

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
	t_mlx	*player;
	t_mini	*mini;
	t_cam	*cam;
	t_map	*map;
};

/*
 * mlx		: pointer to the mlx context.
 * win		: pointer to the mlx window.
 * img		: pointer to image (XImage)
 * addr		: address of the image
 * bpp		: bits per pixel.
 * llen		: line length.
 * end		: endian type.
 * win_w	: window width
 * win_h 	: window height
*/
struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		llen;
	int		end;
	int		win_w;
	int		win_h;
};

/*
 * pos_x : camera's x position.
 * pos_y : camera's y position.
 * dir_x : camera's x direction vector.
 * dir_y : camera's y direction vector.
*/
struct s_cam
{
	int		key[6];
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	mospeed;
	double	rospeed;
	double	plane_x;
	double	plane_y;
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

struct s_mini
{
	t_mlx	*mlx;
	int		color;
	double	x_step;
	double	y_step;
};

struct s_tex
{
	void	*t;
	int		w;
	int		h;
	char	*addr;
	int		bpp;
	int		llen;
	int		end;
};

struct s_ray
{
	int		tex_n;
	int		side;
	int		step_x;
	int		step_y;
	int		map_x;
	int		map_y;
	double	dir_x;
	double	dir_y;
	double	sdist_x;
	double	sdist_y;
	double	ddist_x;
	double	ddist_y;
	double	perp_wall_dist;

};

struct s_pix
{
	int32_t		color;
	int			line_h;
	int			pitch;
	int			draw_start;
	int			draw_end;
	int			tex_n;
	int			tex_y;
	int			tex_x;
	double		wall_x;
	double		step;
	double		tex_pos;
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
void	get_player_dir(t_cam *cam, char c);
int		map_has_multiple_players(char **map, int x, int y);

void	setup_hooks(t_data *d);
int		hook_keypress(int key, t_data *d);
int		hook_keypress_release(int key, t_data *d);

int		move(t_data *d);
void	rotate_left(t_data *d);
void	rotate_right(t_data *d);

void	raycast(t_data *d, t_ray *r, int x);

int		draw_frame(t_data *d);
void	mlx_pixel_put_img(t_data *d, int x, int y, int color);

int mini_map(t_data *d);
int print_player(t_data *d);

#endif

