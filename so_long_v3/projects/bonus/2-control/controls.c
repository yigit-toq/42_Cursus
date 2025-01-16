/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 13:39:58 by ytop              #+#    #+#             */
/*   Updated: 2025/01/16 18:45:36 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"
#include "libft.h"

static int	player_controller(t_game *game, int x, int y, char direction);

int	close_controller(t_game *game)
{
	t_player	*p;

	p = game->player;
	error_controller(game, 'F', 0, 0);
	if (p->x == game->count->e_dir[0] && p->y == game->count->e_dir[1])
		ft_printf("%sThanks for playing.\n%s", C_G, END);
	else if (!game->player->death)
		ft_printf("%sGame is closed.\n%s", C_R, END);
	exit(EXIT_SUCCESS);
}

int	key_controller(int keycode, t_game *game)
{
	t_player	*player;

	player = game->player;
	if (player->death || (player->move && keycode != ESC_KEY))
		return (1);
	if (keycode == W_KEY)
	{
		player_controller(game, player->x, player->y - 1, 'B');
	}
	else if (keycode == S_KEY)
	{
		player_controller(game, player->x, player->y + 1, 'F');
	}
	else if (keycode == A_KEY)
	{
		player_controller(game, player->x - 1, player->y, 'L');
	}
	else if (keycode == D_KEY)
	{
		player_controller(game, player->x + 1, player->y, 'R');
	}
	else if (keycode == ESC_KEY)
		close_controller(game);
	return (0);
}

int	key_up_control(int keycode, t_game *game)
{
	if (game->player->death)
		return (1);
	if (!game->dynamite->available && keycode == SPACE_KEY)
		dynamite_drop(game);
	game->player->frame = 0;
	return (0);
}

static int	player_controller(t_game *game, int x, int y, char direction)
{
	game->player->direction = direction;
	if (game->map->map[y][x] != WALL)
	{
		game->player->move = 1;
		game->player->n_t[0] = x;
		game->player->n_t[1] = y;
		return (SUCCESS);
	}
	return (FAILURE);
}
