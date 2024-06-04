/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 14:20:26 by ytop              #+#    #+#             */
/*   Updated: 2024/02/16 14:32:58 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	index;

	index = 0;
	while (str[index])
		index++;
	return (index);
}

char	*ft_strdup(const char *str)
{
	char	*result;
	size_t	index;

	index = 0;
	result = malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	while (str[index])
	{
		result[index] = str[index];
		index++;
	}
	result[index] = '\0';
	return (result);
}

char	*ft_strjoin(char const *str1, char const *str2)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	result = (char *)malloc(ft_strlen(str1) + ft_strlen(str2) + 1);
	if (result == 0)
		return (0);
	while (str1[i])
		result[j++] = str1[i++];
	i = 0;
	while (str2[i])
		result[j++] = str2[i++];
	result[j] = '\0';
	return (result);
}

char	*ft_substr(char const *str, unsigned int start, size_t lenght)
{
	char			*result;
	unsigned int	strlen;
	unsigned int	index;

	strlen = ft_strlen(str);
	if (!str)
		return (0);
	if (strlen < start)
		lenght = 0;
	if (strlen - start < (unsigned int)lenght)
		lenght = (size_t)(strlen - start);
	result = (char *)malloc(lenght + 1);
	if (!result)
		return (0);
	index = 0;
	while ((size_t)index < lenght)
	{
		result[index] = str[index + start];
		index++;
	}
	result[index] = '\0';
	return (result);
}
