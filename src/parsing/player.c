/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 13:27:25 by mbarberi          #+#    #+#             */
/*   Updated: 2023/06/27 13:34:47 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_player_pos(char **map, int *x, int *y)
{
	while (map[*x])
	{
		while (map[*x][*y] && map[*x][*y] != 'N'
			&& map[*x][*y] != 'S' && map[*x][*y] != 'E' && map[*x][*y] != 'W')
			*y += 1;
		if (!map[*x][*y])
			*y = 0;
		else
			break ;
		*x += 1;
	}
	if (!map[*x])
	{
		*x = -1;
		*y = -1;
	}
}

void	get_player_dir(t_cam *cam, char c)
{
	cam->mospeed = 20000.0 / (WINDOW_HEIGHT * WINDOW_WIDTH);
	cam->rospeed = 15000.0 / (WINDOW_HEIGHT * WINDOW_WIDTH);
	if (c == 'E')
	{
		cam->dir_x = 0.0;
		cam->dir_y = 1.0;
		cam->plane_x = 0.66;
		cam->plane_y = 0.0;
		cam->rospeed = -cam->rospeed;
	}
	else if (c == 'W')
	{
		cam->dir_x = 0.0;
		cam->dir_y = -1.0;
		cam->plane_x = 0.66;
		cam->plane_y = 0.0;
	}
	else if (c == 'S')
	{
		cam->dir_x = 1.0;
		cam->dir_y = 0.0;
		cam->plane_x = 0.0;
		cam->plane_y = 0.66;
	}
	else if (c == 'N')
	{
		cam->dir_x = -1.0;
		cam->dir_y = 0.0;
		cam->plane_x = 0.0;
		cam->plane_y = 0.66;
		cam->rospeed = -cam->rospeed;
	}
}

int	map_has_multiple_players(char **map, int x, int y)
{
	int	nx;
	int	ny;

	nx = x;
	ny = y;
	map[x][y] = FILL;
	get_player_pos(map, &nx, &ny);
	if (nx == -1)
		return (0);
	return (1);
}
