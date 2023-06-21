#include "cub3d.h"

int islegal(int c)
{
	return (f_isspace(c) || c == '0' || c == '1' || c == 'N'
			|| c == 'S' || c == 'E' || c == 'W');
}

int get_map_width(char **map)
{
	int i;
	size_t len;
	size_t curr;

	i = 0;
	len = 0;
	curr = 0;
	while (map[i])
	{
		curr = f_strlen(map[i]);
		if (curr > len)
			len = curr;
		i++;
	}
	return ((int)len);
}

int get_map_height(char **map)
{
	int i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}
