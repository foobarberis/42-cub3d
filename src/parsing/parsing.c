/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 13:26:41 by mbarberi          #+#    #+#             */
/*   Updated: 2023/06/26 13:27:19 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

/* returns 1 if the line qualifies to be the beginning of the map */
static int	locate_map(char *s)
{
	while (f_isspace(*s))
		s++;
	if (*s == '0' || *s == '1')
		return (1);
	else if (((*s == 'N' || *s == 'S') && *(s + 1) != 'O')
		|| (*s == 'E' && *(s + 1) != 'A') || (*s == 'W' && *(s + 1) != 'E'))
		return (1);
	return (0);
}

static void	map_split(char *s, char **map, char **head)
{
	int		i;
	int		j;
	int		map_found;
	char	*p;

	i = 0;
	j = 0;
	p = s;
	map_found = 0;
	while (*p && *s)
	{
		p = f_strchrnul(p, '\n');
		if (*p)
			*p++ = '\0';
		if (!map_found)
			map_found = locate_map(s);
		if (map_found)
			map[i++] = s;
		else
			head[j++] = s;
		s = p;
	}
}

int	parsing(t_data *d, char *file)
{
	char	*map_1d;
	char	**map;
	char	**header;

	map_1d = f_file_to_array(file);
	if (!map_1d)
		return (1);
	map = f_calloc(count_lines(map_1d) + 1, sizeof(char *));
	if (!map)
		return (free(map_1d), 1);
	header = f_calloc(count_lines(map_1d) + 1, sizeof(char *));
	if (!header)
		return (free(map_1d), free(map), 1);
	map_split(map_1d, map, header);
	if (parse_header(d, header))
		cub_exit(d, EXIT_SUCCESS);
	if (parse_map(d, map))
		cub_exit(d, EXIT_SUCCESS);
	free(map_1d);
	free(map);
	free(header);
	return (0);
}
