/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:11:47 by ytop              #+#    #+#             */
/*   Updated: 2024/01/10 14:11:47 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DPRINTF_H
# define FT_DPRINTF_H

int	ft_dprintf(int fd, const char *string, ...);

int	ft_putchar(char character, int *lenght);

int	ft_putstr(char *string, int	*lenght);

int	ft_decimal(long number, int *lenght);

int	ft_pointer(unsigned long pointer, int *lenght);
int	ft_hexademical(unsigned long number, int *lenght, char c);

int	get_fd(int file_des);
#endif
