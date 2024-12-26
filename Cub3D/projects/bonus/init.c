/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 00:52:41 by ytop              #+#    #+#             */
/*   Updated: 2024/12/24 20:45:54 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

#include <mlx.h>

void	animation(void)
{
	t_game	*game;

	game = get_game();
	if (game->img->weapon[1].play == FALSE)
	{
		game->player.anim = &game->img->weapon[0];
		game->img->weapon[0].play = TRUE;
	}
	update_animation(game->player.anim);
}

static int	next_frame(void)
{
	t_game	*game;

	game = get_game();
	update_position();
	mlx_put_image_to_window(game->mlx, game->win, game->img->bgframe.img, 0, 0);
	return (raycast(), minimap(), animation(), SUCCESS);
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
	img->cross = add_image(CRS_PATH, (t_size){0, 0});
	while (i < MAX_PATH)
	{
		if (!img->dir[i].img)
			error_controller("Texture path is not found.", NULL);
		img->dir[i] = add_image(img->dir[i].img, (t_size){0, 0});
		i++;
	}
	img->bgframe = add_image(NULL, size);
	size.x = map->size.x * map->mini.x;
	size.y = map->size.y * map->mini.y;
	img->minimap = add_image(NULL, size);
	img->hex[0] = rgb_to_hexa(img->rgb[0][0], img->rgb[0][1], img->rgb[0][2]);
	img->hex[1] = rgb_to_hexa(img->rgb[1][0], img->rgb[1][1], img->rgb[1][2]);
	init_animation(&img->weapon[0], (int[2]){55, 75}, 3, GUN_PATH);
	init_animation(&img->weapon[1], (int[2]){10, 55}, 3, GUN_PATH);
	img->weapon[0].play = TRUE;
	img->weapon[0].loop = TRUE;
	get_game()->player.anim = &img->weapon[0];
}

void	*audio_control()
{
	while (TRUE)
		play_sound("./assets/sounds/background.wav");
	return (NULL);
}

void	init_game(void)
{
	t_game		*game;
	// pthread_t	sound;

	game = get_game();
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIN_W, WIN_H, WIN_NAME);
	init_img();
	mlx_loop_hook(game->mlx, next_frame, NULL);
	mlx_hook(game->win, 2, 1L << 0, key_press_handler, game);
	mlx_hook(game->win, 3, 1L << 1, key_release_handler, game);
	mlx_hook(game->win, DESTROY, 1L << DESTROY, exit_game, game);
	mlx_loop(game->mlx);
}
