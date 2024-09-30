/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 15:07:52 by ytop              #+#    #+#             */
/*   Updated: 2024/09/29 01:29:25 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	strlen;
	unsigned int	i;

	i = 0;
	strlen = ft_strlen(s);
	if (!s)
		return (0);
	if (strlen < start)
		len = 0;
	if (strlen - start < (unsigned int)len)
		len = (size_t)(strlen - start);
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (0);
	while ((size_t)i < len)
	{
		str[i] = s[i + start];
		i++;
	}
	str[i] = '\0';
	return (str);
}
