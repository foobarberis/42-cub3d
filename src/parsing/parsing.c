#include "cub3d.h"

/*
* Errors:
*
* Player is outside of the map.
* No player is set.
* Multiple players are set.
* Map is not closed.
* Map contains illegal characters.
* Map is not after the header.
* Map contains blank lines.
* Header is incomplete.
* Header contains unrecognized identifier.
* Header contains multiple of the same identifier.
* Colors are not in RGB format.
* Colors are not in range 0-255.
*/

static int	count_lines(char *s)
{
	int	i;
	int	lines;

	i = 0;
	lines = 1;
	while (s[i])
	{
		if (s[i] == '\n')
			lines++;
		i++;
	}
	return (lines);
}

static char **map_split(char *s)
{
	int		i;
	char	*p;
	char	**new;

	i = 0;
	p = s;
	new = f_calloc(count_lines(s) + 1, sizeof(char *));
	if (!new)
		return (NULL);
	while (*p && *s)
	{
		p = f_strchrnul(p, '\n');
		if (*p)
			*p++ = '\0';
		new[i++] = s;
		s = p;
	}
	return (new);
}

int parsing(t_data *d, char *file)
{
	char 	*map_1d;
	char	**map_2d;

	map_1d = f_file_to_array(file);
	if (!map_1d)
		return (1);
	map_2d = map_split(map_1d);
	// parse_header(d, map_2d);
	if (parse_map(d, map_2d))
		cub_exit(d, EXIT_SUCCESS);
	free(map_1d);
	free(map_2d);
	return (0);
}
