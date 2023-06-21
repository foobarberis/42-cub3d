#include "cub3d.h"

static void print_debug_info(t_data *d)
{
	printf("--- PLAYER ---\n");
	printf("pos_x = %lf\npos_y = %lf\ndir_x = %lf\ndir_y = %lf\n\n",
	       d->cam->pos_x, d->cam->pos_y, d->cam->dir_x, d->cam->dir_y);
	printf("--- AREA ---\n");
	for (int i = 0; i < d->map->map_h; i++)
	{
		for (int j = 0; j < d->map->map_w; j++)
			printf("%d", d->map->map[i][j]);
		printf("\n");
	}
	printf("\n--- TEXTURES ---\n");
	printf("floor: %X, ceiling: %X\n", d->map->floor, d->map->ceil);
	printf("north : %p, %d, %d\n", d->map->tex[N].t, d->map->tex[N].w, d->map->tex[N].h);
	printf("south : %p, %d, %d\n", d->map->tex[S].t, d->map->tex[S].w, d->map->tex[S].h);
	printf("east : %p, %d, %d\n", d->map->tex[E].t, d->map->tex[E].w, d->map->tex[E].h);
	printf("west : %p, %d, %d\n", d->map->tex[W].t, d->map->tex[W].w, d->map->tex[W].h);
}

int main(int argc, char * argv[])
{
	t_data *d;

	if (argc != 2)
		return (f_dprintf(2, "Usage: ./cub3d map.cub\n"), EXIT_SUCCESS);
	d = data_init(argv[1]);
	if (!d)
		return (EXIT_FAILURE);
	print_debug_info(d);
	mlx_loop_hook(d->mlx->mlx, draw_frame, d);
	setup_hooks(d);
	mlx_loop(d->mlx->mlx);
	return (0);
}
