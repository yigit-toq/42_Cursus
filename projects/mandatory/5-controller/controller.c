/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 23:31:53 by ytop              #+#    #+#             */
/*   Updated: 2025/03/14 17:03:37 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_mandatory.h"

#include <math.h>

static int	update_axis(double *position, double *axis, int sign);

static int	input_systm(double h_move, double v_move);

int	update_position(void)
{
	t_game	*game;
	int		dr[2];

	game = get_game();
	if (game->player.rota[0])
		game->player.theta += ROTATE;
	if (game->player.rota[1])
		game->player.theta -= ROTATE;
	if (game->player.theta < 0)
		game->player.theta += 2 * PI;
	else
	{
		if (game->player.theta >= 2 * PI)
			game->player.theta -= 2 * PI;
	}
	if (game->player.move[0] == FALSE)
		update_axis(&game->player.pos.y, &game->player.axis.y, -1);
	if (game->player.move[1] == FALSE)
		update_axis(&game->player.pos.x, &game->player.axis.x, +1);
	dr[0] = game->player.move[0];
	dr[1] = game->player.move[1];
	if (dr[0] || dr[1])
		input_systm(dr[0], dr[1]);
	return (SUCCESS);
}

static int	update_axis(double *position, double *axis, int sign)
{
	t_game	*game;

	game = get_game();
	if (*axis != 0)
	{
		if (*axis > 0)
			*axis -= game->player.speed / 10;
		else
			*axis += game->player.speed / 10;
	}
	if (fabs(*axis) <= 0.01)
	{
		*axis = 0;
	}
	*position += (*axis) * sign * game->player.speed;
	return (SUCCESS);
}

static int	input_systm(double h_move, double v_move)
{
	t_player	*player;
	t_vect		forw;
	t_vect		side;
	t_vect		pos;
	double		avg;

	player = &get_game()->player;
	side.x = -sin(player->theta);
	side.y = +cos(player->theta);
	forw.x = +cos(player->theta);
	forw.y = +sin(player->theta);
	pos = player->pos;
	avg = sqrt(h_move * h_move + v_move * v_move);
	if (avg > 1)
	{
		h_move /= avg;
		v_move /= avg;
	}
	pos.x += v_move * player->speed * side.x + h_move * player->speed * forw.x;
	pos.y += v_move * player->speed * side.y + h_move * player->speed * forw.y;
	return (wall_check(pos));
}

int	key_press_handler(int key, t_game *game)
{
	if (key == R_ARR_KEY)
		game->player.rota[0] = TRUE;
	if (key == L_ARR_KEY)
		game->player.rota[1] = TRUE;
	if (key == W_KEY)
		game->player.move[0] = +1;
	if (key == S_KEY)
		game->player.move[0] = -1;
	if (key == D_KEY)
		game->player.move[1] = +1;
	if (key == A_KEY)
		game->player.move[1] = -1;
	return (SUCCESS);
}

int	key_relse_handler(int key, t_game *game)
{
	if (key == W_KEY || key == S_KEY)
	{
		game->player.move[0] = FALSE;
	}
	if (key == A_KEY || key == D_KEY)
	{
		game->player.move[1] = FALSE;
	}
	if (key == R_ARR_KEY)
	{
		game->player.rota[0] = FALSE;
	}
	if (key == L_ARR_KEY)
	{
		game->player.rota[1] = FALSE;
	}
	if (key == ESC_KEY)
	{
		exit_game(game, EXIT_SUCCESS);
	}
	return (SUCCESS);
}
