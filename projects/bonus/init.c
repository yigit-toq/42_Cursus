/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 00:52:41 by ytop              #+#    #+#             */
/*   Updated: 2025/01/24 13:01:42 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

#include <mlx.h>

void	*audio_control(t_sound *sound)
{
	while (sound->loop)
	{
		play_sound(sound->path);
	}
	return (NULL);
}

void	init_sound(t_sound *sound, char *path, int loop)
{
	sound->path = path;
	sound->loop = loop;
	if (pthread_create(&sound->thread, NULL, (void *)audio_control, sound))
		error_controller("Failed to create thread.", NULL);
	else
		pthread_detach(sound->thread);
}

static int	next_frame(void)
{
	t_game	*game;

	game = get_game();
	update_position();
	swap_animation(game->player.slot->curr, game->img->next_anim);
	if (game->player.slot->fire && game->player.attack)
	{
		game->player.slot->curr->play = FALSE;
		game->img->next_anim = game->player.slot->fire;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img->bgframe.img, 0, 0);
	raycast();
	minimap();
	return (SUCCESS);
}

static void	init_img(void)
{
	t_size	size;
	t_img	*img;
	t_map	*map;
	int		i;

	img = get_game()->img;
	map = get_game()->map;
	size.x = WIN_W;
	size.y = WIN_H;
	i = 0;
	while (i < DIR_SIZE + 2)
	{
		if (!img->paths[i])
			error_controller("Texture path is not found.", NULL);
		if (i < DIR_SIZE)
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
	game->mlx = addgarbage(mlx_init());
	game->win = mlx_new_window(game->mlx, WIN_W, WIN_H, WIN_NAME);
	init_img();
	init_sound(&game->sound, "./assets/sounds/background.wav", 1);
	mlx_loop_hook(game->mlx, next_frame, NULL);
	mlx_hook(game->win, 2, 1L << 0, key_press_handler, game);
	mlx_hook(game->win, 3, 1L << 1, key_relse_handler, game);
	mlx_hook(game->win, 4, 1L << 2, mouse_press_handler, game);
	mlx_hook(game->win, 5, 1L << 3, mouse_relse_handler, game);
	mlx_hook(game->win, 6, 1L << 6, mouse_moves_handler, game);
	mlx_hook(game->win, DESTROY, 1L << DESTROY, exit_game, game);
	mlx_mouse_hook(game->win, mouse_press_handler, game);
	mlx_loop(game->mlx);
}
