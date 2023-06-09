/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 18:19:38 by mbarberi          #+#    #+#             */
/*   Updated: 2023/02/06 17:28:20 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlc.h"

/**
 * @brief Produce output according to a format specified in the string s and
 * write this output to stdout.
 * @param s The format string.
 * @return The number of characters printed if the function returns
 * successfully, else it returns a negative value.
 */
int	f_printf(const char *s, ...)
{
	ssize_t	r;
	va_list	ap;

	if (!s || write(STDOUT_FILENO, 0, 0) < 0)
		return (-1);
	if (!*s)
		return (0);
	r = 0;
	va_start(ap, s);
	while (*s)
	{
		if (*s != '%')
			r += printf__putchar(STDOUT_FILENO, *s);
		else
			r += printf__arg(STDOUT_FILENO, *++s, &ap);
		if (!*s++)
			break ;
	}
	va_end(ap);
	return ((int)r);
}
