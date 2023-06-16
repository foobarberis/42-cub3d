#include "cub3d.h"

void get_player_pos(char **map, int *x, int *y)
{
	while (map[*x])
	{
		while (map[*x][*y] && map[*x][*y] != 'N' && map[*x][*y] != 'S' && map[*x][*y] != 'E' && map[*x][*y] != 'W')
			*y += 1;
		if (!map[*x][*y])
			*y = 0;
		else
			break;
		*x += 1;
	}
	if (!map[*x])
	{
		*x = -1;
		*y = -1;
	}
}

/* FIXME: Check if values are correct */
void get_player_dir(char c, double *dx, double *dy)
{
	if (c == 'N')
	{
		*dx = 1.0;
		*dy = 0.0;
	}
	else if (c == 'S')
	{
		*dx = -1.0;
		*dy = 0.0;
	}
	else if (c == 'E')
	{
		*dx = 0.0;
		*dy = -1.0;
	}
	else if (c == 'W')
	{
		*dx = 0.0;
		*dy = 1.0;
	}
}

int map_has_mult_player(char **map, int x, int y)
{
	int nx;
	int ny;

	nx = x;
	ny = y;
	map[x][y] = FILL;
	get_player_pos(map, &nx, &ny);
	if (nx == -1)
		return (0);
	return (1);
}
