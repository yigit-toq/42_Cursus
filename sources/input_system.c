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

int	exit_game(void)
{
	t_game	*game;
	int		i;

	i = 0;
	game = get_game();
	mlx_destroy_window(game->mlx, game->win);
	while (i < 4)
	{
		mlx_destroy_image(game->mlx, game->img->direction[i]);
		i++;
	}
	save_scene();
	exit(EXIT_SUCCESS);
}

int	input_system(char direction, double acceleration)
{
	t_game	*game;
	double	*axis;

	game = get_game();
	if (direction == 'N' || direction == 'S')
	{
		game->player.move[0] = TRUE;
		axis = &game->player.axis.y;
		game->player.position.y -= SPEED * (*axis);
	}
	if (direction == 'W' || direction == 'E')
	{
		game->player.move[1] = TRUE;
		axis = &game->player.axis.x;
		game->player.position.x += SPEED * (*axis);
	}
	if (fabs(*axis) < MAX_SPEED)
	{
		*axis += acceleration;
	}
	return (SUCCESS);
}

int	update_position(double *position, double *axis, int sign)
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
	return (SUCCESS);
}

int	key_press_handler(int key)
{
	if (key == W)
	{
		input_system('N', +SPEED / 10);
	}
	if (key == S)
	{
		input_system('S', -SPEED / 10);
	}
	if (key == A)
	{
		input_system('W', -SPEED / 10);
	}
	if (key == D)
	{
		input_system('E', +SPEED / 10);
	}
	return (SUCCESS);
}

int	key_release_handler(int key)
{
	t_game	*game;

	game = get_game();
	if (key == W || key == S)
	{
		game->player.move[0] = FALSE;
	}
	if (key == A || key == D)
	{
		game->player.move[1] = FALSE;
	}
	if (key == ESC)
	{
		exit_game();
	}
	if (key == M)
	{
		game->map->map_hl = !game->map->map_hl;
		minimap();
	}
	return (SUCCESS);
}
