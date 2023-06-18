#include "cub3d.h"

static uint32_t rgb_extract_color(char *color)
{
	uint8_t r;
	uint8_t g;
	uint8_t b;

	r = (uint8_t)f_atoi(color);
	color = f_strchr(color, ',') + 1;
	g = (uint8_t)f_atoi(color);
	color = f_strchr(color, ',') + 1;
	b = (uint8_t)f_atoi(color);
	return ((r << 16) | (g << 8) | b);
}

static int rgb_has_forbidden_char(char *s)
{
	while (*s)
	{
		if (!(f_isdigit(*s) || *s == ','))
			return (f_dprintf(2, "cub3d: %c: forbidden character\n", *s), 1);
		s++;
	}
	return (0);
}

static int rgb_check_overflow(char *s, int len)
{
	int l;
	char *p;

	p = s;
	while (1)
	{
		l = (int)f_strlen(s);
		if (l < 1 || l > 3 || f_atoi(s) > 255)
			return (f_dprintf(2, "cub3d: %s: RGB value is not in range 0-255\n"), 1);
		while (*s)
			s++;
		if ((int)(s - p) >= len)
			break;
		else
			*s = ',';
		s += 1;
	}
	return (0);
}

/* check if the line represents a valid RGB value converts it to int if it is.*/
int parse_color(char *s, uint32_t *color)
{
	int i;
	int c;
	int len;

	i = 0;
	c = 0;
	len = (int)f_strlen(s);
	if (len < 3)
		return (1);
	if (rgb_has_forbidden_char(s))
		return (1);
	while (i < len)
	{
		if (s[i] == ',')
		{
			s[i] = '\0';
			c++;
		}
		i++;
	}
	if (c != 2)
		return (f_dprintf(2, "cub3d: missing RGB value\n"), 1);
	if (rgb_check_overflow(s, len))
		return (1);
	*color = rgb_extract_color(s);
	return (0);
}
