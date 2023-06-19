#include "cub3d.h"

static void compute_step(t_ray *r, double pos_x, double pos_y)
{
	if (r->dir_x < 0)
	{
		r->step_x = -1;
		r->sdist_x = (pos_x - r->map_x) * r->ddist_x;
	}
	else
	{
		r->step_x = 1;
		r->sdist_x = (r->map_x + 1.0 - pos_x) * r->ddist_x;
	}
	if (r->dir_x < 0)
	{
		r->step_y = -1;
		r->sdist_y = (pos_y - r->map_y) * r->ddist_y;
	}
	else
	{
		r->step_y = 1;
		r->sdist_y = (r->map_y + 1.0 - pos_y) * r->ddist_y;
	}
}

void dda(t_data *d, t_ray *r)
{
	while (r->hit == 0)
	{
		// jump to next map square, either in x-direction, or in y-direction
		if (r->sdist_x < r->sdist_y)
		{
			r->sdist_x += r->ddist_x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->sdist_y += r->ddist_y;
			r->map_y += r->step_y;
			r->side = 1;
		}
		// Check if ray has hit a wall
		if (d->map->map[r->map_x][r->map_y] > 0)
			r->hit = 1;
	}
	// Calculate distance of perpendicular ray (Euclidean distance would give fisheye effect!)
	if (r->side == 0)
		r->perp_wall_dist = (r->sdist_x - r->ddist_x);
	else
		r->perp_wall_dist = (r->sdist_y - r->ddist_y);
}

void ray_init(t_data *d, t_ray *r, int x)
{
	r->perp_wall_dist = 0;
	r->cam_x = 2 * x / (double) d->mlx->win_w - 1;
	r->dir_x = d->cam->dir_x + d->cam->plane_x * r->cam_x;
	r->dir_y = d->cam->dir_y + d->cam->plane_y * r->cam_x;
	// which box of the map we're in
	r->map_x = (int) d->cam->pos_x;
	r->map_y = (int) d->cam->pos_y;
	// length of ray from one x or y-side to next x or y-side
	r->ddist_x = (r->dir_x == 0) ? INFINITY : fabs(1 / r->dir_x);
	r->ddist_y = (r->dir_y == 0) ? INFINITY : fabs(1 / r->dir_y);
	r->hit = 0; // was there a wall hit?
	r->side;    // was a NS or a EW wall hit?
	compute_step(r, d->cam->pos_x, d->cam->pos_y);
}
