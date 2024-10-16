/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 18:16:31 by ytop              #+#    #+#             */
/*   Updated: 2024/10/16 18:21:34 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	extension_controller(char *path)
{
	char	*extension;
	char	*name;
	int		result;

	name = ft_strdup(path);
	error_controller("Malloc not allocated.", name);
	extension = ft_strrchr(name, '.');
	if (!extension)
	{
		free(name);
		error_controller("Wrong format.", 0);
	}
	if (ft_strlen(extension) == 4)
		result = ft_strncmp(extension, ".cub", 4);
	else
		result = 1;
	free(name);
	if (result)
		error_controller("Wrong extension.", 0);
	return ;
}

void	error_controller(char *message, void *allocate)
{
	if (allocate)
		return ;
	clear_garbage();
	exit(EXIT_FAILURE);
}
