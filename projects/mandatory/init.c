/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 00:52:41 by ytop              #+#    #+#             */
/*   Updated: 2025/03/07 18:39:09 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_mandatory.h"

#include <mlx.h>

static int	loop_frame(void)
{
	t_game	*game;

	game = get_game();
	update_position();
	mlx_put_image_to_window(game->mlx, game->win, game->img->frame.img, 0, 0);
	return (raycast(), SUCCESS);
}

static void	init_img(void)
{
	t_img	*img;
	t_size	size;
	int		i;

	img = get_game()->img;
	size.x = WIN_W;
	size.y = WIN_H;
	i = 0;
	while (i < DIR) // bakılacak
	{
		if (img->paths[i])
			img->dir[i] = add_image(img->paths[i], (t_size){0, 0});
		if (img->dir[i].img == NULL)
			error_controller("Texture path is not found :D", NULL);
		i++;
	}
	img->frame = add_image(NULL, size);
	img->hex[0] = rgb_to_hexa(img->rgb[0][0], img->rgb[0][1], img->rgb[0][2]);
	img->hex[1] = rgb_to_hexa(img->rgb[1][0], img->rgb[1][1], img->rgb[1][2]);
}

void	init_game(void)
{
	t_game	*game;

	game = get_game();
	game->mlx = addgarbage(mlx_init());
	error_controller("Mlx initialization failed", game->mlx);
	game->win = mlx_new_window(game->mlx, WIN_W, WIN_H, WIN);
	error_controller("Window creation failed :D", game->win);
	init_img();
	mlx_loop_hook(game->mlx, loop_frame, NULL);
	mlx_hook(game->win, 2, 1L << 0, key_press_handler, game);
	mlx_hook(game->win, 3, 1L << 1, key_release_handler, game);
	mlx_hook(game->win, DESTROY, 1L << DESTROY, exit_game, game);
	mlx_loop(game->mlx);
}
