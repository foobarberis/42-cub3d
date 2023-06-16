#include "cub3d.h"

int islegal(int c)
{
	return (f_isspace(c) || c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

/* returns the length of the longest line */
int get_map_width(char **map)
{
	int i;
	size_t curr;
	size_t len;

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
	return ((int)len);
}

/* returns the number of lines (one based)*/
int get_map_height(char **map)
{
	int i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}
