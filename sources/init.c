/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 00:52:41 by ytop              #+#    #+#             */
/*   Updated: 2024/11/26 16:36:56 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	render_frame(void)
{
	return (minimap_loop(), update_position(), SUCCESS);
}

static void	init_img(void)
{
	t_game	*game;
	int		i;

	game = get_game();
	i = 0;
	while (i < MAX_PATH)
	{
		if (!game->img->dir_syml[i])
			error_controller("Texture path is not found.", NULL);
		game->img->dir_syml[i] = open_xpm(game->img->dir_syml[i]);
		i++;
	}
}

void	init_game(void)
{
	t_game	*game;

	game = get_game();
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, NAME);
	init_img();
	mlx_loop_hook(game->mlx, render_frame, NULL);
	mlx_hook(game->win, 2, 1L << 0, key_press_handler, game);
	mlx_hook(game->win, 3, 1L << 1, key_release_handler, game);
	mlx_hook(game->win, DESTROY, 1L << DESTROY, exit_game, game);
	mlx_loop(game->mlx);
}
