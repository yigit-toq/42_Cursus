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

#include "cub3d_bonus.h"

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

// int	arg_check(char *arg)
// {
// 	if (!ft_strcmp(arg, "--load") || !ft_strcmp(arg, "-l"))
// 	{
// 		return (1);
// 	}
// 	if (!ft_strcmp(arg, "--save") || !ft_strcmp(arg, "-s"))
// 	{
// 		return (2);
// 	}
// 	return (0);
// }

// int	arg_controller(char **argv)
// {
// 	t_game	*game;
// 	int		i;
//
// 	i = 0;
// 	game = get_game();
// 	while (argv[i + 1] && arg_check(argv[i]))
// 	{
// 		if (arg_check(argv[i]) == 1)
// 			game->load = TRUE;
// 		else
// 			game->save = TRUE;
// 		i++;
// 	}
// 	if (game->load)
// 	{
// 		if (exten_controller(argv[i]) == 2)
// 			load_scene(open_file(argv[i]));
// 		else
// 			error_controller("Usage: ./cub3d <map.save>", NULL);
// 	}
// 	return (i);
// }

// int	exten_controller(char *path)
// {
// 	char	*extension;
//
// 	extension = ft_strrchr(path, '.');
// 	if (!extension)
// 		return (0);
// 	else
// 	{
// 		if (!ft_strcmp(extension,  ".cub"))
// 			return (1);
// 		if (!ft_strcmp(extension, ".save"))
// 			return (2);
// 	}
// 	return (0);
// }
