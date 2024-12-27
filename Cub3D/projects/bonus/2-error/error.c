/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 18:54:45 by ytop              #+#    #+#             */
/*   Updated: 2024/12/27 14:00:45 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

#include <mlx.h>

void	exten_controller(char *path)
{
	char	*extension;

	extension = ft_strrchr(path, '.');
	if (!extension)
		error_controller("Wrong format  :D", NULL);
	if (ft_strcmp(extension, ".cub"))
		error_controller("Wrong extension.", NULL);
}

void	error_controller(char *message, void *pointer)
{
	if (pointer)
		return ;
	clear_garbage();
	ft_dprintf(2, C_G"----------------------------\n");
	ft_dprintf(2, C_R"Error: " C_Y"%s\n" C_E, message);
	ft_dprintf(2, C_G"----------------------------\n");
	exit(EXIT_FAILURE);
}

void	free_game(void)
{
	t_game	*game;
	int		i;

	game = get_game();
	i = 0;
	while (i < MAX_PATH)
	{
		mlx_destroy_image(game->mlx, game->img->dir[i].img);
		i++;
	}
	i = 0;
	while (i < game->img->weapon[1].total)
	{
		mlx_destroy_image(game->mlx, game->img->weapon[1].frames[i].img);
		if (i < game->img->weapon[0].total)
		mlx_destroy_image(game->mlx, game->img->weapon[0].frames[i].img);
		i++;
	}
	mlx_destroy_image(game->mlx, game->img->bgframe.img);
	mlx_destroy_image(game->mlx, game->img->minimap.img);
	mlx_destroy_image(game->mlx, game->img->cross.img);
	clear_garbage();
}

int	exit_game(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	free_game();
	exit(EXIT_SUCCESS);
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
