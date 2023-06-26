#include "cub3d.h"

static t_data *data_create(void)
{
	t_data	*d;

	d = f_calloc(1, sizeof(t_data));
	if (!d)
		return (NULL);
	d->mlx = f_calloc(1, sizeof(t_mlx));
	if (!d->mlx)
		return (free(d), NULL);
	d->cam = f_calloc(1, sizeof(t_cam));
	if (!d->cam)
		return (free(d->mlx), free(d), NULL);
	d->map = f_calloc(1, sizeof(t_map));
	if (!d->map)
		return (free(d->cam), free(d->mlx), free(d), NULL);
	d->map->tex = f_calloc(4, sizeof(t_tex));
		if (!d->map->tex)
		return (free(d->cam), free(d->mlx), free(d->map), free(d), NULL);
	return (d);
}

static int mlx_setup(t_data *d)
{
	d->mlx->win_w = WINDOW_WIDTH;
	d->mlx->win_h = WINDOW_HEIGHT;
	d->mlx->mlx = mlx_init();
	if (!(d->mlx->mlx))
		return (1);
	d->mlx->win = mlx_new_window(d->mlx->mlx, d->mlx->win_w, d->mlx->win_h, "cub3D");
	d->mlx->img = mlx_new_image(d->mlx->mlx, d->mlx->win_w, d->mlx->win_h);
	if (!(d->mlx->win) || !(d->mlx->img))
		return (1);
	d->mlx->addr = mlx_get_data_addr(d->mlx->img, &d->mlx->bpp, &d->mlx->llen, &d->mlx->end);
	return (0);
}

int **matrix_create(int w, int h)
{
	int i;
	int **new;

	i = 0;
	new = f_calloc(h, sizeof(int *));
	if (!new)
		return (NULL);
	while (i < h)
	{
		new[i] = f_calloc(w, sizeof(int *));
		if (!new[i])
			matrix_destroy(new, i);
		i++;
	}
	return (new);
}

t_data *data_init(char *file)
{
	t_data	*d;

	d = data_create();
	if (!d)
		return (NULL);
	if (mlx_setup(d))
		return (data_destroy(d), NULL);
	/* FIXME: Find better formula */
	d->cam->mospeed = (double)(WINDOW_HEIGHT * WINDOW_WIDTH) / 6400000.00; // 0.075;
	d->cam->rospeed = (double)(WINDOW_HEIGHT * WINDOW_WIDTH) / 6400000.00; // 0.075;
	parsing(d, file);
	return (d);
}
