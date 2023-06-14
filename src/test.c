#include "cub3d.h"

int main(int argc, char **argv)
{
	t_data *d;

	if (argc != 2)
		return (f_dprintf(2, "Usage: ./cub3d map.cub\n"), EXIT_SUCCESS);
	d = data_create(argv[1]);
	if (!d)
		return (EXIT_FAILURE);
	setup_hooks(d);
	mlx_loop(d->mlx->mlx);
	return (EXIT_SUCCESS);
}
