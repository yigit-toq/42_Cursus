/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 15:07:52 by ytop              #+#    #+#             */
/*   Updated: 2024/03/22 16:05:36 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

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
	str = (char *)malloc(sizeof(char) * (len + 1));
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
