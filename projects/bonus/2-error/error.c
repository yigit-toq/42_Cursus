/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 18:54:45 by ytop              #+#    #+#             */
/*   Updated: 2024/12/30 15:14:30 by ytop             ###   ########.fr       */
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
	ft_dprintf(2, C_G"________________________________________\n");
	ft_dprintf(2, C_R"\nError: " C_Y"%s\n" C_E, message);
	ft_dprintf(2, C_G"________________________________________\n");
	ft_dprintf(2, C_E);
	exit(EXIT_FAILURE);
}

void	free_game(void)
{
	t_game	*game;
	int		i;

	game = get_game();
	i = 0;
	mlx_destroy_window(game->mlx, game->win);
	while (i < DIR_SIZE)
	{
		mlx_destroy_image(game->mlx, game->img->direct[i].img);
		mlx_destroy_image(game->mlx, game->img->skybox[i].img);
		i++;
	}
	i = 0;
	while (i < game->img->knife[0].total)
	{
		mlx_destroy_image(game->mlx, game->img->knife[0].frames[i].img);
		if (i < game->img->knife[1].total)
			mlx_destroy_image(game->mlx, game->img->knife[1].frames[i].img);
		i++;
	}
	i = 0;
	while (i < game->img->vandal[2].total)
	{
		mlx_destroy_image(game->mlx, game->img->vandal[2].frames[i].img);
		if (i < game->img->vandal[0].total)
			mlx_destroy_image(game->mlx, game->img->vandal[0].frames[i].img);
		if (i < game->img->vandal[1].total)
			mlx_destroy_image(game->mlx, game->img->vandal[1].frames[i].img);
		if (i < game->img->vandal[3].total)
			mlx_destroy_image(game->mlx, game->img->vandal[3].frames[i].img);
		i++;
	}
	i = 0;
	while (i < game->img->qskill[1].total)
	{
		mlx_destroy_image(game->mlx, game->img->qskill[1].frames[i].img);
		if (i < game->img->qskill[0].total)
			mlx_destroy_image(game->mlx, game->img->qskill[0].frames[i].img);
		if (i < game->img->qskill[3].total)
			mlx_destroy_image(game->mlx, game->img->qskill[3].frames[i].img);
		i++;
	}
	i = 0;
	while (i < game->img->rskill[3].total)
	{
		mlx_destroy_image(game->mlx, game->img->rskill[3].frames[i].img);
		i++;
	}
	while (game->count.door > 0)
	{
		i = 0;
		game->count.door--;
		while (i < game->door[game->count.door].anim.total)
		{
			mlx_destroy_image(game->mlx, game->door[game->count.door].anim.frames[i].img);
			i++;
		}
		
	}
	while (game->count.enemy > 0)
	{
		i = 0;
		game->count.enemy--;
		while (i < game->enemy[game->count.enemy].anim.total)
		{
			mlx_destroy_image(game->mlx, game->enemy[game->count.enemy].anim.frames[i].img);
			i++;
		}
	}
	mlx_destroy_image(game->mlx, game->img->bgframe.img);
	mlx_destroy_image(game->mlx, game->img->minimap.img);
	mlx_destroy_image(game->mlx, game->img->crossh.img);
	mlx_destroy_image(game->mlx, game->img->ground.img);
}

int	exit_game(t_game *game)
{
	free_game();
	mlx_destroy_display(game->mlx);
	clear_garbage();
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
