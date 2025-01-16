/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 13:39:58 by ytop              #+#    #+#             */
/*   Updated: 2025/01/16 18:45:55 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft.h"

static void	player_controller(t_game *game, int x, int y);

int	close_controller(t_game *game)
{
	t_player	*p;

	p = game->player;
	error_controller(game, 'F', 0, 0);
	if (p->x == game->count->e_dir[0] && p->y == game->count->e_dir[1])
		ft_printf("%sThanks for playing.\n%s", C_G, END);
	else
		ft_printf("%sGame is closed.\n%s", C_R, END);
	exit(EXIT_SUCCESS);
}

int	key_controller(int keycode, t_game *game)
{
	int	x;
	int	y;

	x = game->player->x;
	y = game->player->y;
	if (keycode == W_KEY)
		player_controller(game, x, y - 1);
	else if (keycode == S_KEY)
		player_controller(game, x, y + 1);
	else if (keycode == A_KEY)
		player_controller(game, x - 1, y);
	else if (keycode == D_KEY)
		player_controller(game, x + 1, y);
	else if (keycode == ESC_KEY)
		close_controller(game);
	return (0);
}

static void	player_controller(t_game *game, int x, int y)
{
	char		**map;

	map = game->map->map;
	if (map[y][x] != WALL)
	{
		if (map[y][x] == COLL)
			game->count->coll--;
		map[game->player->y][game->player->x] = FLOOR;
		map[y][x] = PLAYER;
		game->player->x = x;
		game->player->y = y;
		game->count->step++;
		ft_printf("%sMovement: %d\n%s", C_Y, game->count->step, END);
		if (x == game->count->e_dir[0] && y == game->count->e_dir[1])
			if (!game->count->coll)
				close_controller(game);
	}
	return ;
}
