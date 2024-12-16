/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 00:52:41 by ytop              #+#    #+#             */
/*   Updated: 2024/12/16 17:23:01 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	render_frame(void)
{
	t_game	*game;

	game = get_game();
	update_position();
	minimap_loop();
	raycast();
	mlx_put_image_to_window(game->mlx, game->win, game->img->frame.img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->img->minimap.img, 0, WIN_H - (game->map->size.y * game->map->scale.y));
	return (SUCCESS);
}

static void	init_img(void)
{
	t_img	*img;
	t_map	*map;
	t_size	size;
	int		i;

	img	= get_game()->img;
	map = get_game()->map;
	size.x = WIN_W;
	size.y = WIN_H;
	i = 0;
	while (i < MAX_PATH)
	{
		if (!img->dir_symbl[i].img)
			error_controller("Texture path is not found.", NULL);
		img->dir_symbl[i] = add_image(img->dir_symbl[i].img, (t_size){0, 0});
		i++;
	}
	img->frame = add_image(NULL, size);
	size.x = map->scale.x * map->size.x;
	size.y = map->scale.y * map->size.y;
	img->minimap = add_image(NULL, size);
	img->hex_color[0] = rgb_to_hex(img->rgb_color[0][0], img->rgb_color[0][1], img->rgb_color[0][2]);
	img->hex_color[1] = rgb_to_hex(img->rgb_color[1][0], img->rgb_color[1][1], img->rgb_color[1][2]);
}

void	init_game(void)
{
	t_game	*game;

	game = get_game();
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIN_W, WIN_H, NAME);
	init_img();
	mlx_loop_hook(game->mlx, render_frame, NULL);
	mlx_hook(game->win, 2, 1L << 0, key_press_handler, game);
	mlx_hook(game->win, 3, 1L << 1, key_release_handler, game);
	mlx_hook(game->win, DESTROY, 1L << DESTROY, exit_game, game);
	mlx_loop(game->mlx);
}
