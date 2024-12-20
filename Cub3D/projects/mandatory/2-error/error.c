/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 18:54:45 by ytop              #+#    #+#             */
/*   Updated: 2024/12/16 14:00:33 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	exten_controller(char *path)
{
	char	*extension;

	extension = ft_strrchr(path, '.');
	if (!extension)
		error_controller("Wrong format. :D", NULL);
	if (ft_strcmp(extension, ".cub"))
		error_controller("Wrong extension.", NULL);
}

void	error_controller(char *message, void *pointer)
{
	if (pointer)
		return ;
	ft_dprintf(2, C_R"Error: " C_Y"%s\n" C_E, message);
	exit(EXIT_FAILURE);
}
