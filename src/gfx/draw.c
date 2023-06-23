#include "cub3d.h"

static void draw_pixel(t_data *d, t_pix *p, t_ray *r, int x)
{
	int y;

	y = p->draw_start;
	while (y < p->draw_end)
	{
		p->tex_y = (int) p->tex_pos & (d->map->tex[p->tex_n].h - 1);
		p->tex_pos += p->step;
		p->color = d->map->tex[p->tex_n].addr[p->tex_y * d->map->tex[p->tex_n].llen + (p->tex_x << 2)];
		if (r->side == 1)
			p->color = (p->color >> 1) & 0x7F7F7F;
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

static void compute_texture(t_data *d, t_pix *p, t_ray *r, int x)
{
	p->pitch = 100;
	p->line_h = (int) (d->mlx->win_h / r->perp_wall_dist);
	p->draw_start = -p->line_h / 2 + d->mlx->win_h / 2 + p->pitch;
	if (p->draw_start < 0)
		p->draw_start = 0;
	p->draw_end = p->line_h / 2 + d->mlx->win_h / 2 + p->pitch;
	if (p->draw_end >= d->mlx->win_h)
		p->draw_end = d->mlx->win_h - 1;
	p->tex_n = d->map->map[r->map_x][r->map_y] - 1;
	if (!r->side) /* setting this to 1 fixes texture wtf */
		p->wall_x = d->cam->pos_y + r->perp_wall_dist * r->dir_y;
	else
		p->wall_x = d->cam->pos_x + r->perp_wall_dist * r->dir_x;
	p->wall_x -= floor(p->wall_x);
	p->tex_x = (int) (p->wall_x * (double) d->map->tex[p->tex_n].w);
	if ((!r->side && r->dir_x > 0) || (r->side && r->dir_y < 0))
		p->tex_x = d->map->tex[p->tex_n].w - p->tex_x - 1;
	p->step = 1.0 * d->map->tex[N].h / p->line_h;
	p->tex_pos = (p->draw_start - p->pitch - d->mlx->win_h / 2 + p->line_h / 2) * p->step;
}

int draw_frame(t_data *d)
{
	int x;
	t_ray r;
	t_pix p;

	x = 0;
	move(d);
	printf("%f, %f, %f, %f\n", d->cam->pos_x, d->cam->pos_y, d->cam->dir_x, d->cam->dir_y);
	while (x < d->mlx->win_w)
	{
		raycast(d, &r, x);
		compute_texture(d, &p, &r, x);
		draw_pixel(d, &p, &r, x);
		x++;
	}
	mlx_clear_window(d->mlx->mlx, d->mlx->win);
	mlx_put_image_to_window(d->mlx->mlx, d->mlx->win, d->mlx->img, 0, 0);
	return (0);
}
