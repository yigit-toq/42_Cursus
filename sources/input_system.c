/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_system.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 23:31:53 by ytop              #+#    #+#             */
/*   Updated: 2024/10/26 23:31:53 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	input_system(char direction, double acceleration, double new_pos)
{
	t_game	*game;
	double	*axis;

	game = get_game();
	(void)new_pos;
	if (direction == 'N' || direction == 'S')
	{
		game->move[0] = TRUE;
		axis = &game->player.vertical;
		game->player.y -= SPEED * *axis;
	}
	if (direction == 'W' || direction == 'E')
	{
		game->move[1] = TRUE;
		axis = &game->player.horizontal;
		game->player.x += SPEED * *axis;
	}
	if (fabs(*axis) < MAX_SPEED)
		*axis += acceleration;
	return (0);
}

int	exit_game(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	exit(EXIT_SUCCESS);
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
		game->move[0] = FALSE;
	}
	if (key == A || key == D)
	{
		game->move[1] = FALSE;
	}
	if (key == M)
	{
		game->count.map_hl = !game->count.map_hl;
		mini_map();
	}
	if (key == ESC)
	{
		mlx_destroy_window(game->mlx, game->win);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

void	update_position(double *position, double *axis, int sign)
{
	if (*axis != 0)
	{
		if (*axis > 0)
			*axis -= SPEED / 10;
		else
			*axis += SPEED / 10;
	}
	if (fabs(*axis) <= 0.01)
	{
		*axis = 0;
	}
	if (*axis)
	{
		*position += (*axis) * sign * SPEED;
	}
}
