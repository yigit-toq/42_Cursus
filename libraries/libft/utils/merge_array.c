/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_arrays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:57:37 by ytop              #+#    #+#             */
/*   Updated: 2024/09/27 15:57:37 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*merge_array(char **arr)
{
	char	*new;
	int		words;
	int		letters;

	words = 0;
	letters = 0;
	while (arr && arr[words])
	{
		letters += ft_strlen(arr[words]);
		words++;
	}
	new = ft_calloc(letters + 1, sizeof(char));
	if (!new)
		return (0);
	words = 0;
	while (arr && arr[words])
	{
		ft_strlcat(new, arr[words], letters + 1);
		words++;
	}
	new[letters] = 0;
	return (new);
}
