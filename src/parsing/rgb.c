#include "cub3d.h"

int rgb_has_forbidden_char(char *s)
{
	while (*s)
	{
		if (!f_isdigit(*s) || *s != ',')
			return (f_dprintf(2, "cub3d: %c: forbidden character\n", *s), 1);
		s++;
	}
	return (0);
}

int rgb_check_overflow(char *s, int len)
{
	int i;
	int l;
	int color;

	while (1)
	{
		i = 0;
		l = (int)f_strlen(s);
		if (l > 3 || l < 1)
			return (f_dprintf(2, "cub3d: %s: RGB value is not in range 0-255\n"), 1);
		color = f_atoi(s);
		if (color > 255)
			return (f_dprintf(2, "cub3d: %s: RGB value is not in range 0-255\n"), 1);
		while (s[i])
			i++;
		if (i == len)
			break;
		else
			i++;
		s += i;
	}
	return (0);
}

int check_color(char *s)
{
	int i;
	int c;
	int len;

	i = 0;
	c = 0;
	len = (int)f_strlen(s);
	while (i < len)
	{
		if (s[i] == ',')
		{
			s[i] = '\0';
			c++;
		}
		i++;
	}
	if (c != 3)
		return (f_dprintf(2, "cub3d: missing RGB value\n"), 1);
	if (rgb_check_overflow(s, len))
		return (1);
	return (0);
}
