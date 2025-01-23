/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 00:52:41 by ytop              #+#    #+#             */
/*   Updated: 2025/01/23 16:28:10 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

#include <mlx.h>

static int	next_frame(void)
{
	t_game	*game;

	game = get_game();
	update_position();
	swap_animation(game->player.slot->curr, game->img->next_anim);
	mlx_put_image_to_window(game->mlx, game->win, game->img->bgframe.img, 0, 0);
	return (raycast(), minimap(), SUCCESS);
}

static void	init_img(void)
{
	t_img	*img;
	t_map	*map;
	t_size	size;
	int		i;

	img = get_game()->img;
	map = get_game()->map;
	size.x = WIN_W;
	size.y = WIN_H;
	i = 0;
	while (i < DIR_SIZE)
	{
		if (!img->paths[i])
			error_controller("Texture path is not found.", NULL);
		img->dir[i] = add_image(img->paths[i], (t_size){0, 0});
		i++;
	}
	img->crossh = add_image(img->paths[4], (t_size){0, 0});
	img->ground = add_image(img->paths[5], (t_size){0, 0});
	img->bgframe = add_image(NULL, size);
	size.x = map->size.x * map->mini.x;
	size.y = map->size.y * map->mini.y;
	img->minimap = add_image(NULL, size);
	img->hex[0] = rgb_to_hexa(img->rgb[0][0], img->rgb[0][1], img->rgb[0][2]);
	img->hex[1] = rgb_to_hexa(img->rgb[1][0], img->rgb[1][1], img->rgb[1][2]);
	init_slot();
}

void	init_game(void)
{
	t_game		*game;

	game = get_game();
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIN_W, WIN_H, WIN_NAME);
	init_img();
	mlx_loop_hook(game->mlx, next_frame, NULL);
	mlx_hook(game->win, 2, 1L << 0, key_press_handler, game);
	mlx_hook(game->win, 3, 1L << 1, key_release_handler, game);
	mlx_hook(game->win, DESTROY, 1L << DESTROY, exit_game, game);
	mlx_hook(game->win, MOUSE_H, 1L << MOUSE_H, mouse_move, game);
	mlx_loop(game->mlx);
}
