/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 00:34:15 by ytop              #+#    #+#             */
/*   Updated: 2024/10/23 00:34:15 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mini_map(t_game *game)
{
	int		h;
	int		w;

	h = 0;
	w = 0;
	game = get_game();
	if (game->count.map_hl == FALSE)
	{
		mlx_clear_window(game->mlx, game->win);
		return (0);	
	}
	while (h < game->map->height)
	{
		w = 0;
		while (w < game->map->width)
		{
			for (int y = 0; y < SIZE; y++)
			{
				for (int x = 0; x < SIZE; x++)
				{
					if (game->map->map[h][w] == WALL)
						mlx_pixel_put(game->mlx, game->win, x + (w * SIZE), y + (h * SIZE), H_W);
					if (game->map->map[h][w] == FLOOR)
						mlx_pixel_put(game->mlx, game->win, x + (w * SIZE), y + (h * SIZE), H_B);
					if (game->map->map[h][w] == game->player.dir)
						mlx_pixel_put(game->mlx, game->win, x + (w * SIZE), y + (h * SIZE), H_R);
				}
			}
			w++;
		}
		h++;
	}
	return (0);
}

static void init_img(void)
{
	t_game	*game;
	int		i;

	game = get_game();
	i = 0;
	while (i < 4)
	{
		if (!game->img->direction[i])
			error_controller("Texture path is not found.", NULL);
		game->img->direction[i] = xpm_check(game->img->direction[i]);
		i++;
	}
}

int	key_controller(int key, t_game *game)
{
	if (key == M)
	{
		game->count.map_hl = (game->count.map_hl == TRUE) ? FALSE : TRUE;
	}
	if (key == ESC)
	{
		mlx_destroy_window(game->mlx, game->win);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

void	init_game(void)
{
    t_game	*game;

    game = get_game();
    game->mlx = mlx_init();
    game->win = mlx_new_window(game->mlx, 1280, 720, NAME);
    init_img();
	mlx_key_hook(game->win, key_controller, game);
	mlx_loop_hook(game->mlx, mini_map, game);
	mlx_loop(game->mlx);
}
