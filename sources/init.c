/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 00:52:41 by ytop              #+#    #+#             */
/*   Updated: 2024/12/11 18:10:22 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	render_frame(void)
{
	t_game	*game;

	game = get_game();
	update_position();
	if (game->player.move[0] || game->player.move[1])
		raycast();
	minimap_loop();
	mlx_put_image_to_window(game->mlx, game->win, game->img->minimap.img, 0, 300);
	return (SUCCESS);
}

static void	init_img(void)
{
	t_game	*game;
	int		i;

	game = get_game();
	i = 0;
	while (i < MAX_PATH)
	{
		if (!game->img->dir_symbl[i].img)
			error_controller("Texture path is not found.", NULL);
		game->img->dir_symbl[i] = add_image(game->img->dir_symbl[i].img, FALSE, 0, 0);
		i++;
	}
	game->img->minimap = add_image(NULL, TRUE, game->map->scale.x * game->map->size.x, game->map->scale.y * game->map->size.y);
}

void	init_game(void)
{
	t_game	*game;

	game = get_game();
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIN_W, WIN_H, NAME);
	init_img();
	game->img->hex[0] = rgb_to_hex(game->img->colors[0][0], game->img->colors[0][1], game->img->colors[0][2]);
	game->img->hex[1] = rgb_to_hex(game->img->colors[1][0], game->img->colors[1][1], game->img->colors[1][2]);
	mlx_loop_hook(game->mlx, render_frame, NULL);
	mlx_hook(game->win, 2, 1L << 0, key_press_handler, game);
	mlx_hook(game->win, 3, 1L << 1, key_release_handler, game);
	mlx_hook(game->win, DESTROY, 1L << DESTROY, exit_game, game);
	mlx_loop(game->mlx);
}
