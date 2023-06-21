#include "cub3d.h"

static void move_forward(t_data *d)
{
	if (d->map->map[(int) (d->cam->pos_x + d->cam->dir_x * d->cam->mospeed)][(int) d->cam->pos_y] == 0)
		d->cam->pos_x += d->cam->dir_x * d->cam->mospeed;
	if (d->map->map[(int) d->cam->pos_x][(int) (d->cam->pos_y + d->cam->dir_y * d->cam->mospeed)] == 0)
		d->cam->pos_y += d->cam->dir_y * d->cam->mospeed;
}

static void move_backward(t_data *d)
{
	if (d->map->map[(int) (d->cam->pos_x - d->cam->dir_x * d->cam->mospeed)][(int) d->cam->pos_y] == 0)
		d->cam->pos_x -= d->cam->dir_x * d->cam->mospeed;
	if (d->map->map[(int) d->cam->pos_x][(int) (d->cam->pos_y - d->cam->dir_y * d->cam->mospeed)] == 0)
		d->cam->pos_y -= d->cam->dir_y * d->cam->mospeed;
}

static void move_left(t_data *d)
{
	if (d->map->map[(int) (d->cam->pos_x - d->cam->plane_x * d->cam->mospeed)][(int) d->cam->pos_y] == 0)
		d->cam->pos_x -= d->cam->plane_x * d->cam->mospeed;
	if (d->map->map[(int) d->cam->pos_x][(int) (d->cam->pos_y - d->cam->plane_y * d->cam->mospeed)] == 0)
		d->cam->pos_y -= d->cam->plane_y * d->cam->mospeed;
}

static void move_right(t_data *d)
{
	if (d->map->map[(int) (d->cam->pos_x + d->cam->plane_x * d->cam->mospeed)][(int) d->cam->pos_y] == 0)
		d->cam->pos_x += d->cam->plane_x * d->cam->mospeed;
	if (d->map->map[(int) d->cam->pos_x][(int) (d->cam->pos_y + d->cam->plane_y * d->cam->mospeed)] == 0)
		d->cam->pos_y += d->cam->plane_y * d->cam->mospeed;
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
	return (0);
}
