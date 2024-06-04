/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:38:54 by ytop              #+#    #+#             */
/*   Updated: 2024/03/22 17:11:26 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

static int	ft_nblen(long *nb, long *tmp, int *check)
{
	int	len;

	len = 1;
	if (*nb < 0)
	{
		*nb *= -1;
		*tmp = *nb;
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
	long	nb;
	long	tmp;
	int		len;
	int		check;
	char	*str;

	nb = (long)n;
	tmp = nb;
	check = 0;
	len = ft_nblen(&nb, &tmp, &check);
	str = (char *)malloc(len + 1);
	if (!str)
		return (0);
	str[len] = '\0';
	while (len--)
	{
		str[len] = 48 + (nb % 10);
		nb /= 10;
	}
	if (check == 1)
		str[0] = '-';
	return (str);
}
