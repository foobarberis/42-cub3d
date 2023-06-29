/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 13:28:50 by mbarberi          #+#    #+#             */
/*   Updated: 2023/06/29 10:48:37 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_data	*data_create(void)
{
	t_data	*d;

	d = f_calloc(1, sizeof(t_data));
	if (!d)
		return (NULL);
	d->mlx = f_calloc(1, sizeof(t_mlx));
	if (!d->mlx)
		return (free(d), NULL);
	d->cam = f_calloc(1, sizeof(t_cam));
	if (!d->cam)
		return (free(d->mlx), free(d), NULL);
	d->map = f_calloc(1, sizeof(t_map));
	if (!d->map)
		return (free(d->cam), free(d->mlx), free(d), NULL);
	d->minimap = f_calloc(1, sizeof(t_mlx));
	if (!d->minimap)
		return (free(d->map), free(d->cam), free(d->mlx), free(d), NULL);
	return (data_create_next(d));
}

static int	mlx_setup(t_data *d)
{
	d->mlx->win_w = WINDOW_WIDTH;
	d->mlx->win_h = WINDOW_HEIGHT;
	d->mlx->mlx = mlx_init();
	if (!(d->mlx->mlx))
		return (1);
	d->mlx->win = mlx_new_window(d->mlx->mlx, d->mlx->win_w,
			d->mlx->win_h, "cub3D");
	d->mlx->img = mlx_new_image(d->mlx->mlx, d->mlx->win_w, d->mlx->win_h);
	if (!(d->mlx->win) || !(d->mlx->img))
		return (1);
	d->mlx->addr = mlx_get_data_addr(d->mlx->img, &d->mlx->bpp,
			&d->mlx->llen, &d->mlx->end);
	return (0);
}

static int	minimap_setup(t_data *d)
{
	d->minimap->win_w = WINDOW_WIDTH / R_MAP;
	d->minimap->win_h = WINDOW_HEIGHT / R_MAP;
	d->player->win_w = 6;
	d->player->win_h = 6;
	d->minimap->img = mlx_new_image(d->mlx->mlx, d->minimap->win_w,
			d->minimap->win_h);
	d->player->img = mlx_new_image(d->mlx->mlx, d->player->win_w,
			d->player->win_h);
	if (!(d->player->img) || !(d->minimap->img))
		return (1);
	d->player->addr = mlx_get_data_addr(d->player->img, &d->player->bpp,
			&d->player->llen, &d->player->end);
	d->minimap->addr = mlx_get_data_addr(d->minimap->img, &d->minimap->bpp,
			&d->minimap->llen, &d->minimap->end);
	return (0);
}

int	**matrix_create(int w, int h)
{
	int	i;
	int	**new;

	i = 0;
	new = f_calloc(h, sizeof(int *));
	if (!new)
		return (NULL);
	while (i < h)
	{
		new[i] = f_calloc(w, sizeof(int *));
		if (!new[i])
			matrix_destroy(new, i);
		i++;
	}
	return (new);
}

t_data	*data_init(char *file)
{
	t_data	*d;

	d = data_create();
	if (!d)
		return (NULL);
	d->map->floor = -1;
	d->map->ceil = -1;
	if (mlx_setup(d))
		return (data_destroy(d), NULL);
	if (minimap_setup(d))
		return (data_destroy(d), NULL);
	if (parsing(d, file))
		return (data_destroy(d), NULL);
	mini_map(d);
	return (d);
}
