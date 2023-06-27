/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 13:32:52 by mbarberi          #+#    #+#             */
/*   Updated: 2023/06/27 10:44:57 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mlx_pixel_put_img(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->llen + (x << 2));
	*(unsigned int *)dst = color;
}

void	setup_hooks(t_data *d)
{
	mlx_hook(d->mlx->win, KeyPress, KeyPressMask, hook_keypress, d);
	mlx_hook(d->mlx->win, KeyRelease, KeyReleaseMask, hook_keypress_release, d);
	mlx_hook(d->mlx->win, DestroyNotify, NoEventMask, cub_exit, d);
	mlx_hook(d->mlx->win, Expose, ExposureMask, draw_frame, d);
}
