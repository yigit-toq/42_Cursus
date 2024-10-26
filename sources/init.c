/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 00:52:41 by ytop              #+#    #+#             */
/*   Updated: 2024/10/24 00:52:41 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_tile(int x, int y, int color)
{
	t_game	*game;
	int		h;
	int		w;

	game = get_game();
	h = 0;
	while (h < SIZE)
	{
		w = 0;
		while (w < SIZE)
		{
			mlx_pixel_put(game->mlx, game->win, x + w, y + h, color);
			w++;
		}
		h++;
	}
}

void	mini_map(void)
{
	t_game	*game;
	int		h;
	int		w;

	h = 0;
	game = get_game();
	while (h < game->map->height)
	{
		w = 0;
		while (w < game->map->width)
		{
			if (game->map->map[h][w] == WALL)
				render_tile(w * SIZE, h * SIZE, H_W);
			else
				render_tile(w * SIZE, h * SIZE, H_B);
			w++;
		}
		h++;
	}
}

void	mini_map_loop(void)
{
	t_game	*game;

	game = get_game();
	if (game->count.map_hl == FALSE)
	{
		mlx_clear_window(game->mlx, game->win);
		return ;
	}
	render_tile(game->player.x * SIZE, game->player.y * SIZE, H_R);
}

int	loop_handler(t_game *game)
{
	(void)game;
	mini_map_loop();
	if (game->move[0] == FALSE)
	{
		update_position(&game->player.y, &game->player.vertical, -1);
	}
	if (game->move[1] == FALSE)
	{
		update_position(&game->player.x, &game->player.horizontal, 1);
	}
	usleep(25000);
	return (0);
}

static void	init_img(void)
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

void	init_game(void)
{
	t_game	*game;

	game = get_game();
	game->mlx = mlx_init();
	if (!game->mlx)
		error_controller("Mlx is not initialized.", NULL);
	game->win = mlx_new_window(game->mlx, 1280, 720, NAME);
	if (!game->win)
		error_controller("Window is not created.", NULL);
	init_img();
	mlx_hook(game->win, 2, 1L << 0, key_press_handler, game);
	mlx_hook(game->win, 3, 1L << 1, key_release_handler, game);
	mlx_hook(game->win, 17, 1L << 17, exit_game, game);
	mlx_loop_hook(game->mlx, loop_handler, game);
	mlx_loop(game->mlx);
}
