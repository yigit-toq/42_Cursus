/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 23:31:53 by ytop              #+#    #+#             */
/*   Updated: 2024/12/30 13:40:58 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#include <math.h>

// int	input_systm(int f, int s, double acceleration)
// {
// 	t_game	*game;
// 	t_coord	*axis;
// 	t_coord	forw;
// 	t_coord	side;
// 	t_coord line;
// 	int		dir;
//
// 	game = get_game();
// 	side.x = -sin(game->player.theta);
//     side.y = +cos(game->player.theta);
// 	forw.x = +cos(game->player.theta);
//     forw.y = +sin(game->player.theta);
// 	axis = &game->player.axis;
//     if (f)
//     {
//         game->player.move[0] = TRUE;
// 		line = forw;
// 		dir = f;
//     }
//     if (s)
//     {
//         game->player.move[1] = TRUE;
// 		line = side;
// 		dir = s;
//     }
// 	if (fabs(axis->x) < MAX_SPEED)
// 	{
// 		axis->x += acceleration * line.x * dir;
// 	}
// 	if (fabs(axis->y) < MAX_SPEED)
// 	{
// 		axis->y += acceleration * line.y * dir;
// 	}
// 	game->player.position.x += axis->x * SPEED * (f * forw.x + s * side.x);
// 	game->player.position.y += axis->y * SPEED * (f * forw.y + s * side.y);
// 	// if (direction == 'N' || direction == 'S')
// 	// {
// 	// 	game->player.move[0] = TRUE;
// 	// 	axis = &game->player.axis.y;
// 	// 	game->player.position.y -= SPEED * (*axis);
// 	// }
// 	// if (direction == 'W' || direction == 'E')
// 	// {
// 	// 	game->player.move[1] = TRUE;
// 	// 	axis = &game->player.axis.x;
// 	// 	game->player.position.x += SPEED * (*axis);
// 	// }
// 	// if (fabs(*axis) < MAX_SPEED)
// 	// {
// 	// 	*axis += acceleration;
// 	// }
// 	return (SUCCESS);
// }

static int	update_axis(double *position, double *axis, int sign);

static int	input_systm(double h_move, double v_move);

int	update_position(void)
{
	t_game	*game;
	int		dr[2];

	game = get_game();
	if (game->player.rotate[0])
	{
		game->player.theta += ROTATE;
	}
	if (game->player.rotate[1])
	{
		game->player.theta -= ROTATE;
	}
	if (game->player.theta < 0)
	{
		game->player.theta += 2 * PI;
	}
	else
	{
		if (game->player.theta >= 2 * PI)
			game->player.theta -= 2 * PI;
	}
	if (game->player.move[0] == FALSE)
	{
		update_axis(&game->player.pos.y, &game->player.axis.y, -1);
	}
	if (game->player.move[1] == FALSE)
	{
		update_axis(&game->player.pos.x, &game->player.axis.x, +1);
	}
	dr[0] = game->player.move[0];
	dr[1] = game->player.move[1];
	if (dr[0] || dr[1])
	{
		input_systm(dr[0], dr[1]);
	}
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
	t_game	*game;
	t_vect	forw;
	t_vect	side;
	t_vect	pos;
	double	avg;

	game = get_game();
	pos = game->player.pos;
	side.x = -sin(game->player.theta);
	side.y = +cos(game->player.theta);
	forw.x = +cos(game->player.theta);
	forw.y = +sin(game->player.theta);
	avg = sqrt(h_move * h_move + v_move * v_move);
	if (avg > 1)
	{
		h_move /= avg;
		v_move /= avg;
	}
	pos.x += v_move * game->player.speed * side.x;
	pos.y += v_move * game->player.speed * side.y;
	pos.x += h_move * game->player.speed * forw.x;
	pos.y += h_move * game->player.speed * forw.y;
	if (game->map->map[(int)grid_to_ct(pos.y, 1)][(int)grid_to_ct(pos.x, 1)] == WALL)
		return (FAILURE);
	return (game->player.pos = pos, SUCCESS);
}

int	key_press_handler(int key, t_game *game)
{
	if (key == RIGHT_KEY)
		game->player.rotate[0] = TRUE;
	if (key == LEFT_KEY)
		game->player.rotate[1] = TRUE;
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

int	key_release_handler(int key, t_game *game)
{
	if (key == W_KEY || key == S_KEY)
	{
		game->player.move[0] = FALSE;
	}
	if (key == A_KEY || key == D_KEY)
	{
		game->player.move[1] = FALSE;
	}
	if (key == RIGHT_KEY)
	{
		game->player.rotate[0] = FALSE;
	}
	if (key == LEFT_KEY)
	{
		game->player.rotate[1] = FALSE;
	}
	if (key == ESC_KEY)
	{
		exit_game(game);
	}
	return (SUCCESS);
}
