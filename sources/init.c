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

void	render_tile(int x, int y, int size, int color)
{
	t_game	*game;
	int		h;
	int		w;

	game = get_game();
	h = 0;
	w = 0;
	while (h < size)
	{
		w = 0;
		while (w < size)
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
	int		size;
	int		x;
	int		y;

	x = 0;
	y = 0;
	game = get_game();
	size = (WIDTH / 4) / game->map->width;
	while (y < game->map->height)
	{
		x = 0;
		while (x < game->map->width)
		{
			if (game->map->map[y][x] == WALL)
				render_tile(x * size, y * size, size, H_W);
			else
				render_tile(x * size, y * size, size, H_B);
			x++;
		}
		y++;
	}
	game->map->size = size;
}

void	mini_map_loop(void)
{
	t_game	*game;
	double	size;
	double	p[2];

	game = get_game();
	if (game->map->map_hl == FALSE)
	{
		mlx_clear_window(game->mlx, game->win);
		return ;
	}
	size = game->map->size;
	p[0] = game->player.position.x;
	p[1] = game->player.position.y;
	render_tile(p[0] * size, p[1] * size, size, H_R);
}

int	loop_handler(void)
{
	t_game	*game;

	mini_map_loop();
	game = get_game();
	if (game->player.move[0] == FALSE)
	{
		update_position(&game->player.position.y, &game->player.axis.y, -1);
	}
	if (game->player.move[1] == FALSE)
	{
		update_position(&game->player.position.x, &game->player.axis.x, +1);
	}
	return (usleep(25000), SUCCESS);
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
		game->img->direction[i] = open_xpm(game->img->direction[i]);
		i++;
	}
}

void	init_game(void)
{
	t_game	*game;

	game = get_game();
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, NAME);
	init_img();
	mlx_hook(game->win, KEY_RELEASE, 1L << 1, key_release_handler, NULL);
	mlx_hook(game->win, KEY_PRESS, 1L << 0, key_press_handler, NULL);
	mlx_hook(game->win, DESTROY, 1L << DESTROY, exit_game, NULL);
	mlx_loop_hook(game->mlx, loop_handler, game);
	mlx_loop(game->mlx);
}
