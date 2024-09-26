/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations_player_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 19:20:58 by ytop              #+#    #+#             */
/*   Updated: 2024/08/16 17:12:01 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

#include <stdio.h>

static int	player_movement(t_game *game);
static int	set_values(t_player *player, char direction, int **transform);

void	player_animation(t_game *game)
{
	static unsigned int	multiplier;
	static unsigned int	progress;
	int					sign;
	int					*transform;

	if (!game->player->move)
		return ;
	if (game->player->frame == 3)
		game->player->frame = 0;
	sign = set_values(game->player, game->player->direction, &transform);
	*transform += PLAYER_SPEED * sign;
	multiplier++;
	progress++;
	if (!(multiplier % F_SPEED))
		game->player->frame++;
	if (progress == (CONST / PLAYER_SPEED))
	{
		progress = 0;
		game->player->move = 0;
		game->player->frame = 0;
		set_values(game->player, game->player->direction, &transform);
		player_movement(game);
	}
}

static int	player_movement(t_game *game)
{
	t_player	*player;
	t_count		*count;

	player = game->player;
	count = game->count;
	if (game->map->map[player->n_t[1]][player->n_t[0]] == COLLECT)
	{
		count->collect--;
		count->score++;
		if (!count->collect)
			game->door->unlock = 1;
	}
	game->map->map[player->y][player->x] = FLOOR;
	game->map->map[player->n_t[1]][player->n_t[0]] = PLAYER;
	player->x = player->n_t[0];
	player->y = player->n_t[1];
	game->count->step++;
	if (player->n_t[0] == count->e_dir[0] && player->n_t[1] == count->e_dir[1])
	{
		if (!count->collect)
			close_controller(game);
	}
	return (SUCCESS);
}

static int	set_values(t_player *player, char direction, int **transform)
{
	if (direction == 'F' || direction == 'B')
	{
		*transform = &player->w_t[1];
		if (direction == 'F')
			player->img = player->img_f[player->frame];
		else
		{
			player->img = player->img_b[player->frame];
			return (-1);
		}
	}
	else
	{
		*transform = &player->w_t[0];
		if (direction == 'R')
			player->img = player->img_r[player->frame];
		else
		{
			player->img = player->img_l[player->frame];
			return (-1);
		}
	}
	return (1);
}
