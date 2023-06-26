#include "cub3d.h"

static void	my_pixel_put(t_mini *mini)
{
	int	*dst;

	dst = (int *)mini->mlx->addr;
	dst[(int)mini->y * WINDOW_WIDTH / R_MAP + (int)mini->x] = mini->color;
}

static int	ft_color(t_data *d, double x, double y, double i, double j)
{
	int		color;
	if (d->map->map[(int)y][(int)x])
		color = 0x00000000;
	else
		color = 0x00FFFFFF;
	return (color);
}

static void	algo_draw_line(t_data *d, double x, double y, double i, double j)
{
	d->mini->x = x * d->mini->x_step;
	d->mini->y = y * d->mini->y_step;
	d->mini->x1 = (x + 1) * d->mini->x_step;
	d->mini->y1 = (y + 1) * d->mini->y_step;
	while ((d->mini->x - d->mini->x1) < 0)
	{
		d->mini->y = y * d->mini->y_step;
		while((d->mini->y - d->mini->y1) < 0)
		{
			d->mini->color = ft_color(d, x, y, i, j);
			my_pixel_put(d->mini);
			d->mini->y += 1;
		}
		d->mini->x += 1;
	}
}

int mini_map(t_data *d)
{
	double x;
	double y;
	double i;
	double j;

	x = 0;
	d->mini->x_step = (double)d->mini->mlx->win_w / (double)d->map->map_w;
	d->mini->y_step = (double)d->mini->mlx->win_h / (double)d->map->map_h;
	j = d->cam->pos_y * d->mini->x_step;
	i = d->cam->pos_x * d->mini->y_step;
	while ((int)x < d->map->map_h)
	{
		y = 0;
		while ((int)y < d->map->map_w)
		{
			if ((int)x < d->map->map_h)
				algo_draw_line(d, y, x, i, j);
			y++;
		}
		x++;
	}
	return (0);
}