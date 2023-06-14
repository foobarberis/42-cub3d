#include "cub3d.h"

t_data *data_create(char *file)
{
	t_data	*d;

	d = malloc(sizeof(t_data));
	if (!d)
		return (NULL);
	d->map = map_create(file);
	if (!d->map)
		return (data_destroy(d), NULL);
	d->cam = cam_create(d);
	if (!d->cam)
		return (data_destroy(d), NULL);
	d->mlx = mlx_create();
	if (!d->mlx)
		return (data_destroy(d), NULL);
	return (d);
}

t_mlx *mlx_create(void)
{
	t_mlx *mlx;

	mlx = malloc(sizeof(t_mlx));
	if (!mlx)
		return (NULL);
	mlx->win_w = WINDOW_WIDTH;
	mlx->win_h = WINDOW_HEIGHT;
	mlx->mlx = mlx_init();
	if (!(mlx->mlx))
		return (free(mlx), NULL);
	mlx->win = mlx_new_window(mlx->mlx, mlx->win_w, mlx->win_h, "cub3D");
	mlx->img = mlx_new_image(mlx->mlx, mlx->win_w, mlx->win_h);
	if (!(mlx->win) || !(mlx->img))
		return (mlx_destroy(mlx), NULL);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->llen, &mlx->end);
	return (mlx);
}

/* FIXME: Use values extracted from the map for pos and dir */
t_cam *cam_create(t_data *d)
{
	t_cam *cam;

	cam = malloc(sizeof(t_cam));
	if (!cam)
		return (NULL);
	cam->pos_x = 22.0;
	cam->pos_y = 11.5;
	cam->dir_x = 1.0;
	cam->dir_y = 0.0;
	cam->plane_x = 0.0;
	cam->plane_y = 0.66;
	return (cam);
}

t_map *map_create(char *file)
{
	t_map *map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	return (map);
}
