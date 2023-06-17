#include "cub3d.h"

static void remove_white_space(char *s)
{
	int i;
	int j;

	if (!*s)
		return;
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

/* FIXME: Add f_strncmp to mlc */
int f_strncmp(const char *_l, const char *_r, size_t n)
{
	const unsigned char *l=(void *)_l, *r=(void *)_r;
	if (!n--) return 0;
	for (; *l && *r && n && *l == *r ; l++, r++, n--);
	return *l - *r;
}

static int parse_texture(t_data *d, char *s)
{
	// check if id is valid
	// check if corresponding texture exists already
	// transform xpm to img, check return val for NULL
}

/* FIXME: Handle "NO\t" instead of just "NO " */
static int grep_textures(t_data *d, char *s)
{
	int	width;
	int	height;

	if (!f_strncmp(s, "NO ", 3))
		d->map->tex[N] = mlx_xpm_file_to_image(d->mlx->mlx, &s[2], &width, &height);
	else if (!f_strncmp(s, "SO ", 3))
		d->map->tex[S] = mlx_xpm_file_to_image(d->mlx->mlx, &s[2], &width, &height);
	else if (!f_strncmp(s, "WE ", 3))
		d->map->tex[W] = mlx_xpm_file_to_image(d->mlx->mlx, &s[2], &width, &height);
	else if (!f_strncmp(s, "EA ", 3))
		d->map->tex[E] = mlx_xpm_file_to_image(d->mlx->mlx, &s[2], &width, &height);
	else if (!f_strncmp(s, "F", 2))
		parse_color(&s[2])
	else if (!f_strncmp(s, "C ", 2))
	else
		return (f_dprintf(2, "cub3d: unrecognized identifier\n"), 1);
	return (0);

}

int parse_header(t_data *d, char **header)
{
	int i;

	i = 0;
	while (header[i])
	{
		if (header[i][0])
		{
			remove_white_space(header[i]);
			grep_textures(d, header[i]);
		}
		printf("DEBUG :: %s\n", header[i]);
		i++;
	}
	return 0;
}
