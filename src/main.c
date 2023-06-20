#include "cub3d.h"

static int draw_frame(t_data *d)
{
	for (int x = 0; x < d->mlx->win_w; x++)
	{
		ray_init(d, d->ray, x);
		dda(d, d->ray);

		// Calculate height of line to draw on screen
		int lineHeight = (int) (d->mlx->win_h / d->ray->perp_wall_dist);

		int pitch = 100;

		// calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + d->mlx->win_h / 2 + pitch;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + d->mlx->win_h / 2 + pitch;
		if (drawEnd >= d->mlx->win_h)
			drawEnd = d->mlx->win_h - 1;

		// texturing calculations
		int texNum = d->map->map[d->ray->map_x][d->ray->map_y] - 1; // 1 subtracted from it so that texture 0 can be used!

		// calculate value of wallX
		double wallX; // where exactly the wall was hit
		if (d->ray->side == 0)
			wallX = d->cam->pos_x + d->ray->perp_wall_dist * d->ray->dir_x;
		else
			wallX = d->cam->pos_y + d->ray->perp_wall_dist * d->ray->dir_y;
		wallX -= floor((wallX));

		// x coordinate on the texture
		int texX = (int) (wallX * (double) d->map->tex[N].w);
		if (d->ray->side == 0 && d->ray->dir_x > 0)
			texX = d->map->tex[N].w - texX - 1;
		if (d->ray->side == 1 && d->ray->dir_y < 0)
			texX = d->map->tex[N].w - texX - 1;

		// TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
		// How much to increase the texture coordinate per screen pixel
		double step = 1.0 * d->map->tex[N].h / lineHeight;
		// Starting texture coordinate
		double texPos = (drawStart - pitch - d->mlx->win_h / 2 + lineHeight / 2) * step;
		for (int y = drawStart; y < drawEnd; y++)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			int texY = (int) texPos & (d->map->tex[N].h - 1);
			texPos += step;
			// int32_t color = d->map->tex[N][d->map->tex[N].h * texY + texX];
			// int32_t *test = d->map->tex[N].t + 1; // rand() % 10; //+ (d->map->tex[N].h * texY + texX);
			int32_t color = 0;
			// make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			//	if (d->ray->side == 1)
			//	color = (color >> 1) & 8355711;
			mlx_pixel_put_img(d, x, y, color);
		}
		for (int y = 0; y < drawStart; y++)
			mlx_pixel_put_img(d, x, y, d->map->ceil);
		for (int y = d->mlx->win_h; y > drawEnd; y--)
			mlx_pixel_put_img(d, x, y, d->map->floor);
	}
	mlx_put_image_to_window(d->mlx->mlx, d->mlx->win, d->mlx->img, 0, 0);
/* 	for (int y = 0; y < d->mlx->win_h; y++)
	  for (int x = 0; x < d->mlx->win_w; x++)
		mlx_pixel_put_img(d, x, y, 0);; // clear the buffer instead of cls() */
}

static void print_debug_info(t_data *d)
{
	printf("--- PLAYER ---\n");
	printf("pos_x = %lf\npos_y = %lf\ndir_x = %lf\ndir_y = %lf\n\n",
	       d->cam->pos_x, d->cam->pos_y, d->cam->dir_x, d->cam->dir_y);
	printf("--- AREA ---\n");
	for (int i = 0; i < d->map->map_h; i++)
	{
		for (int j = 0; j < d->map->map_w; j++)
			printf("%d", d->map->map[i][j]);
		printf("\n");
	}
	printf("\n--- TEXTURES ---\n");
	printf("floor: %X, ceiling: %X\n", d->map->floor, d->map->ceil);
	printf("north : %p, %d, %d\n", d->map->tex[N].t, d->map->tex[N].w, d->map->tex[N].h);
	printf("south : %p, %d, %d\n", d->map->tex[S].t, d->map->tex[S].w, d->map->tex[S].h);
	printf("east : %p, %d, %d\n", d->map->tex[E].t, d->map->tex[E].w, d->map->tex[E].h);
	printf("west : %p, %d, %d\n", d->map->tex[W].t, d->map->tex[W].w, d->map->tex[W].h);
}

int main(int argc, char * argv[])
{
	t_data *d;

	if (argc != 2)
		return (f_dprintf(2, "Usage: ./cub3d map.cub\n"), EXIT_SUCCESS);
	d = data_init(argv[1]);
	if (!d)
		return (EXIT_FAILURE);
	d->ray = malloc(1 * sizeof(t_ray));
	print_debug_info(d);
	mlx_loop_hook(d->mlx->mlx, draw_frame, d);
	setup_hooks(d);
	mlx_loop(d->mlx->mlx);
	return (0);
}
