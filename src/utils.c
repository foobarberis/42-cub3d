#include "cub3d.h"

void	mlx_pixel_put_img(t_data *d, int x, int y, int color)
{
	char	*dst;

	dst = d->mlx->addr + (y * d->mlx->llen + x * (d->mlx->bpp / 8));
	*(unsigned int *)dst = color;
}

void	setup_hooks(t_data *d)
{
	mlx_hook(d->mlx->win, 2, 1L << 0, hook_keypress, d);
	mlx_hook(d->mlx->win, 3, 2L << 0, hook_keypress_release, d);
	// mlx_key_hook(d->mlx->win, hook_keypress, d);
	mlx_hook(d->mlx->win, DestroyNotify, NoEventMask, cub_exit, d);
	// mlx_hook(env->win, Expose, ExposureMask, map_draw, env);
}
