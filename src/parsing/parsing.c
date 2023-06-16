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

static int locate_map(char **map)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (map[i])
	{
		while (f_isspace(map[i][j]))
			j++;
		if (map[i][j] == '0' || map[i][j] == '1')
			return (i);
		if (((map[i][j] == 'N' || map[i][j] == 'S') && map[i][j + 1] != 'O')
			|| (map[i][j] == 'E' && map[i][j + 1] != 'A')
			|| (map[i][j] == 'W' && map[i][j + 1] != 'E'))
		return (i);
		i++;
	}
	return (-1);
}

/* FIXME: Maybe add return value in case locate_map return -1 */
static void remove_header(char **map)
{
	int i;
	int j;

	j = 0;
	i = locate_map(map);
	if (i == -1)
		return;
	while (map[i])
		map[j++] = map[i++];
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
	remove_header(map_2d);
	for (int i = 0; map_2d[i]; i++)
		printf("%s\n", map_2d[i]);
	// map_only(map);
	if (parse_map(d, map_2d))
		cub_exit(d, EXIT_SUCCESS);
	free(map_1d);
	free(map_2d);
	return (0);
}
