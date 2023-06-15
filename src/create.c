#include "cub3d.h"

t_data *data_create(void)
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
	return (d);
}

t_data *data_init(char *file)
{
	t_data	*d;

	d = data_create();
	if (!d)
		return (NULL);
	if (mlx_setup(d))
		return (data_destroy(d), NULL);
	map_parsing(d);
	return (d);
}

int mlx_setup(t_data *d)
{
	d->mlx->win_w = WINDOW_WIDTH;
	d->mlx->win_h = WINDOW_HEIGHT;
	d->mlx->mlx = mlx_init();
	if (!(d->mlx->mlx))
		return (free(d->mlx), 1);
	d->mlx->win = mlx_new_window(d->mlx->mlx, d->mlx->win_w, d->mlx->win_h, "cub3D");
	d->mlx->img = mlx_new_image(d->mlx->mlx, d->mlx->win_w, d->mlx->win_h);
	if (!(d->mlx->win) || !(d->mlx->img))
		return (mlx_destroy(d->mlx), 1);
	d->mlx->addr = mlx_get_data_addr(d->mlx->img, &d->mlx->bpp, &d->mlx->llen, &d->mlx->end);
	return (0);
}

