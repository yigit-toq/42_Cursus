/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:38:54 by ytop              #+#    #+#             */
/*   Updated: 2024/09/29 01:28:08 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nblen(long *nbr, long *tmp, int *check)
{
	int	len;

	len = 1;
	if (*nbr < 0)
	{
		*tmp = *nbr;
		*nbr *= -1;
		*check = 1;
		len += 1;
	}
	while (*tmp >= 10)
	{
		*tmp /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long	nbr;
	long	tmp;
	int		len;
	int		check;
	char	*str;

	nbr = (long)n;
	tmp = nbr;
	check = 0;
	len = ft_nblen(&nbr, &tmp, &check);
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (0);
	str[len] = '\0';
	while (len--)
	{
		str[len] = 48 + (nbr % 10);
		nbr /= 10;
	}
	if (check == 1)
		str[0] = '-';
	return (str);
}
