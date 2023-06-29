/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 13:27:52 by mbarberi          #+#    #+#             */
/*   Updated: 2023/06/29 08:19:23 by mbarberi         ###   ########.fr       */
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
			return (f_dprintf(2, ERR_RGB_RANGE, s), 1);
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

static int	count_commas(char *s, int len)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (i < len)
	{
		if (s[i] == ',')
		{
			s[i] = '\0';
			c++;
		}
		i++;
	}
	return (c);
}

int	parse_color(char *s, int len, int32_t *color)
{
	if (len < 3)
		return (1);
	if (rgb_has_forbidden_char(s))
		return (1);
	if (count_commas(s, len) != 2)
		return (f_dprintf(2, "cub3d: missing RGB value\n"), 1);
	if (rgb_check_overflow(s, len))
		return (1);
	if (*color != -1)
		return (f_dprintf(2, ERR_DUPID), 1);
	*color = rgb_extract_color(s);
	return (0);
}
