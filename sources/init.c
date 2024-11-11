/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 00:52:41 by ytop              #+#    #+#             */
/*   Updated: 2024/11/11 17:59:03 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	render_frame(void)
{
	t_game	*game;

	minimap_loop();
	game = get_game();
	if (game->player.move[0] == FALSE)
	{
		update_position(&game->player.position.y, &game->player.axis.y, -1);
	}
	if (game->player.move[1] == FALSE)
	{
		update_position(&game->player.position.x, &game->player.axis.x, +1);
	}
	return (delay(30), SUCCESS);
}

static void	init_img(void)
{
	t_game	*game;
	int		i;

	game = get_game();
	i = 0;
	while (i < MAX_PATH)
	{
		if (!game->img->direction[i])
			error_controller("Texture path is not found.", NULL);
		game->img->direction[i] = open_xpm(game->img->direction[i]);
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
	mlx_hook(game->win, KEY_RELEASE, 1L << 1, key_release_handler, NULL);
	mlx_hook(game->win, KEY_PRESS, 1L << 0, key_press_handler, NULL);
	mlx_hook(game->win, DESTROY, 1L << DESTROY, exit_game, NULL);
	mlx_loop_hook(game->mlx, render_frame, game);
	mlx_loop(game->mlx);
}
