/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 22:47:50 by ytop              #+#    #+#             */
/*   Updated: 2025/03/07 18:42:48 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_mandatory.h"

char	**copy_array(char **array, int size)
{
	char	**copy;
	int		i;

	i = 0;
	copy = ft_calloc(size + 1, sizeof(char *));
	error_controller("Memory allocation failed.", copy);
	while (array[i])
	{
		copy[i] = ft_strdup(array[i]);
		i++;
	}
	return (copy);
}
