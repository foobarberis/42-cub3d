#include "cub3d.h"

void data_destroy(t_data *d)
{
	if (!d)
		return;
	if (d->map)
		map_destroy(d, d->map);
	if (d->mlx)
		mlx_destroy(d->mlx);
	if (d->cam)
		free(d->cam);
	free(d);
}

void mlx_destroy(t_mlx *mlx)
{
	mlx_loop_end(mlx->mlx);
	if (mlx->win)
		mlx_destroy_window(mlx->mlx, mlx->win);
	if (mlx->img)
		mlx_destroy_image(mlx->mlx, mlx->img);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
	free(mlx);
}

void map_destroy(t_data *d, t_map *map)
{
	int i;

	i = 0;
	if (map->map)
	{
		while (i < map->map_h)
			free(map->map[i++]);
		free(map->map);
	}
	i = 0;
	while (i < 4)
		if (map->tex[i])
			mlx_destroy_image(d->mlx->mlx, map->tex[i++]);
	free(map);
}

void matrix_destroy(int **m, int h)
{
	int i;

	i = 0;
	while (i < h)
		free(m[i++]);
	free(m);
}

int	cub_exit(t_data *d, int code)
{
	data_destroy(d);
	exit(code);
	return (0);
}
