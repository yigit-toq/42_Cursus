/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:11:47 by ytop              #+#    #+#             */
/*   Updated: 2024/10/16 16:04:05 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DPRINTF_H
# define FT_DPRINTF_H

int	ft_dprintf(int fd, const char *string, ...);

int	fd_putchar(char character, int *lenght);

int	fd_decimal(long number, int *lenght);

int	fd_putstr(char *string, int *lenght);

int	fd_pointer(unsigned long pointer, int *lenght);

int	fd_hexademical(unsigned long number, int *lenght, char c);

int	get_fd(int file_des);
#endif
