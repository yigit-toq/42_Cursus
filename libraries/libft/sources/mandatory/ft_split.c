/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 18:05:59 by ytop              #+#    #+#             */
/*   Updated: 2024/09/30 17:13:54 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(char **str, char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] != c)
			i++;
		if (str)
			str[count] = ft_substr(s, 0, i);
		if (str && str[count] == 0)
			return (-1);
		count++;
		while (s[i] && s[i] == c)
			i++;
		s = s + i;
		i = 0;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**str;

	if (!s)
		return (0);
	while (*s && *s == c)
		s++;
	str = ft_calloc(ft_count(0, s, c) + 1, sizeof(char *));
	if (!str)
		return (0);
	if (ft_count(str, s, c) == -1)
	{
		i = 0;
		while (str[i])
		{
			gfree(str[i]);
			i++;
		}
		gfree(str);
		return (0);
	}
	return (str);
}
