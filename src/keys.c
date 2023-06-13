#include "cub3D"

static void rotate_right()
{
	// both camera direction and camera plane must be rotated
	double oldDirX = dirX;
	dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
	dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
	double oldPlaneX = planeX;
	planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
	planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
}

static void rotate_left()
{
	// both camera direction and camera plane must be rotated
	double oldDirX = dirX;
	dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
	dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
	double oldPlaneX = planeX;
	planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
	planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
}

static void move_forward()
{
	if (worldMap[(int) (posX + dirX * moveSpeed)][(int) posY] == false)
		posX += dirX * moveSpeed;
	if (worldMap[(int) posX][(int) (posY + dirY * moveSpeed)] == false)
		posY += dirY * moveSpeed;
}

static void move_backward()
{
	if (worldMap[(int) (posX - dirX * moveSpeed)][(int) posY] == false)
		posX -= dirX * moveSpeed;
	if (worldMap[(int) posX][(int) (posY - dirY * moveSpeed)] == false)
		posY -= dirY * moveSpeed;
}

int fdf_hook_keypress(int key, t_data *env)
{
	if (key == XK_Escape)
		fdf_exit(env);
	if (key == XK_Up)
		move_forward();
	if (key == XK_Down)
		move_backward();
	if (key == XK_Right)
		rotate_right();
	if (key == XK_Left)
		rotate_left();
	return (0);
}
