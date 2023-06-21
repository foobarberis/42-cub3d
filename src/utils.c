#include "cub3d.h"

/*
* From : https://tronche.com/gui/x/xlib/utilities/manipulating-images.html
* "The first byte of the first line of plane n must be located at the
* address (data + (n * height * bytes_per_line))."
*/
void	mlx_pixel_put_img(t_data *d, int x, int y, int color)
{
	char	*dst;

	dst = d->mlx->addr + (y * d->mlx->llen + x * (d->mlx->bpp / 8));
	*(unsigned int *)dst = color;
}

void	setup_hooks(t_data *d)
{
	mlx_hook(d->mlx->win, KeyPress, KeyPressMask, hook_keypress, d);
	mlx_hook(d->mlx->win, KeyRelease, KeyReleaseMask, hook_keypress_release, d);
	mlx_hook(d->mlx->win, DestroyNotify, NoEventMask, cub_exit, d);
	mlx_hook(d->mlx->win, Expose, ExposureMask, draw_frame, d);
}
