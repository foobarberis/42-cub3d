#include "cub3d.h"

void dfs(char **m, int x, int y, int *error)
{
	m[x][y] = FILL;
	/* FIXME: Find a better solution to not compute length each time */
	if (x <= 0 || y <= 0 ||!m[x][y + 1] || x >= get_map_height(m))
		*error = 1;
	if (*error)
		return;
	if (y < (int)f_strlen(m[x - 1]) && m[x - 1][y] != '1' && m[x - 1][y] != FILL)
		dfs(m, x - 1, y, error);
	if (y < (int)f_strlen(m[x + 1]) && m[x + 1][y] != '1' && m[x + 1][y] != FILL)
		dfs(m, x + 1, y, error);
	if (m[x][y - 1] != '1' && m[x][y - 1] != FILL)
		dfs(m, x, y - 1, error);
	if (m[x][y + 1] != '1' && m[x][y + 1] != FILL)
		dfs(m, x, y + 1, error);
}

/* check for empty lines or forbidden chars, returns 1 in case of error */
int check_map(char **map)
{
	int i;
	int j;

	i = 0;
	while (map[i])
	{
		j = 0;
		if (!map[i][j])
			return (f_dprintf(2, "cub3d: line %d: map contains empty lines\n", i + 1), 1);
		while (map[i][j])
		{
			if (!islegal(map[i][j]))
				return (f_dprintf(2, "cub3d: line %d: map contains forbidden character (`%c')\n", i + 1, map[i][j]), 1);
			j++;
		}
		i++;
	}
	return (0);
}

void ascii_to_int(int **mat, char **map, int nrows)
{
	int i;
	int j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (f_isspace(map[i][j]))
				mat[i][j] = 1;
			else if (map[i][j] == '0')
				mat[i][j] = 1;
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

int parse_map(t_data *d, char **map)
{
	int x;
	int y;
	int error;

	x = 0;
	y = 0;
	error = 0;
	if (check_map(map))
		return (1);
	get_player_pos(map, &x, &y);
	if (x == -1)
		return (f_dprintf(2, "cub3d: player not found\n"), 1);
	get_player_dir(map[x][y], &d->cam->dir_x, &d->cam->dir_y);
	if (map_has_multiple_players(map, x, y))
		return (f_dprintf(2, "cub3d: multiple players found\n"), 1);
	dfs(map, x, y, &error);
	if (error)
		return (f_dprintf(2, "cub3d: map is not closed\n"), 1);
	d->map->map_w = get_map_width(map);
	d->map->map_h = get_map_height(map);
	d->map->map = matrix_create(d->map->map_w, d->map->map_h);
	if (!d->map->map)
		return (1);
	ascii_to_int(d->map->map, map, d->map->map_w);
	d->cam->pos_x = (double)x;
	d->cam->pos_y = (double)y;
	return (0);
}
