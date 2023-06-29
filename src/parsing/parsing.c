/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 13:26:41 by mbarberi          #+#    #+#             */
/*   Updated: 2023/06/29 10:33:05 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	char	**head;

	map_1d = f_file_to_array(file);
	if (!map_1d)
		return (1);
	map = f_calloc(count_lines(map_1d) + 1, sizeof(char *));
	if (!map)
		return (free(map_1d), 1);
	head = f_calloc(count_lines(map_1d) + 1, sizeof(char *));
	if (!head)
		return (free(map_1d), free(map), 1);
	map_split(map_1d, map, head);
	if (parse_header(d, head))
		return (free(map_1d), free(map), free(head), cub_exit(d, EXIT_SUCCESS));
	if (parse_map(d, map))
		return (free(map_1d), free(map), free(head), cub_exit(d, EXIT_SUCCESS));
	free(map_1d);
	free(map);
	free(head);
	return (0);
}
