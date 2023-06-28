/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 13:27:25 by mbarberi          #+#    #+#             */
/*   Updated: 2023/06/28 10:26:20 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_player_dir_ns(t_cam *cam, char c)
{
	if (c == 'N')
	{
		cam->dir_x = -1.0;
		cam->dir_y = 0.0;
		cam->plane_x = 0.0;
		cam->plane_y = 0.66;
		cam->rospeed = -cam->rospeed;
	}
	else if (c == 'S')
	{
		cam->dir_x = 1.0;
		cam->dir_y = 0.0;
		cam->plane_x = 0.0;
		cam->plane_y = 0.66;
	}
}

static void	get_player_dir_ew(t_cam *cam, char c)
{
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
}

void	get_player_dir(t_cam *cam, char c)
{
	cam->mospeed = 0.030;
	cam->rospeed = 0.020;
	if (c == 'N' || c == 'S')
		return (get_player_dir_ns(cam, c));
	else if (c == 'E' || c == 'W')
		return (get_player_dir_ew(cam, c));
}

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
