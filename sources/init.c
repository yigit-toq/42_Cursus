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

void	mini_map_loop(void)
{
	t_game	*game;

	game = get_game();
	if (game->count.map_hl == FALSE)
	{
		mlx_clear_window(game->mlx, game->win);
		return ;
	}
	for (int y = 0; y < SIZE; y++)
	{
		for (int x = 0; x < SIZE; x++)
		{
			mlx_pixel_put(game->mlx, game->win, x + (game->player.x * SIZE), y + (game->player.y * SIZE), H_R);
		}
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
			for (int y = 0; y < SIZE; y++)
			{
				for (int x = 0; x < SIZE; x++)
				{
					if (game->map->map[h][w] == WALL)
						mlx_pixel_put(game->mlx, game->win, x + (w * SIZE), y + (h * SIZE), H_W);
					if (game->map->map[h][w] == FLOOR)
						mlx_pixel_put(game->mlx, game->win, x + (w * SIZE), y + (h * SIZE), H_B);
				}
			}
			w++;
		}
		h++;
	}
}

int	loop_handler(t_game *game)
{
	(void)game;
	mini_map_loop();
	if (game->move[1] == FALSE)
	{
		if (game->player.vertical > 0)
			game->player.vertical -= SPEED / 10;
		if (game->player.vertical < 0)
			game->player.vertical += SPEED / 10;
		if (fabs(game->player.vertical) <= 0.01)
			game->player.vertical = 0;
		if (game->player.vertical != 0)
		{
			game->player.y -= SPEED * game->player.vertical;
		}
	}
	if (game->move[0] == FALSE)
	{
		if (game->player.horizontal > 0)
			game->player.horizontal -= SPEED / 10;
		if (game->player.horizontal < 0)
			game->player.horizontal += SPEED / 10;
		if (fabs(game->player.horizontal) <= 0.01)
			game->player.horizontal = 0;
		if (game->player.horizontal != 0)
		{
			game->player.x += SPEED * game->player.horizontal;
		}
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

int	input_system(char direction, double acceleration, double new_pos)
{
	t_game	*game;
	double	*axis;

	game = get_game();
	(void)new_pos;
	if (direction == 'N' || direction == 'S')
	{
		game->move[1] = TRUE;
		axis = &game->player.vertical;
		game->player.y -= SPEED * *axis;
	}
	if (direction == 'W' || direction == 'E')
	{
		game->move[0] = TRUE;
		axis = &game->player.horizontal;
		game->player.x += SPEED * *axis;
	}
	if (fabs(*axis) < MAX_SPEED)
		*axis += acceleration;
	return (0);
}

int	key_press_handler(int key, t_game *game)
{
	(void)game;
	if (key == W)
	{
		input_system('N', +SPEED / 10, game->player.y - SPEED);
	}
	if (key == S)
	{
		input_system('S', -SPEED / 10, game->player.y + SPEED);
	}
	if (key == A)
	{
		input_system('W', -SPEED / 10, game->player.x - SPEED);
	}
	if (key == D)
	{
		input_system('E', +SPEED / 10, game->player.x + SPEED);
	}
	return (0);
}

int	key_release_handler(int key, t_game *game)
{
	if (key == W || key == S)
	{
		game->move[1] = FALSE;
	}
	if (key == A || key == D)
	{
		game->move[0] = FALSE;
	}
	if (key == M)
	{
		mini_map();
		game->count.map_hl = !game->count.map_hl;
	}
	if (key == ESC)
	{
		mlx_destroy_window(game->mlx, game->win);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int	exit_game(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	exit(EXIT_SUCCESS);
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
