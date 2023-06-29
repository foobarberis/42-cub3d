/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 13:13:23 by mbarberi          #+#    #+#             */
/*   Updated: 2023/06/29 16:29:28 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_map(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		if (!map[i][j])
			return (f_dprintf(2, ERR ERR_EMPTY, i + 1), 1);
		while (map[i][j])
		{
			if (!islegal(map[i][j]))
				return (f_dprintf(2, ERR ERR_FORBID, i + 1, map[i][j]), 1);
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
				mat[i][j] = 1;
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

static int	check_zero(char **map)
{
	int	i;
	int	j;
	int	error;

	i = 0;
	error = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0')
				dfs(map, i, j, &error);
			if (error)
				return (1);
			j++;
		}
		i++;
	}
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
		return (f_dprintf(2, ERR "cub3d: player not found\n"), 1);
	get_player_dir(d->cam, map[x][y]);
	if (map_has_multiple_players(map, x, y))
		return (f_dprintf(2, ERR "cub3d: multiple players found\n"), 1);
	dfs(map, x, y, &error);
	if (error || check_zero(map))
		return (f_dprintf(2, ERR "cub3d: map is not closed\n"), 1);
	if (map_to_matrix(d, map))
		return (1);
	d->cam->pos_x = (double)x + 0.5;
	d->cam->pos_y = (double)y + 0.5;
	return (0);
}
