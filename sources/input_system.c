/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_system.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 23:31:53 by ytop              #+#    #+#             */
/*   Updated: 2024/11/18 18:15:42 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int	input_system(int f, int s, double acceleration)
// {
// 	t_game	*game;
// 	t_coord	*axis;
// 	t_coord	forw;
// 	t_coord	side;
// 	t_coord line;
// 	int		dir;

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

static int	input_systm(double forward, double strafe);

int	update_position(void)
{
	t_game	*game;
	int		dr[2];

	game = get_game();
	if (game->player.move[0] == FALSE)
	{
		update_axis(&game->player.position.y, &game->player.axis.y, -1);
	}
	if (game->player.move[1] == FALSE)
	{
		update_axis(&game->player.position.x, &game->player.axis.x, +1);
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
	*position += (*axis) * sign * SPEED;
	return (SUCCESS);
}

static int	input_systm(double forward, double strafe)
{
	t_game	*game;
	t_coord	forw;
	t_coord	side;

	game = get_game();
	side.x = -sin(game->player.theta);
	side.y = +cos(game->player.theta);
	forw.x = +cos(game->player.theta);
	forw.y = +sin(game->player.theta);
	game->player.position.x += +strafe * SPEED * side.x;
	game->player.position.y += +strafe * SPEED * side.y;
	game->player.position.x += forward * SPEED * forw.x;
	game->player.position.y += forward * SPEED * forw.y;
	return (SUCCESS);
}

int	key_press_handler(int key, t_game *game)
{
	if (key == RIGHT)
		game->player.theta += ROTATE;
	if (key == LEFT)
		game->player.theta -= ROTATE;
	if (key == W)
		game->player.move[0] = +1;
	if (key == S)
		game->player.move[0] = -1;
	if (key == D)
		game->player.move[1] = +1;
	if (key == A)
		game->player.move[1] = -1;
	if (game->player.theta < 0)
	{
		game->player.theta += 2 * PI;
	}
	else
	{
		if (game->player.theta >= 2 * PI)
			game->player.theta -= 2 * PI;
	}
	return (SUCCESS);
}

int	key_release_handler(int key, t_game *game)
{
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
		exit_game(game);
	}
	if (key == M)
	{
		game->map->is_map = !game->map->is_map;
	}
	return (SUCCESS);
}

int	exit_game(t_game *game)
{
	int		i;

	i = 0;
	mlx_destroy_window(game->mlx, game->win);
	while (i < MAX_PATH)
	{
		mlx_destroy_image(game->mlx, game->img->dir_syml[i]);
		i++;
	}
	exit(EXIT_SUCCESS);
}

// save_scene();
