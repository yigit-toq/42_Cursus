/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_animations_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 19:20:58 by ytop              #+#    #+#             */
/*   Updated: 2024/06/11 16:15:49 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long_bonus.h"

static int	coord_bool(t_player *player, char direction);

int	player_front_animation(t_game *game, int x, int y)
{
	static unsigned int	speed;
	char				**map;
	int					coord_wall;

	map = game->map->map;
	coord_wall = ((!coord_bool(game->player, 'V') && map[y][x - 1] == WALL)
			|| (coord_bool(game->player, 'V') && map[y][x + 1] == WALL));
	if (!(game->player->t_x % CONST))
		coord_wall = 0;
	if ((map[y][x] == WALL && !(game->player->t_y % CONST))
			|| (coord_wall && map[y][x] != WALL))
		return (0);
	game->player->img = game->player->img_f[game->player->frame + 1];
	game->player->t_y += PLAYER_SPEED;
	if (game->player->frame)
		game->player->frame = 0;
	if (speed % F_SPEED)
		game->player->frame++;
	game->count->step++;
	speed++;
	return (1);
}

int	player_back_animation(t_game *game, int x, int y)
{
	static unsigned int	speed;
	char				**map;
	int					coord_wall;

	map = game->map->map;
	coord_wall = ((!coord_bool(game->player, 'V') && map[y][x - 1] == WALL)
			|| (coord_bool(game->player, 'V') && map[y][x + 1] == WALL));
	if (!(game->player->t_x % CONST))
		coord_wall = 0;
	if ((map[y][x] == WALL && !(game->player->t_y % CONST))
			|| (coord_wall && map[y][x] != WALL))
		return (0);
	game->player->img = game->player->img_b[game->player->frame + 1];
	game->player->t_y -= PLAYER_SPEED;
	if (game->player->frame)
		game->player->frame = 0;
	if (speed % F_SPEED)
		game->player->frame++;
	game->count->step++;
	speed++;
	return (1);
}

int	player_left_animation(t_game *game, int x, int y)
{
	static unsigned int	speed;
	char				**map;
	int					coord_wall;

	map = game->map->map;
	coord_wall = ((!coord_bool(game->player, 'H') && map[y - 1][x] == WALL)
			|| (coord_bool(game->player, 'H') && map[y + 1][x] == WALL));
	if (!(game->player->t_y % CONST))
		coord_wall = 0;
	if ((map[y][x] == WALL && !(game->player->t_x % CONST))
			|| (coord_wall && map[y][x] != WALL))
		return (0);
	game->player->img = game->player->img_l[game->player->frame + 1];
	game->player->t_x -= PLAYER_SPEED;
	if (game->player->frame)
		game->player->frame = 0;
	if (speed % F_SPEED)
		game->player->frame++;
	game->count->step++;
	speed++;
	return (1);
}

int	player_right_animation(t_game *game, int x, int y)
{
	static unsigned int	speed;
	char				**map;
	int					coord_wall;

	map = game->map->map;
	coord_wall = ((!coord_bool(game->player, 'H') && map[y - 1][x] == WALL)
			|| (coord_bool(game->player, 'H') && map[y + 1][x] == WALL));
	if (!(game->player->t_y % CONST))
		coord_wall = 0;
	if ((map[y][x] == WALL && !(game->player->t_x % CONST))
			|| (coord_wall && map[y][x] != WALL))
		return (0);
	game->player->img = game->player->img_r[game->player->frame + 1];
	game->player->t_x += PLAYER_SPEED;
	if (game->player->frame)
		game->player->frame = 0;
	if (speed % F_SPEED)
		game->player->frame++;
	game->count->step++;
	speed++;
	return (1);
}

static int	coord_bool(t_player *player, char direction)
{
	int	result;

	result = 0;
	if (direction == 'H')
	{
		if ((player->t_y - (player->y * CONST)) < 0)
			result = 0;
		else
			result = 1;
	}
	else if (direction == 'V')
	{
		if ((player->t_x - (player->x * CONST)) < 0)
			result = 0;
		else
			result = 1;
	}
	return (result);
}
