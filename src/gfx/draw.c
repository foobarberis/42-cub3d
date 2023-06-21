#include "cub3d.h"

void draw_pixel(t_data *d, t_pix *p, int x)
{
	int y;

	y = p->draw_start;
	while (y < p->draw_end)
	{
		// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
		p->tex_y = (int) p->tex_pos & (d->map->tex[p->tex_n].h - 1);
		p->tex_pos += p->step;
		// int32_t *test = (int32_t *)(d->map->tex[p->tex_n].addr + (d->map->tex[p->tex_n].h * p->tex_y + p->tex_x * d->map->tex[p->tex_n].llen));
		p->color = d->map->tex[p->tex_n].addr[d->map->tex[p->tex_n].h * p->tex_y + p->tex_x];
		// make p->color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
		if (d->ray->side == 1)
			p->color = (p->color >> 1) & 8355711;
		mlx_pixel_put_img(d, x, y, p->color);
		y++;
	}
	y = 0;
	while (y < p->draw_start)
		mlx_pixel_put_img(d, x, y++, d->map->ceil);
	y = d->mlx->win_h;
	while (y > p->draw_end)
		mlx_pixel_put_img(d, x, y--, d->map->floor);
}

int draw_frame(t_data *d)
{
	t_pix p;

	move(d);
	for (int x = 0; x < d->mlx->win_w; x++)
	{
		raycast(d, d->ray, x);

		// Calculate height of line to draw on screen
		p.pitch = 100;
		p.line_h = (int) (d->mlx->win_h / d->ray->perp_wall_dist);

		// calculate lowest and highest pixel to fill in current stripe
		p.draw_start = -p.line_h / 2 + d->mlx->win_h / 2 + p.pitch;
		if (p.draw_start < 0)
			p.draw_start = 0;
		p.draw_end = p.line_h / 2 + d->mlx->win_h / 2 + p.pitch;
		if (p.draw_end >= d->mlx->win_h)
			p.draw_end = d->mlx->win_h - 1;

		// texturing calculations
		p.tex_n = d->map->map[d->ray->map_x][d->ray->map_y] - 1; // 1 subtracted from it so that texture 0 can be used!

		// where exactly the wall was hit
		if (d->ray->side == 0)
			p.wall_x = d->cam->pos_x + d->ray->perp_wall_dist * d->ray->dir_x;
		else
			p.wall_x = d->cam->pos_y + d->ray->perp_wall_dist * d->ray->dir_y;
		p.wall_x -= floor((p.wall_x));

		// x coordinate on the texture
		p.tex_x = (int) (p.wall_x * (double) d->map->tex[N].w);
		if (d->ray->side == 0 && d->ray->dir_x > 0)
			p.tex_x = d->map->tex[N].w - p.tex_x - 1;
		if (d->ray->side == 1 && d->ray->dir_y < 0)
			p.tex_x = d->map->tex[N].w - p.tex_x - 1;

		// TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate p.stepping faster
		// How much to increase the texture coordinate per screen pixel
		p.step = 1.0 * d->map->tex[N].h / p.line_h;
		// Starting texture coordinate
		p.tex_pos = (p.draw_start - p.pitch - d->mlx->win_h / 2 + p.line_h / 2) * p.step;
		draw_pixel(d, &p, x);
	}
	mlx_clear_window(d->mlx->mlx, d->mlx->win);
	mlx_put_image_to_window(d->mlx->mlx, d->mlx->win, d->mlx->img, 0, 0);
	return (0);
}
