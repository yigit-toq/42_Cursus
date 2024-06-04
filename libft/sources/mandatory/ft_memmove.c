/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 15:55:03 by ytop              #+#    #+#             */
/*   Updated: 2024/03/22 16:04:12 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if (!dst && !src)
		return (0);
	if (src < dst)
	{
		while (len-- > 0)
		{
			((unsigned char *)dst)[len] = ((unsigned char *)src)[len];
		}
	}
	else if (src > dst)
		ft_memcpy(dst, src, len);
	return (dst);
}
