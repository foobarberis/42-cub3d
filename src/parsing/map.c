#include "cub3D.h"

void dfs(char **m, int x, int y, int *error)
{
	m[x][y] = FILL;
	if (x <= 0 || y <= 0 || x >= 13 || !m[x][y + 1])
		*error = 1;
	if (*error)
		return;
	if (y < (int)strlen(m[x - 1]) && m[x - 1][y] != '1' && m[x - 1][y] != FILL)
		dfs(m, x - 1, y, error);
	if (y < (int)strlen(m[x + 1]) && m[x + 1][y] != '1' && m[x + 1][y] != FILL)
		dfs(m, x + 1, y, error);
	if (m[x][y - 1] != '1' && m[x][y - 1] != FILL)
		dfs(m, x, y - 1, error);
	if (m[x][y + 1] != '1' && m[x][y + 1] != FILL)
		dfs(m, x, y + 1, error);
}

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
void get_player_dir(char c, int *dx, int *dy)
{
	if (d == 'N')
	{
		*dx = 1.0;
		*dy = 0.0;
	}
	else if (d == 'S')
	{
		*dx = -1.0;
		*dy = 0.0;
	}
	else if (d == 'E')
	{
		*dx = 0.0;
		*dy = -1.0;
	}
	else if (d == 'W')
	{
		*dx = 0.0;
		*dy = 1.0;
	}
}

static islegal(int c)
{
	return (f_isspace(c) || c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

/* check for empty lines or forbidden chars */
int map_is_valid(char **map)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (map[i])
	{
		if (!map[i][0])
			return (1);
		while (map[i][j])
		{
			if (!islegal(map[i][j])
				return (1);
			j++;
		}
		j = 0;
		i++;
	}
}

int check_mult_player(char **map, int x, int y)
{
	int nx;
	int ny;

	nx = x;
	ny = y;
	map[x][y] = FILL;
	get_player_pos(map, nx, ny);
	if (nx == -1)
		return (1);
	return (0);
}

/* returns the length of the longest line */
int get_map_width(char **map)
{
	int i;
	int curr;
	int len;

	i = 0;
	curr = 0;
	len = 0;
	while (map[i])
	{
		curr = f_strlen(map[i]);
		if (curr > len)
			len = curr;
		i++;
	}
	return (len);
}

/* returns the number of lines (one based)*/
int get_map_height(char **map)
{
	int i;

	i = 1;
	while (map[i])
		i++;
	return (i);
}

int **matrix_create(t_map *map, char **map)
{
	int i;
	int **new;

	i = 0;
	new = f_calloc(map->map_h, sizeof(int *));
	if (!new)
		return (NULL);
	while (i < map->map_h)
	{
		map[i] = new = f_calloc(map->map_w, sizeof(int *));
		if (!map[i])
			/* FIXME: Add free function */
		i++;
	}
	return (new);
}

int **ascii_to_int(int **mat, char **map)
{
	int i;
	int j;
	int **new;

	i =0;
	j =0;
	while (map[i])
	{
		while (map[i][j])
		{
			if ()
		}
			mat[i]
	}
		i++;
	new
}

/*
 * Check map for forbidden characters and empty lines
 * Check if player exists, extract player position and direction and check if there is only one player
 * Check if the map is closed
 * Convert the map to int, replacing remaining 0 and spaces with 1
*/
int parse_map(t_data *d, char **map)
{

}
