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
	destroy_images(game->img->frame, 1);
	destroy_images(game->img->dir, DIR);
}
