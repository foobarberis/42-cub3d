#include "cub3d.h"

/* FIXME: Add strchrnul*/

static char *f_strchrnul(const char *s, int c)
{
	while (*s && *(unsigned char *)s != c)
		s++;
	return ((char *)s);
}

char **f_split(char *s, int lim)
{
	char **new;

	if (!s)
		return (NULL);
}

t_map *map_init(char *path)
{
	t_map	*map;
	char	**ascii_map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	ascii_map = f_split(f_file_to_array(path), '\n');
	// remove empty lines
	// check for syntax errors
	// check if the map is closed (check that each column starts and ends with a wall)
	// extract textures and colors
	// replace spaces with walls
	// transform ascii map to int
	// replace int value with texture (1 for N, 2 for S etc.)
}


/* char *f_split(char *s, int lim)
{
	static char *file = f_file_to_array(path);
	static char *p = file;
	static char *q = file;

	if (!file)
		return (NULL);
	p = q;
	if (!*q)
		return (free(file), NULL);
	else if (*q == '\n')
		q++;
	q = f_strchrnul(file, '\n');
	if (!q)
		;
	q = 0;
	return (p);
} */
