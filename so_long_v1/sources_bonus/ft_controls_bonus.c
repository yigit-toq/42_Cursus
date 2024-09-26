/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_controls_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 13:39:58 by ytop              #+#    #+#             */
/*   Updated: 2024/07/01 17:52:39 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"
#include "../includes/libft.h"

static void	player_controller(t_game *game, int x, int y, char direction);
static int	player_direction(t_game *game, int x, int y, char direction);
static int	move_bool(int i, int j, char d_i, char d_o);

int	close_controller(t_game *game)
{
	t_player	*p;

	p = game->player;
	error_controller(game, 'F', 0, 0);
	if (p->x == game->count->e_dir[0] && p->y == game->count->e_dir[1])
		ft_printf("%sThanks for playing.\n%s", GREEN, END);
	else if (!game->player->death)
		ft_printf("%sGame is closed.\n%s", RED, END);
	exit(EXIT_SUCCESS);
}

int	key_controller(int keycode, t_game *game)
{
	if (game->player->death)
		return (0);
	if (keycode == KEY_W)
	{
		if (player_back_animation(game, game->player->x, game->player->y - 1))
			player_controller(game, game->player->x, game->player->y - 1, 'B');
	}
	else if (keycode == KEY_A)
	{
		if (player_left_animation(game, game->player->x - 1, game->player->y))
			player_controller(game, game->player->x - 1, game->player->y, 'L');
	}
	else if (keycode == KEY_S)
	{
		if (player_front_animation(game, game->player->x, game->player->y + 1))
			player_controller(game, game->player->x, game->player->y + 1, 'F');
	}
	else if (keycode == KEY_D)
	{
		if (player_right_animation(game, game->player->x + 1, game->player->y))
			player_controller(game, game->player->x + 1, game->player->y, 'R');
	}
	else if (keycode == KEY_ESC)
		close_controller(game);
	return (0);
}

static void	player_controller(t_game *game, int x, int y, char direction)
{
	char		**map;

	map = game->map->map;
	game->player->direction = direction;
	if (map[y][x] != WALL)
	{
		if (player_direction(game, x, y, direction))
		{
			if (map[y][x] == COLLECT)
			{
				game->count->collect--;
				game->count->score++;
				if (!game->count->collect)
					game->door->unlock = 1;
			}
			map[game->player->y][game->player->x] = FLOOR;
			map[y][x] = PLAYER;
			game->player->x = x;
			game->player->y = y;
			if (x == game->count->e_dir[0] && y == game->count->e_dir[1])
				if (!game->count->collect)
					close_controller(game);
		}
	}
	return ;
}

static int	player_direction(t_game *game, int x, int y, char direction)
{
	int	move[4];

	move[0] = move_bool(y * CONST, game->player->t_y, direction, 'F');
	move[1] = move_bool(y * CONST, game->player->t_y, direction, 'B');
	move[2] = move_bool(x * CONST, game->player->t_x, direction, 'L');
	move[3] = move_bool(x * CONST, game->player->t_x, direction, 'R');
	return (move[0] || move[1] || move[2] || move[3]);
}

static int	move_bool(int input, int output, char d_input, char d_output)
{
	int	result;

	result = (!(input % output) && d_input == d_output);
	return (result);
}
