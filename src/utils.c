#include "cub3d.h"


static void	mlx_pixel_put_img(t_data *env, int x, int y, int color)
{
	char	*dst;

	dst = env->addr + (y * env->llen + x * (env->bpp / 8));
	*(unsigned int *)dst = color;
}

int	fdf_exit(t_data *env)
{
	mlx_loop_end(env->mlx);
	mlx_destroy_image(env->mlx, env->img);
	env->img = NULL;
	mlx_destroy_window(env->mlx, env->win);
	env->win = NULL;
	mlx_destroy_display(env->mlx);
	free(env->mlx);
	env->mlx = NULL;
	// matrix_destroy(env->m, env->ymap);
	free(env);
	env = NULL;
	exit(EXIT_SUCCESS);
}

void	fdf_setup_hooks(t_data *env)
{
	mlx_key_hook(env->win, fdf_hook_keypress, env);
	mlx_hook(env->win, DestroyNotify, NoEventMask, fdf_exit, env);
	//mlx_hook(env->win, Expose, ExposureMask, map_draw, env);
}
