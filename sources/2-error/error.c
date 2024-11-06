/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 18:54:45 by ytop              #+#    #+#             */
/*   Updated: 2024/10/22 14:33:59 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_scene(int fd)
{
	(void)fd;
}

void	save_scene(void)
{
	if (get_game()->save)
	{
		ft_printf("Save\n");
	}
}

int	arg_controller(char **argv)
{
	t_game	*game;
	int		load;
	int		i;

	game = get_game();
	while (argv[i + 1])
	{
		while (!ft_strcmp(argv[i], "--load") || !ft_strcmp(argv[i], "-l"))
		{
			load = TRUE;
			i++;
		}
		if (!ft_strcmp(argv[i], "--save") || !ft_strcmp(argv[i], "-s"))
		{
			game->save = TRUE;
		}
		if (load)
		{
			if (exten_controller(argv[i]) == 2)
				load_scene(open_file(argv[i]));
			else
				error_controller("Invalid file extension.", NULL);
		}
		i++;
	}
	return (i);
}

int	exten_controller(char *path)
{
	char	*extension;

	extension = ft_strrchr(path, '.');
	if (!extension)
		return (-1);
	if (!ft_strcmp(extension, ".cub"))
		return (1);
	if (!ft_strcmp(extension, ".save"))
		return (2);
	return (-2);
}

void	error_controller(char *message, void *pointer)
{
	if (pointer)
		return ;
	ft_dprintf(2, C_R "Error: " C_Y "%s\n" C_E, message);
	exit(EXIT_FAILURE);
}
