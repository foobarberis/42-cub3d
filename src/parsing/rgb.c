/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 13:27:52 by mbarberi          #+#    #+#             */
/*   Updated: 2023/06/28 10:36:59 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static uint32_t	rgb_extract_color(char *color)
{
	uint32_t	r;

	r = 0;
	r = r | (uint8_t)f_atoi(color);
	color = f_strchr(color, ',') + 1;
	r = (r << 8) | (uint8_t)f_atoi(color);
	color = f_strchr(color, ',') + 1;
	r = (r << 8) | (uint8_t)f_atoi(color);
	return (r);
}

static int	rgb_has_forbidden_char(char *s)
{
	while (*s)
	{
		if (!(f_isdigit(*s) || *s == ','))
			return (f_dprintf(2, "cub3d: %c: forbidden character\n", *s), 1);
		s++;
	}
	return (0);
}

static int	rgb_check_overflow(char *s, int len)
{
	int		l;
	char	*p;

	p = s;
	while (1)
	{
		l = (int)f_strlen(s);
		if (l < 1 || l > 3 || f_atoi(s) > 255)
			return (f_dprintf(2, ERR_RGB_RANGE), 1);
		while (*s)
			s++;
		if ((int)(s - p) >= len)
			break ;
		else
			*s = ',';
		s += 1;
	}
	return (0);
}

/* check if the line represents a valid RGB value converts it to int if it is.*/
int	parse_color(char *s, int len, uint32_t *color)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
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
