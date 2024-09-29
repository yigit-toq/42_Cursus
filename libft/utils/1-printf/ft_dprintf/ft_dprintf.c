/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:48:13 by ytop              #+#    #+#             */
/*   Updated: 2024/09/27 17:48:13 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/printf/ft_dprintf.h"
#include <stdarg.h>

static int	ft_format_checker(char format, va_list args, int *lenght)
{
	if (format == 'c')
		return (ft_putchar(va_arg(args, int), lenght));
	else if (format == 's')
		return (ft_putstr(va_arg(args, char *), lenght));
	else if (format == 'd' || format == 'i')
		return (ft_decimal(va_arg(args, int), lenght));
	else if (format == 'u')
		return (ft_decimal(va_arg(args, unsigned int), lenght));
	else if (format == 'x')
		return (ft_hexademical(va_arg(args, unsigned int), lenght, 'x'));
	else if (format == 'X')
		return (ft_hexademical(va_arg(args, unsigned int), lenght, 'X'));
	else if (format == 'p')
		return (ft_pointer(va_arg(args, unsigned long), lenght));
	else if (format == '%')
		return (ft_putchar('%', lenght));
	return (0);
}

int	ft_dprintf(int fd, const char *string, ...)
{
	va_list	args;
	int		index;
	int		lenght;
	int		error;

	index = 0;
	lenght = 0;
	get_fd(fd);
	va_start(args, string);
	while (string[index])
	{
		if (string[index] == '%')
		{
			error = ft_format_checker(string[++index], args, &lenght);
			if (error > 0)
				index++;
			else if (error < 0)
				return (-1);
		}
		else
			if (ft_putchar(string[index++], &lenght) == -1)
				return (-1);
	}
	va_end(args);
	return (lenght);
}

int	get_fd(int file_des)
{
	static int	fd;

	if (file_des != -1)
		fd = file_des;
	return (fd);
}
