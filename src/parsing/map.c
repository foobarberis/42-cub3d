/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 13:13:23 by mbarberi          #+#    #+#             */
/*   Updated: 2023/06/28 14:25:36 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	dfs(char **m, int x, int y, int *error)
{
	m[x][y] = FILL;
	if ((x && y > (int)f_strlen(m[x - 1])) || ((x + 1 < get_map_height(m)) && y > (int)f_strlen(m[x + 1])) || x <= 0 || y <= 0 ||!m[x][y + 1] || x >= get_map_height(m))
		*error = 1;
	if (*error)
		return ;
	if (y < (int)f_strlen(m[x - 1])
		&& m[x - 1][y] != '1' && m[x - 1][y] != FILL)
		dfs(m, x - 1, y, error);
	if (y < (int)f_strlen(m[x + 1])
		&& m[x + 1][y] != '1' && m[x + 1][y] != FILL)
		dfs(m, x + 1, y, error);
	if (m[x][y - 1] != '1' && m[x][y - 1] != FILL)
		dfs(m, x, y - 1, error);
	if (m[x][y + 1] != '1' && m[x][y + 1] != FILL)
		dfs(m, x, y + 1, error);
}

static int	check_map(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		if (!map[i][j])
			return (f_dprintf(2, ERR_EMPTY, i + 1), 1);
		while (map[i][j])
		{
			if (!islegal(map[i][j]))
				return (f_dprintf(2, ERR_FORBID, i + 1, map[i][j]), 1);
			j++;
		}
		i++;
	}
	return (0);
}

static void	ascii_to_int(int **mat, char **map, int nrows)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (f_isspace(map[i][j]))
				mat[i][j] = 0;
			else if (map[i][j] == '0')
				mat[i][j] = 0;
			else if (map[i][j] == '1')
				mat[i][j] = 1;
			else if (map[i][j] == FILL)
				mat[i][j] = 0;
			else
				mat[i][j] = 0;
			j++;
		}
		while (j < nrows)
			mat[i][j++] = 1;
	i++;
	}
}

static int	map_to_matrix(t_data *d, char **map)
{
	d->map->map_w = get_map_width(map);
	d->map->map_h = get_map_height(map);
	d->map->map = matrix_create(d->map->map_w, d->map->map_h);
	if (!d->map->map)
		return (1);
	ascii_to_int(d->map->map, map, d->map->map_w);
	return (0);
}

int	parse_map(t_data *d, char **map)
{
	int	x;
	int	y;
	int	error;

	x = 0;
	y = 0;
	error = 0;
	if (check_map(map))
		return (1);
	get_player_pos(map, &x, &y);
	if (x == -1)
		return (f_dprintf(2, "cub3d: player not found\n"), 1);
	get_player_dir(d->cam, map[x][y]);
	if (map_has_multiple_players(map, x, y))
		return (f_dprintf(2, "cub3d: multiple players found\n"), 1);
	dfs(map, x, y, &error);
	if (error)
		return (f_dprintf(2, "cub3d: map is not closed\n"), 1);
	if (map_to_matrix(d, map))
		return (1);
	d->cam->pos_x = (double)x;
	d->cam->pos_y = (double)y;
	return (0);
}
