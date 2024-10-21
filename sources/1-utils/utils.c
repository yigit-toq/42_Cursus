/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:25:41 by ytop              #+#    #+#             */
/*   Updated: 2024/10/21 13:36:37 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*wspace_trim(char *line)
{
	char	*new;
	int		i;
	int		j;

	if (!line)
		return (NULL);
	i = 0;
	j = 0;
	while (line[i] == ' ' || (line[i] > 8 && line[i] < 14))
		i++;
	while (line[j])
		j++;
	while (line[j] == ' ' || (line[j] > 8 && line[j] < 14))
		j--;
	new = ft_substr(line, i, (j - i) + 1);
	return (new);
}
