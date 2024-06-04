/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 14:45:28 by ytop              #+#    #+#             */
/*   Updated: 2024/03/22 16:04:36 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*array;

	array = (unsigned char *)b;
	while (len > 0)
	{
		array[len - 1] = c;
		len--;
	}
	return (b);
}
