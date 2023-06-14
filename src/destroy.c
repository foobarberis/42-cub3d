#include "cub3d.h"

void data_destroy(t_data *d)
{
	if (!d)
		return ;
	if (d->mlx)
		mlx_destroy(d->mlx);
	if (d->map)
		map_destroy(d->map);
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

void map_destroy(t_map *map)
{
	int i;

	i = 0;
	if (map->map)
	{
		while (i < map->map_h)
			free(map->map[i++]);
		free(map->map);
	}
	free(map);
}

int	cub_exit(t_data *d, int code)
{
	data_destroy(d);
	exit(code);
	return (0);
}
