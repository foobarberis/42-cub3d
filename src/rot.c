#include "cub3d.h"

void rotate_left(t_data *d)
{
	double odir_x;
	double oplane_x;

	odir_x = d->cam->dir_x;
	oplane_x = d->cam->plane_x;
	d->cam->dir_x =
	    d->cam->dir_x * cos(-d->cam->rospeed) - d->cam->dir_y * sin(-d->cam->rospeed);
	d->cam->dir_y = odir_x * sin(-d->cam->rospeed) + d->cam->dir_y * cos(-d->cam->rospeed);
	d->cam->plane_x =
	    d->cam->plane_x * cos(-d->cam->rospeed) - d->cam->plane_y * sin(-d->cam->rospeed);
	d->cam->plane_y =
	    oplane_x * sin(-d->cam->rospeed) + d->cam->plane_y * cos(-d->cam->rospeed);
}

void rotate_right(t_data *d)
{
	double odir_x;
	double oplane_x;

	odir_x = d->cam->dir_x;
	oplane_x = d->cam->plane_x;
	d->cam->dir_x = d->cam->dir_x * cos(d->cam->rospeed)
	- d->cam->dir_y * sin(d->cam->rospeed);
	d->cam->dir_y = odir_x * sin(d->cam->rospeed)
	+ d->cam->dir_y * cos(d->cam->rospeed);
	d->cam->plane_x = d->cam->plane_x * cos(d->cam->rospeed)
	- d->cam->plane_y * sin(d->cam->rospeed);
	d->cam->plane_y = oplane_x * sin(d->cam->rospeed)
	+ d->cam->plane_y * cos(d->cam->rospeed);
}
