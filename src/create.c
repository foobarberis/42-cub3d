/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 13:28:50 by mbarberi          #+#    #+#             */
/*   Updated: 2023/06/26 13:29:34 by mbarberi         ###   ########.fr       */
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
	d->mini = f_calloc(1, sizeof(t_mini));
	if (!d->mini)
		return (free(d->map), free(d->cam), free(d->mlx), free(d), NULL);
	d->player = f_calloc(1, sizeof(t_player));
	if (!d->mini)
		return (free(d->mini), free(d->map), free(d->cam), free(d->mlx), free(d), NULL);
	d->map->tex = f_calloc(4, sizeof(t_tex));
	if (!d->map->tex)
		return (free(d->cam), free(d->mlx), free(d->map), free(d), NULL);
	return (d);
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

static int minimap_setup(t_data *d)
{
	d->mini->mlx = f_calloc(1, sizeof(t_mlx));
	if (!d->mini->mlx)
		return (free(d), NULL);
	d->mini->mlx->mlx = d->mlx->mlx;
	d->mini->mlx->win = d->mlx->win;
	d->mini->mlx->win_w = WINDOW_WIDTH / R_MAP;
	d->mini->mlx->win_h = WINDOW_HEIGHT / R_MAP;
	d->mini->mlx->img = mlx_new_image(d->mini->mlx->mlx, d->mini->mlx->win_w, d->mini->mlx->win_h);
	if (!(d->mini->mlx->win) || !(d->mini->mlx->img))
		return (1);
	d->mini->mlx->addr = mlx_get_data_addr(d->mini->mlx->img, &d->mini->mlx->bpp, &d->mini->mlx->llen, &d->mini->mlx->end);
	return (0);
}

static int player_setup(t_data *d)
{
	d->player->mlx = f_calloc(1, sizeof(t_mlx));
	if (!d->player->mlx)
		return (free(d), NULL);
	d->player->mlx->mlx = d->mlx->mlx;
	d->player->mlx->win = d->mlx->win;
	d->player->mlx->win_w = 5;
	d->player->mlx->win_h = 5;
	d->player->mlx->img = mlx_new_image(d->player->mlx->mlx, d->player->mlx->win_w, d->player->mlx->win_h);
	if (!(d->player->mlx->win) || !(d->player->mlx->img))
		return (1);
	d->player->mlx->addr = mlx_get_data_addr(d->player->mlx->img, &d->player->mlx->bpp, &d->player->mlx->llen, &d->player->mlx->end);
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
	if (mlx_setup(d))
		return (data_destroy(d), NULL);
	if (minimap_setup(d))
		return (data_destroy(d), NULL);
	if (player_setup(d))
		return (data_destroy(d), NULL);
	if (parsing(d, file))
		return (data_destroy(d), NULL);
	mini_map(d);
	return (d);
}
