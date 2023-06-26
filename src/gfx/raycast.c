/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 13:12:32 by mbarberi          #+#    #+#             */
/*   Updated: 2023/06/26 13:25:58 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_step(t_data *d, t_ray *r)
{
	if (r->dir_x < 0)
	{
		r->step_x = -1;
		r->sdist_x = (d->cam->pos_x - r->map_x) * r->ddist_x;
	}
	else
	{
		r->step_x = 1;
		r->sdist_x = (r->map_x + 1.0 - d->cam->pos_x) * r->ddist_x;
	}
	if (r->dir_y < 0)
	{
		r->step_y = -1;
		r->sdist_y = (d->cam->pos_y - r->map_y) * r->ddist_y;
	}
	else
	{
		r->step_y = 1;
		r->sdist_y = (r->map_y + 1.0 - d->cam->pos_y) * r->ddist_y;
	}
}

static void	pick_texture(t_ray *r)
{
	r->tex_n = 0;
	if (r->side)
	{
		if (r->step_y > 0)
			r->tex_n = N;
		else if (r->step_y < 0)
			r->tex_n = S;
	}
	else if (!r->side)
	{
		if (r->step_x > 0)
			r->tex_n = E;
		else if (r->step_x < 0)
			r->tex_n = W;
	}
}

static void	dda(t_data *d, t_ray *r)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (r->sdist_x < r->sdist_y)
		{
			r->sdist_x += r->ddist_x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->sdist_y += r->ddist_y;
			r->map_y += r->step_y;
			r->side = 1;
		}
		if (d->map->map[r->map_x][r->map_y] > 0)
			hit = 1;
	}
	if (!r->side)
		r->perp_wall_dist = (r->sdist_x - r->ddist_x);
	else
		r->perp_wall_dist = (r->sdist_y - r->ddist_y);
	pick_texture(r);
}

void	raycast(t_data *d, t_ray *r, int x)
{
	double	cam_x;

	cam_x = 2 * x / (double) d->mlx->win_w - 1;
	r->dir_x = d->cam->dir_x + d->cam->plane_x * cam_x;
	r->dir_y = d->cam->dir_y + d->cam->plane_y * cam_x;
	r->map_x = (int) d->cam->pos_x;
	r->map_y = (int) d->cam->pos_y;
	if (!r->dir_x)
		r->ddist_x = INFINITY;
	else
		r->ddist_x = fabs(1 / r->dir_x);
	if (!r->dir_y)
		r->ddist_y = INFINITY;
	else
		r->ddist_y = fabs(1 / r->dir_y);
	init_step(d, r);
	dda(d, r);
}
