#include "cub3d.h"

int hook_keypress_release(int key, t_data *d)
{
	 if (key == XK_w)
		d->cam->key[K_W] = 0;
	else if (key == XK_s)
		d->cam->key[K_S] = 0;
	else if (key == XK_a)
		d->cam->key[K_A] = 0;
	else if (key == XK_d)
		d->cam->key[K_D] = 0;
	else if (key == XK_Left)
		d->cam->key[K_L] = 0;
	else if (key == XK_Right)
		d->cam->key[K_R] = 0;
	return (0);
}

int hook_keypress(int key, t_data *d)
{
	if (key == XK_Escape)
		cub_exit(d, EXIT_SUCCESS);
	else if (key == XK_w)
		d->cam->key[K_W] = 1;
	else if (key == XK_s)
		d->cam->key[K_S] = 1;
	else if (key == XK_a)
		d->cam->key[K_A] = 1;
	else if (key == XK_d)
		d->cam->key[K_D] = 1;
	else if (key == XK_Left)
		d->cam->key[K_L] = 1;
	else if (key == XK_Right)
		d->cam->key[K_R] = 1;
	return (0);
}
