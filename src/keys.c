#include "cub3d.h"
#include <stdbool.h>

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

int hook_keypress(t_data *d, int key)
{
	if (key == XK_Escape)
		cub_exit(d, EXIT_SUCCESS);
	else if (key == XK_Up)
		move_forward(d);
	else if (key == XK_Down)
		move_backward(d);
	else if (key == XK_Right)
		rotate_right(d);
	else if (key == XK_Left)
		rotate_left(d);
	return (0);
}
