#include "cub3d.h"

static int  ft_color(t_data *d, double x, double y)
{
    if (d->map->map[(int)y][(int)x])
        return (0x00000000);
    else
        return (0x00FFFFFF);
}

int print_player(t_data *d)
{
	double	i;
	double	j;
	double	x;
	double	y;

	i = 0;
	x = d->cam->pos_y * d->x_step - 2;
	y = d->cam->pos_x * d->y_step - 2;
	while (i < 5 * (int)d->x_step)
	{
		j = 0;
		while(j < 5 * (int)d->y_step)
		{
			mlx_pixel_put_img(d->player, (int)i, (int)j, 0xFF0000);
			j += 1;
		}
		i += 1;
	}
	mlx_put_image_to_window(d->mlx->mlx, d->mlx->win, d->player->img, (int)x, (int)y);
	return (0);
}

static void algo_draw_line(t_data *d, double x, double y)
{
	int	i;
	int	j;
	int color;
	double mini_x;
	double mini_y;

	i = 0;
	mini_x = x * d->x_step;
	mini_y = y * d->y_step;
	color = ft_color(d, x, y);
    while (i < d->x_step)
    {
		j = 0;
        while(j < d->y_step)
        {
            mlx_pixel_put_img(d->minimap, (int)(i + mini_x), (int)(j + mini_y), color);
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
    d->x_step = (double)d->minimap->win_w / (double)d->map->map_w;
    d->y_step = (double)d->minimap->win_h / (double)d->map->map_h;
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
