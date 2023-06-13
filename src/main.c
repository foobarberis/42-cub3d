#include "cub3d.h"
#include <stdio.h>
#include <stdbool.h>

static t_camera *cub_cam_init()
{
	t_camera *cam;

	cam = malloc(sizeof(t_camera));
	if (!cam)
		return (NULL);
	cam->pos_x = 22.0;
	cam->pos_y = 11.5;
	cam->dir_x - 1.0;
	cam->dir_y = 0.0;
	cam->plane_x = 0.0;
	cam->plane_y = 0.66;
	return (cam);
}

static void	cub_free_if(t_data *env)
{
	if (env->win)
		mlx_destroy_window(env->mlx, env->win);
	if (env->img)
/* 		mlx_destroy_image(env->mlx, env->img);
	if (env->m)
		matrix_destroy(env->m, env->ymap); */
	mlx_destroy_display(env->mlx);
	free(env->mlx);
	env->win = NULL;
	env->img = NULL;
	env->addr = NULL;
	// env->m = NULL;
	env->mlx = NULL;
	free(env);
	env = NULL;
}

static void	cub_init_members(t_data *env)
{
	env->mlx = NULL;
	env->win = NULL;
	env->img = NULL;
	env->addr = NULL;
	env->bpp = 0;
	env->llen = 0;
	env->end = 0;
	env->xwin = screenWidth;
	env->ywin = screenHeight;
}

t_data	*cub_init(void)
{
	t_data	*p;

	p = malloc(sizeof(t_data));
	if (!p)
		return (NULL);
	cub_init_members(p);
	p->mlx = mlx_init();
	if (!(p->mlx))
		return (free(p), NULL);
	p->win = mlx_new_window(p->mlx, p->xwin, p->ywin, "cub3D");
	p->img = mlx_new_image(p->mlx, p->xwin, p->ywin);
	if (!(p->win) || !(p->img))
		return (cub_free_if(p), NULL);
	p->addr = mlx_get_data_addr(p->img, &(p->bpp), &(p->llen), &(p->end));
	return (p);
}

int worldMap[mapWidth][mapHeight] = {
    {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 7, 7, 7, 7, 7, 7, 7, 7},
    {4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 7},
    {4, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7},
    {4, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7},
    {4, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 7},
    {4, 0, 4, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 7, 0, 7, 7, 7, 7, 7},
    {4, 0, 5, 0, 0, 0, 0, 5, 0, 5, 0, 5, 0, 5, 0, 5, 7, 0, 0, 0, 7, 7, 7, 1},
    {4, 0, 6, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5, 7, 0, 0, 0, 0, 0, 0, 8},
    {4, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 1},
    {4, 0, 8, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5, 7, 0, 0, 0, 0, 0, 0, 8},
    {4, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5, 7, 0, 0, 0, 7, 7, 7, 1},
    {4, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 0, 5, 5, 5, 5, 7, 7, 7, 7, 7, 7, 7, 1},
    {6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
    {8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
    {6, 6, 6, 6, 6, 6, 0, 6, 6, 6, 6, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
    {4, 4, 4, 4, 4, 4, 0, 4, 4, 4, 6, 0, 6, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3},
    {4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2},
    {4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 2, 0, 0, 5, 0, 0, 2, 0, 0, 0, 2},
    {4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2},
    {4, 0, 6, 0, 6, 0, 0, 0, 0, 4, 6, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 2},
    {4, 0, 0, 5, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2},
    {4, 0, 6, 0, 6, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 5, 0, 0, 2, 0, 0, 0, 2},
    {4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2},
    {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3}};

int buffer[screenHeight][screenWidth];

int main(int argc, char * argv[])
{
	t_data *env;
	t_camera *cam;

	env = cub_init();
	cam = cub_cam_init();

	double time_curr_frame = 0;    // time of current frame
	double time_prev_frame = 0; // time of previous frame

	int tw, th;
	env->tex[0] = mlx_xpm_file_to_image(env->mlx, "assets/eagle.xpm", &tw, &th);
	env->tex[1] = mlx_xpm_file_to_image(env->mlx, "assets/redbrick.xpm", &tw, &th);
	env->tex[2] = mlx_xpm_file_to_image(env->mlx, "assets/purplestone.xpm", &tw, &th);
	env->tex[3] = mlx_xpm_file_to_image(env->mlx, "assets/greystone.xpm", &tw, &th);
	env->tex[4] = mlx_xpm_file_to_image(env->mlx, "assets/bluestone.xpm", &tw, &th);
	env->tex[5] = mlx_xpm_file_to_image(env->mlx, "assets/mossy.xpm", &tw, &th);
	env->tex[6] = mlx_xpm_file_to_image(env->mlx, "assets/wood.xpm", &tw, &th);
	env->tex[7] = mlx_xpm_file_to_image(env->mlx, "assets/colorstone.xpm", &tw, &th);

	// start the main loop
	while (1)
	{
		for (int x = 0; x < env->xwin; x++)
		{
			// calculate ray position and direction
			double cameraX = 2 * x / (double) env->xwin - 1; // x-coordinate in camera space
			double rayDirX = dirX + planeX * cameraX;
			double rayDirY = dirY + planeY * cameraX;

			// which box of the map we're in
			int mapX = (int)posX;
			int mapY = (int)posY;

			// length of ray from current position to next x or y-side
			double sideDistX;
			double sideDistY;

			// length of ray from one x or y-side to next x or y-side
			double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
			double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
			double perpWallDist;

			// what direction to step in x or y-direction (either +1 or -1)
			int stepX;
			int stepY;

			int hit = 0; // was there a wall hit?
			int side;    // was a NS or a EW wall hit?

			// calculate step and initial sideDist
			if (rayDirX < 0)
			{
				stepX = -1;
				sideDistX = (posX - mapX) * deltaDistX;
			}
			else
			{
				stepX = 1;
				sideDistX = (mapX + 1.0 - posX) * deltaDistX;
			}
			if (rayDirY < 0)
			{
				stepY = -1;
				sideDistY = (posY - mapY) * deltaDistY;
			}
			else
			{
				stepY = 1;
				sideDistY = (mapY + 1.0 - posY) * deltaDistY;
			}
			// perform DDA
			while (hit == 0)
			{
				// jump to next map square, either in x-direction, or in y-direction
				if (sideDistX < sideDistY)
				{
					sideDistX += deltaDistX;
					mapX += stepX;
					side = 0;
				}
				else
				{
					sideDistY += deltaDistY;
					mapY += stepY;
					side = 1;
				}
				// Check if ray has hit a wall
				if (worldMap[mapX][mapY] > 0)
					hit = 1;
			}

			// Calculate distance of perpendicular ray (Euclidean distance would give fisheye effect!)
			if (side == 0)
				perpWallDist = (sideDistX - deltaDistX);
			else
				perpWallDist = (sideDistY - deltaDistY);

			// Calculate height of line to draw on screen
			int lineHeight = (int) (env->ywin / perpWallDist);

			int pitch = 100;

			// calculate lowest and highest pixel to fill in current stripe
			int drawStart = -lineHeight / 2 + env->ywin / 2 + pitch;
			if (drawStart < 0)
				drawStart = 0;
			int drawEnd = lineHeight / 2 + env->ywin / 2 + pitch;
			if (drawEnd >= env->ywin)
				drawEnd = env->ywin - 1;

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
			double texPos = (drawStart - pitch - env->ywin / 2 + lineHeight / 2) * step;
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
		for (int y = 0; y < env->ywin; y++)
			for (int x = 0; x < env->xwin; x++)
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
