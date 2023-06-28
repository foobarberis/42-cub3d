/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_strchrnul.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 10:12:14 by mbarberi          #+#    #+#             */
/*   Updated: 2023/06/28 10:40:06 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlc.h"

/**
 * @brief The strchrnul() function is like strchr() except that if c is not
 * found in s, then it returns a pointer to the null byte at the end of s,
 * rather than NULL.
 * @param s The string to search.
 * @param c The character to find.
 * @return The strchrnul() function returns a pointer to the matched
 * character, or a pointer to the null byte at the end of s (i.e.,
 * s+strlen(s)) if the character is not found.
 */
char	*f_strchrnul(const char *s, int c)
{
	while (*s && *(unsigned char *)s != c)
		s++;
	return ((char *)s);
}
