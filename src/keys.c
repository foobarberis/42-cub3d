#include "cub3d.h"

static void rotate_right(t_data *d)
{
	// both camera direction and camera plane must be rotated
/* 	double oldDirX = dirX;
	dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
	dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
	double oldPlaneX = planeX;
	planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
	planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed); */
}

static void rotate_left(t_data *d)
{
	// both camera direction and camera plane must be rotated
/* 	double oldDirX = dirX;
	dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
	dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
	double oldPlaneX = planeX;
	planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
	planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed); */
}

static void move_forward(t_data *d)
{
/* 	if (worldMap[(int) (posX + dirX * moveSpeed)][(int) posY] == false)
		posX += dirX * moveSpeed;
	if (worldMap[(int) posX][(int) (posY + dirY * moveSpeed)] == false)
		posY += dirY * moveSpeed; */
}

static void move_backward(t_data *d)
{
/* 	if (worldMap[(int) (posX - dirX * moveSpeed)][(int) posY] == false)
		posX -= dirX * moveSpeed;
	if (worldMap[(int) posX][(int) (posY - dirY * moveSpeed)] == false)
		posY -= dirY * moveSpeed; */
}

int hook_keypress(t_data *d, int key)
{
	if (key == XK_Escape)
		cub_exit(d, EXIT_SUCCESS);
	else if (key == XK_Up)
		move_forward(d);
	else if (key == XK_Down)
		move_backward(d);
	else if (key == XK_Right)
		rotate_right(d);
	else if (key == XK_Left)
		rotate_left(d);
	return (0);
}
