/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 00:52:41 by ytop              #+#    #+#             */
/*   Updated: 2024/12/27 17:51:16 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

#include <mlx.h>

void	swap_animation(t_anim *c_anim, t_anim *n_anim)
{
	t_game	*game;

	game = get_game();
	if (c_anim->play == FALSE)
	{
		game->player.anim = n_anim;
		n_anim->play = TRUE;
	}
}

void	animation(void)
{
	t_game	*game;

	game = get_game();
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
	init_animation(&img->vandal[0], (int[2]){0, 20}, 3, GUN_IDLE_PATH);
	init_animation(&img->vandal[1], (int[2]){0, 45}, 3, GUN_SKIN_PATH);
	init_animation(&img->qskill[0], (int[2]){0, 45}, 3, QSK_IDLE_PATH);
	init_animation(&img->qskill[1], (int[2]){0, 05}, 3, QSK_PUSH_PATH);

	init_animation(&img->knife[0], (int[2]){0, 10}, 3, KNF_IDLE_PATH);
	init_animation(&img->knife[1], (int[2]){0, 15}, 3, KNF_SKIN_PATH);
	img->vandal[0].play = TRUE;
	img->vandal[0].loop = TRUE;
	get_game()->player.anim = &img->vandal[0];
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
	mlx_loop(game->mlx);
}
