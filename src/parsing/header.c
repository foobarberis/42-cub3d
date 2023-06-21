#include "cub3d.h"

static void remove_white_space(char *s)
{
	int i;
	int j;

	i = (int)f_strlen(s) - 1;
	j = 0;
	while (f_isspace(s[i]))
		i--;
	s[i + 1] = '\0';
	i = 0;
	while (f_isspace(s[i]))
		i++;
	while (s[i] && !f_isspace(s[i]))
		s[j++] = s[i++];
	s[j++] = ' ';
	while (f_isspace(s[i]))
		i++;
	while (s[i])
		s[j++] = s[i++];
	s[j] = '\0';
}

static int extract_texture(t_data *d, t_tex *tex, char *s)
{
	if (tex->t)
		return (f_dprintf(2, "cub3d: duplicate identifier\n"), 1);
	tex->t = mlx_xpm_file_to_image(d->mlx->mlx, s, &tex->w, &tex->h);
	if (!tex->t)
		return (f_dprintf(2, "cub3d: %s: texture could not be loaded\n", s), 1);
	tex->addr = mlx_get_data_addr(tex->t, &tex->bpp, &tex->llen, &tex->end);
	return (0);
}

static int parse_header_line(t_data *d, char *s)
{
	if (f_strlen(s) < 4) /* smallest possible line if e.g `NO a' */
		return (1);
	if (*s == 'N' && *(s + 1) == 'O' && f_isspace(*(s + 2)))
		return (extract_texture(d, &d->map->tex[N], s + 3));
	else if (*s == 'S' && *(s + 1) == 'O' && f_isspace(*(s + 2)))
		return (extract_texture(d, &d->map->tex[S], s + 3));
	else if (*s == 'E' && *(s + 1) == 'A' && f_isspace(*(s + 2)))
		return (extract_texture(d, &d->map->tex[E], s + 3));
	else if (*s == 'W' && *(s + 1) == 'E' && f_isspace(*(s + 2)))
		return (extract_texture(d, &d->map->tex[W], s + 3));
	else if (*s == 'F' && f_isspace(*(s + 1)))
		return (parse_color(s + 2, &d->map->floor));
	else if (*s == 'C' && f_isspace(*(s + 1)))
		return (parse_color(s + 2, &d->map->ceil));
	else
		return (f_dprintf(2, "cub3d: %s: unrecognized identifier\n", s), 1);
}

int parse_header(t_data *d, char **head)
{
	while (*head)
	{
		if (**head)
		{
			remove_white_space(*head);
			if (parse_header_line(d, *head))
				return (1);
		}
		head++;
	}
	return (0);
}
