#include "cub3d.h"

void	my_pixel_put(t_player *player, double x, double y)
{
	int	*dst;

	dst = (int *)player->mlx->addr;
	dst[(int)y + (int)x] = 0xFF0000; //player->color;
}

int print_player(t_data *d)
{
	double	i;
	double	j;
	double x;
	double y;

	i = 0;
	x = d->cam->pos_x * d->mini->y_step - 5;
	y = d->cam->pos_y * d->mini->x_step - 5;
	while (i < 5 * (int)d->mini->x_step)
	{
		j = 0;
		while(j < 5 * (int)d->mini->y_step)
		{
			my_pixel_put(d->player, i, j);
			j += 1;
		}
		i += 1;
	}
	mlx_put_image_to_window(d->mlx->mlx, d->mlx->win, d->player->mlx->img, (int)y, (int)x);
	return (0);
}
