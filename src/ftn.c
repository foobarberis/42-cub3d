/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftn.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 10:46:00 by mbarberi          #+#    #+#             */
/*   Updated: 2023/06/29 11:48:14 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	dfs(char **m, int x, int y, int *error)
{
	if ((x && y >= (int)f_strlen(m[x - 1])) || ((x + 1 < get_map_height(m))
			&& y >= (int)f_strlen(m[x + 1])) || x <= 0
		|| y <= 0 || !m[x][y + 1] || x >= get_map_height(m)
		|| f_isspace(m[x][y]))
		*error = 1;
	m[x][y] = FILL;
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

t_data	*data_create_next(t_data *d)
{
	d->player = f_calloc(1, sizeof(t_mlx));
	if (!d->player)
		return (free(d->minimap), free(d->map), free(d->cam),
			free(d->mlx), free(d), NULL);
	d->map->tex = f_calloc(4, sizeof(t_tex));
	if (!d->map->tex)
		return (free(d->player), free(d->minimap), free(d->map),
			free(d->cam), free(d->mlx), free(d), NULL);
	return (d);
}
