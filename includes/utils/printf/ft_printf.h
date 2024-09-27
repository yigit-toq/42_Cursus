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

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

int	ft_printf(const char *string, ...);

int	ft_decimal(long number, int *lenght);

int	ft_putstr(char *string, int	*lenght);

int	ft_putchar(char character, int *lenght);

int	ft_pointer(unsigned long pointer, int *lenght);
int	ft_hexademical(unsigned long number, int *lenght, char c);
#endif
