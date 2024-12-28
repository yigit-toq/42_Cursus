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

void	animation(void)
{
	t_game	*game;

	game = get_game();
	update_animation(game->player.slot->curr);
}

static int	next_frame(void)
{
	t_game	*game;

	game = get_game();
	update_position();
	mlx_put_image_to_window(game->mlx, game->win, game->img->bgframe.img, 0, 0);
	return (raycast(), minimap(), animation(), SUCCESS);
}

void	add_slot(t_slot *slot, int index, int curr, t_anim *anim, int *check)
{
	slot->index = index;
	if (check[0])
		slot->take = &anim[0];
	if (check[1])
		slot->idle = &anim[1];
	if (check[2])
		slot->skin = &anim[2];
	if (check[3])
		slot->fire = &anim[3];
	if (check[curr])
		slot->curr = &anim[curr];
	slot->curr->loop = TRUE;
}

void	init_slot(void)
{
	t_game	*game;

	game = get_game();
	init_animation(&game->img->knife[0], (int[2]){0, 15}, 2, KNF_TAKE_PATH);
	init_animation(&game->img->knife[1], (int[2]){0, 10}, 2, KNF_IDLE_PATH);

	init_animation(&game->img->vandal[1], (int[2]){0, 20}, 2, GUN_IDLE_PATH);
	init_animation(&game->img->vandal[2], (int[2]){0, 45}, 2, GUN_SKIN_PATH);

	init_animation(&game->img->qskill[0], (int[2]){0, 10}, 2, QSK_TAKE_PATH);
	init_animation(&game->img->qskill[1], (int[2]){0, 35}, 2, QSK_IDLE_PATH);
	init_animation(&game->img->qskill[3], (int[2]){0, 05}, 2, QSK_PUSH_PATH);

	add_slot(&game->player.slots[0], 0, 1, game->img->knife, (int[4]){1, 1, 0, 0});
	add_slot(&game->player.slots[1], 1, 1, game->img->vandal, (int[4]){0, 1, 1, 0});
	add_slot(&game->player.slots[2], 2, 1, game->img->qskill, (int[4]){1, 1, 0, 1});

	game->player.slot = &game->player.slots[0];

	game->player.slot->curr->play = TRUE;
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
	mlx_loop(game->mlx);
}
