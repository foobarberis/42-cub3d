#include "cub3d.h"

static int  ft_color(t_data *d, double x, double y)
{
    int     color;
    if (d->map->map[(int)y][(int)x])
        color = 0x00000000;
    else
        color = 0x00FFFFFF;
    return (color);
}

static void algo_draw_line(t_data *d, double x, double y)
{
	int	i;
	int	j;
	double mini_x;
	double mini_y;

	i = 0;
    mini_x = x * d->mini->x_step;
    mini_y = y * d->mini->y_step;
    d->mini->color = ft_color(d, x, y);
    while (i < d->mini->x_step)
    {
		j = 0;
        while(j < d->mini->y_step)
        {
            mlx_pixel_put_img(d->mini->mlx, (int)(i + mini_x), (int)(j + mini_y), d->mini->color);
            j += 1;
        }
        i += 1;
    }
}

int mini_map(t_data *d)
{
    double x;
    double y;


    x = 0;
    d->mini->x_step = (double)d->mini->mlx->win_w / (double)d->map->map_w;
    d->mini->y_step = (double)d->mini->mlx->win_h / (double)d->map->map_h;
    while ((int)x < d->map->map_h)
    {
        y = 0;
        while ((int)y < d->map->map_w)
        {
            if ((int)x < d->map->map_h)
                algo_draw_line(d, y, x);
            y++;
        }
        x++;
    }
    return (0);
}
