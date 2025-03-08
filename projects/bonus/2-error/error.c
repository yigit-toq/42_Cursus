/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 18:54:45 by ytop              #+#    #+#             */
/*   Updated: 2025/03/07 17:51:57 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

#include <mlx.h>

static void	free_game(void);

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
	ft_dprintf(2, C_G"________________________________________\n");
	ft_dprintf(2, C_R"\nError: " C_Y"%s\n" C_E, message);
	ft_dprintf(2, C_G"________________________________________\n");
	ft_dprintf(2, C_E);
	exit_game(get_game(), EXIT_FAILURE);
}

int	exit_game(t_game *game, int status)
{
	if (game->img != NULL)
		free_game();
	if (game->mlx != NULL)
		mlx_destroy_display(game->mlx);
	clear_garbage();
	exit(status);
}

static void	destroy_images(t_data *frames, int total)
{
	t_game	*game;
	int		i;

	i = 0;
	game = get_game();
	while (i < total)
	{
		if (frames[i].img)
			mlx_destroy_image(game->mlx, frames[i].img);
		i++;
	}
}

static void	free_game(void)
{
	t_game	*game;

	game = get_game();
	if (game->win != NULL)
		mlx_destroy_window(game->mlx, game->win);
	destroy_images(game->img->direct, DIR);
	destroy_images(game->img->knife[0].frames, game->img->knife[0].total);
	destroy_images(game->img->knife[1].frames, game->img->knife[1].total);
	destroy_images(game->img->vandal[0].frames, game->img->vandal[0].total);
	destroy_images(game->img->vandal[1].frames, game->img->vandal[1].total);
	destroy_images(game->img->vandal[2].frames, game->img->vandal[2].total);
	destroy_images(game->img->vandal[3].frames, game->img->vandal[3].total);
	destroy_images(game->img->qskill[0].frames, game->img->qskill[0].total);
	destroy_images(game->img->qskill[1].frames, game->img->qskill[1].total);
	destroy_images(game->img->qskill[2].frames, game->img->qskill[2].total);
	destroy_images(game->img->rskill[2].frames, game->img->rskill[2].total);
	if (game->img->bgframe.img)
		mlx_destroy_image(game->mlx, game->img->bgframe.img);
	if (game->img->minimap.img)
		mlx_destroy_image(game->mlx, game->img->minimap.img);
	if (game->img->skybox.img)
		mlx_destroy_image(game->mlx, game->img->skybox.img);
	if (game->img->ground.img)
		mlx_destroy_image(game->mlx, game->img->ground.img);
	if (game->img->crossh.img)
		mlx_destroy_image(game->mlx, game->img->crossh.img);
	if (game->grp == NULL)
		return ;
	if (game->grp->door)
	{
		while (game->count.door-- > 0)
			destroy_images(game->grp->door[game->count.door].anim.frames, game->grp->door[game->count.door].anim.total);
	}
	if (game->grp->enmy)
	{
		while (game->count.enmy-- > 0)
			destroy_images(game->grp->enmy[game->count.enmy].anim.frames, game->grp->enmy[game->count.enmy].anim.total);
	}
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
//
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
//
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
