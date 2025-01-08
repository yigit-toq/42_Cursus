/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 18:54:45 by ytop              #+#    #+#             */
/*   Updated: 2025/01/08 17:21:40 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	mlx_destroy_window(game->mlx, game->win);
	while (i < MAX_PATH)
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
