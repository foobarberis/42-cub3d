#include "cub3d.h"

int print_player(t_data *d)
{
	double	i;
	double	j;
	double x;
	double y;

	i = 0;
	x = d->cam->pos_y * d->mini->x_step - 2;
	y = d->cam->pos_x * d->mini->y_step - 2;
	while (i < 5 * (int)d->mini->x_step)
	{
		j = 0;
		while(j < 5 * (int)d->mini->y_step)
		{
			mlx_pixel_put_img(d->player, (int)i, (int)j, 0xFF0000);
			j += 1;
		}
		i += 1;
	}
	mlx_put_image_to_window(d->mlx->mlx, d->mlx->win, d->player->img, (int)x, (int)y);
	return (0);
}
