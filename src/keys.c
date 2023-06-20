#include "cub3d.h"
#include <stdbool.h>

/* FIXME: Combine rotate, strafe and move in 3 functions */

static void rotate_right(t_data *d)
{
	// both camera direction and camera plane must be rotated

	double oldDirX = d->cam->dir_x;
	d->cam->dir_x = d->cam->dir_x * cos(-d->cam->rospeed) - d->cam->dir_y * sin(-d->cam->rospeed);
	d->cam->dir_y = oldDirX * sin(-d->cam->rospeed) + d->cam->dir_y * cos(-d->cam->rospeed);
	double oldPlaneX = d->cam->plane_x;
	d->cam->plane_x = d->cam->plane_x * cos(-d->cam->rospeed) - d->cam->plane_y * sin(-d->cam->rospeed);
	d->cam->plane_y = oldPlaneX * sin(-d->cam->rospeed) + d->cam->plane_y * cos(-d->cam->rospeed);
}

static void rotate_left(t_data *d)
{
	// both camera direction and camera plane must be rotated
	double oldDirX = d->cam->dir_x;
	d->cam->dir_x = d->cam->dir_x * cos(d->cam->rospeed) - d->cam->dir_y * sin(d->cam->rospeed);
	d->cam->dir_y = oldDirX * sin(d->cam->rospeed) + d->cam->dir_y * cos(d->cam->rospeed);
	double oldPlaneX = d->cam->plane_x;
	d->cam->plane_x = d->cam->plane_x * cos(d->cam->rospeed) - d->cam->plane_y * sin(d->cam->rospeed);
	d->cam->plane_y = oldPlaneX * sin(d->cam->rospeed) + d->cam->plane_y * cos(d->cam->rospeed);
}

static void move_forward(t_data *d)
{
	if (d->map->map[(int) (d->cam->pos_x + d->cam->dir_x * d->cam->mospeed)][(int) d->cam->pos_y] == false)
		d->cam->pos_x += d->cam->dir_x * d->cam->mospeed;
	if (d->map->map[(int) d->cam->pos_x][(int) (d->cam->pos_y + d->cam->dir_y * d->cam->mospeed)] == false)
		d->cam->pos_y += d->cam->dir_y * d->cam->mospeed;
}

static void move_backward(t_data *d)
{
	if (d->map->map[(int) (d->cam->pos_x - d->cam->dir_x * d->cam->mospeed)][(int) d->cam->pos_y] == false)
		d->cam->pos_x -= d->cam->dir_x * d->cam->mospeed;
	if (d->map->map[(int) d->cam->pos_x][(int) (d->cam->pos_y - d->cam->dir_y * d->cam->mospeed)] == false)
		d->cam->pos_y -= d->cam->dir_y * d->cam->mospeed;
}

static void move_left(t_data *d)
{
	if (d->map->map[(int) (d->cam->pos_x - d->cam->dir_x * d->cam->mospeed)][(int) d->cam->pos_y] == false)
		d->cam->pos_x -= d->cam->dir_x * d->cam->mospeed;
	if (d->map->map[(int) d->cam->pos_x][(int) (d->cam->pos_y - d->cam->dir_y * d->cam->mospeed)] == false)
		d->cam->pos_y -= d->cam->dir_y * d->cam->mospeed;
}

static void move_right(t_data *d)
{
	if (d->map->map[(int) (d->cam->pos_x - d->cam->dir_x * d->cam->mospeed)][(int) d->cam->pos_y] == false)
		d->cam->pos_x -= d->cam->dir_x * d->cam->mospeed;
	if (d->map->map[(int) d->cam->pos_x][(int) (d->cam->pos_y - d->cam->dir_y * d->cam->mospeed)] == false)
		d->cam->pos_y -= d->cam->dir_y * d->cam->mospeed;
}

int move(t_data *d)
{
	if (d->cam->key[K_W])
		move_forward(d);
	if (d->cam->key[K_S])
		move_backward(d);
	if (d->cam->key[K_A])
		move_left(d);
	if (d->cam->key[K_D])
		move_right(d);
	if (d->cam->key[K_L])
		rotate_left(d);
	if (d->cam->key[K_R])
		rotate_right(d);
	return 0;
}

int hook_keypress_release(int key, t_data *d)
{
	 if (key == XK_w)
		d->cam->key[K_W] = 0;
	else if (key == XK_s)
		d->cam->key[K_S] = 0;
	else if (key == XK_a)
		d->cam->key[K_A] = 0;
	else if (key == XK_d)
		d->cam->key[K_D] = 0;
	else if (key == XK_Left)
		d->cam->key[K_L] = 0;
	else if (key == XK_Right)
		d->cam->key[K_R] = 0;
	return (0);
}

int hook_keypress(int key, t_data *d)
{
	if (key == XK_Escape)
		cub_exit(d, EXIT_SUCCESS);
	else if (key == XK_w)
		d->cam->key[K_W] = 1;
	else if (key == XK_s)
		d->cam->key[K_S] = 1;
	else if (key == XK_a)
		d->cam->key[K_A] = 1;
	else if (key == XK_d)
		d->cam->key[K_D] = 1;
	else if (key == XK_Left)
		d->cam->key[K_L] = 1;
	else if (key == XK_Right)
		d->cam->key[K_R] = 1;
	return (0);
}

/* int hook_keypress(int key, t_data *d)
{
	if (key == XK_Escape)
		cub_exit(d, EXIT_SUCCESS);
	else if (key == XK_w)
		move_forward(d);
	else if (key == XK_s)
		move_backward(d);
	else if (key == XK_a)
		move_left(d);
	else if (key == XK_d)
		move_right(d);
	else if (key == XK_Left)
		rotate_right(d);
	else if (key == XK_Right)
		rotate_left(d);
	return (0);
} */
