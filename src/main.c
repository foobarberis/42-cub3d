#include "cub3d.h"

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
	printf("north : %p, %d, %d\n", d->map->tex[N], d->map->tex[N].w, d->map->tex[N].h);
	printf("south : %p, %d, %d\n", d->map->tex[S], d->map->tex[S].w, d->map->tex[S].h);
	printf("east : %p, %d, %d\n", d->map->tex[E], d->map->tex[E].w, d->map->tex[E].h);
	printf("west : %p, %d, %d\n", d->map->tex[W], d->map->tex[W].w, d->map->tex[W].h);
}

int main(int argc, char **argv)
{
	t_data *d;

	if (argc != 2)
		return (f_dprintf(2, "Usage: ./cub3d map.cub\n"), EXIT_SUCCESS);
	d = data_init(argv[1]);
	if (!d)
		return (EXIT_FAILURE);
	print_debug_info(d);
	setup_hooks(d);
	cub_exit(d, 0);
	// mlx_loop(d->mlx->mlx);
	return (EXIT_SUCCESS);
}

int main(int argc, char * argv[])
{
	t_ray r;
	t_data *d;

	if (argc != 2)
		return (f_dprintf(2, "Usage: ./cub3d map.cub\n"), EXIT_SUCCESS);
	d = data_init(argv[1]);
	if (!d)
		return (EXIT_FAILURE);
	print_debug_info(d);
	setup_hooks(d);
	cub_exit(d, 0);
	// mlx_loop(d->mlx->mlx);
	return (EXIT_SUCCESS);

	double time_curr_frame = 0;    // time of current frame
	double time_prev_frame = 0; // time of previous frame

	// start the main loop
	while (1)
	{
		for (int x = 0; x < d->mlx->win_w; x++)
		{
			ray_init(d, &r, x);
			dda(d, r)

			// DRAWING
			// Calculate height of line to draw on screen
			int lineHeight = (int) (d->win_y / perpWallDist);

			int pitch = 100;

			// calculate lowest and highest pixel to fill in current stripe
			int drawStart = -lineHeight / 2 + d->win_y / 2 + pitch;
			if (drawStart < 0)
				drawStart = 0;
			int drawEnd = lineHeight / 2 + d->win_y / 2 + pitch;
			if (drawEnd >= d->win_y)
				drawEnd = d->win_y - 1;

			// texturing calculations
			int texNum = worldMap[mapX][mapY] - 1; // 1 subtracted from it so that texture 0 can be used!

			// calculate value of wallX
			double wallX; // where exactly the wall was hit
			if (side == 0)
				wallX = posY + perpWallDist * rayDirY;
			else
				wallX = posX + perpWallDist * rayDirX;
			wallX -= floor((wallX));

			// x coordinate on the texture
			int texX = (int)(wallX * (double)texWidth);
			if (side == 0 && rayDirX > 0)
				texX = texWidth - texX - 1;
			if (side == 1 && rayDirY < 0)
				texX = texWidth - texX - 1;

			// TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
			// How much to increase the texture coordinate per screen pixel
			double step = 1.0 * texHeight / lineHeight;
			// Starting texture coordinate
			double texPos = (drawStart - pitch - d->win_y / 2 + lineHeight / 2) * step;
			for (int y = drawStart; y < drawEnd; y++)
			{
				// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
				int texY = (int) texPos & (texHeight - 1);
				texPos += step;
				int32_t color = texture[texNum][texHeight * texY + texX];
				// make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
				if (side == 1)
					color = (color >> 1) & 8355711;
				buffer[y][x] = color;
			}
		}

		drawBuffer(buffer[0]);
		for (int y = 0; y < d->win_y; y++)
			for (int x = 0; x < d->win_x; x++)
				buffer[y][x] = 0; // clear the buffer instead of cls()
		// timing for input and FPS counter
		time_prev_frame = time_curr_frame;
		time_curr_frame = getTicks();
		double frameTime = (time_curr_frame - time_prev_frame) / 1000.0; // frametime is the time this frame has taken, in seconds
		print(1.0 / frameTime); // FPS counter
		redraw();

		// speed modifiers
		double moveSpeed = frameTime * 5.0; // the constant value is in squares/second
		double rotSpeed = frameTime * 3.0; // the constant value is in radians/second
}
