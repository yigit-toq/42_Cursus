/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:48:00 by ytop              #+#    #+#             */
/*   Updated: 2024/10/16 17:18:55 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./printf/ft_dprintf.h"
#include <unistd.h>

int	fd_putchar(char character, int *lenght)
{
	int	error;

	error = write(get_fd(-1), &character, 1);
	if (error == 1)
		*lenght += 1;
	return (error);
}

int	fd_putstr(char *string, int	*lenght)
{
	int	index;
	int	error;

	index = 0;
	if (!string)
	{
		error = fd_putstr("(null)", lenght);
		if (error == 6)
			*lenght += error;
		return (error);
	}
	while (string[index])
	{
		if (fd_putchar(string[index++], lenght) == -1)
			return (-1);
	}
	return (1);
}

int	fd_decimal(long number, int *lenght)
{
	if (number < 0)
	{
		if (fd_putchar(45, lenght) == -1)
			return (-1);
		number = -number;
	}
	if (number < 10)
	{
		if (fd_putchar(number + 48, lenght) == -1)
			return (-1);
	}
	if (number >= 10)
	{
		if (fd_decimal(number / 10, lenght) == -1)
			return (-1);
		fd_decimal(number % 10, lenght);
	}
	return (1);
}

int	fd_hexademical(unsigned long number, int *lenght, char c)
{
	char	string[16];
	char	*character;
	int		index;

	index = 0;
	if (c == 'x')
		character = "0123456789abcdef";
	else
		character = "0123456789ABCDEF";
	if (!number)
	{
		if (fd_putchar('0', lenght) == -1)
			return (-1);
	}
	while (number)
	{
		string[index++] = character[number % 16];
		number /= 16;
	}
	while (index--)
	{
		if (fd_putchar(string[index], lenght) == -1)
			return (-1);
	}
	return (1);
}

int	fd_pointer(unsigned long pointer, int *lenght)
{
	if (fd_putstr("0x", lenght) == -1)
		return (-1);
	return (fd_hexademical(pointer, lenght, 'x'));
}
