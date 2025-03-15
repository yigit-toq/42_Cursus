/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 17:31:07 by ytop              #+#    #+#             */
/*   Updated: 2025/03/14 17:06:01 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

#include <math.h>

static int	update_axis(double *position, double *axis, int sign);

static int	input_systm(double h_move, double v_move);

void	mouse_control(void)
{
	t_game	*game;
	double	damping;
	double	m_speed;

	game = get_game();
	damping = 0.800;
	m_speed = 0.005;
	if (game->player.mctrl == FALSE)
		return ;
	game->player.theta += game->player.velocity;
	if (!mouse_inside_window())
	{
		if (fabs(game->player.velocity) < m_speed)
		{
			if (game->player.velocity < 0)
				game->player.velocity = -m_speed;
			else
				game->player.velocity = +m_speed;
		}
	}
	else
		game->player.velocity = game->player.velocity * damping;
	if (fabs(game->player.velocity) < 0.01)
		game->player.velocity = 0.0;
}

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
	mouse_control();
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

static int	wall_check(t_vect pos)
{
	t_game	*game;
	int		cell;

	game = get_game();
	cell = game->map->map[(int)grid_to_ct(pos.y, 1)][(int)grid_to_ct(pos.x, 1)];
	if (cell == WALL || (cell == DOOR && !game->grp->curr->state))
	{
		return (FAILURE);
	}
	else
	{
		game->player.pos = pos;
		return (SUCCESS);
	}
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
	return (wall_check(pos));
}
