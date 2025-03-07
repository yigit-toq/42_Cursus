/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 18:54:45 by ytop              #+#    #+#             */
/*   Updated: 2025/03/07 18:36:45 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_mandatory.h"

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
	t_game	*game;

	if (pointer)
		return ;
	game = get_game();
	if (game->mlx)
		mlx_destroy_display(game->mlx);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	clear_garbage();
	ft_dprintf(2, C_G"----------------------------\n");
	ft_dprintf(2, C_R"Error: " C_Y"%s\n" C_E, message);
	ft_dprintf(2, C_G"----------------------------\n");
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
	while (i < DIR)
	{
		mlx_destroy_image(game->mlx, game->img->dir[i].img);
		i++;
	}
	mlx_destroy_image(game->mlx, game->img->frame.img);
}

int	exit_game(t_game *game)
{
	free_game();
	mlx_destroy_display(game->mlx);
	clear_garbage();
	exit(EXIT_SUCCESS);
}
