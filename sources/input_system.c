/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_system.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 23:31:53 by ytop              #+#    #+#             */
/*   Updated: 2024/11/15 14:23:22 by ytop             ###   ########.fr       */
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

int	input_system(int f, int s, double acceleration)
{
	t_game	*game;
	t_coord	*axis;
	t_coord	forw;
	t_coord	side;

	game = get_game();
	side.x = -sin(game->player.theta);
    side.y = +cos(game->player.theta);
	forw.x = +cos(game->player.theta);
    forw.y = +sin(game->player.theta);
	axis = &game->player.axis;
    if (f)
    {
        game->player.move[0] = TRUE;
        axis->x += f * acceleration * forw.x;
        axis->y += f * acceleration * forw.y;
    }
    if (s)
    {
        game->player.move[1] = TRUE;
        axis->x += s * acceleration * side.x;
        axis->y += s * acceleration * side.y;
    }
    if (fabs(axis->x) > MAX_SPEED)
	{
		if (axis->x > 0)
			axis->x = +MAX_SPEED;
		else
			axis->x = -MAX_SPEED;
	}
    if (fabs(axis->y) > MAX_SPEED)
	{
		if (axis->y > 0)
			axis->y = +MAX_SPEED;
		else
			axis->y = -MAX_SPEED;
	}
    game->player.position.x += axis->x * SPEED * 20;
    game->player.position.y += axis->y * SPEED * 20;
	// if (direction == 'N' || direction == 'S')
	// {
	// 	game->player.move[0] = TRUE;
	// 	axis = &game->player.axis.y;
	// 	game->player.position.y -= SPEED * (*axis);
	// }
	// if (direction == 'W' || direction == 'E')
	// {
	// 	game->player.move[1] = TRUE;
	// 	axis = &game->player.axis.x;
	// 	game->player.position.x += SPEED * (*axis);
	// }
	// if (fabs(*axis) < MAX_SPEED)
	// {
	// 	*axis += acceleration;
	// }
	return (SUCCESS);
}

// int input_system(double forward, double strafe, double acceleration)
// {
//     t_game *game;
// 	double strafe_x, strafe_y;
//     double forward_x, forward_y;

//     game = get_game();
// 	(void)acceleration;
    
//     // Theta'ya göre hareket yönü bileşenleri
//     forward_x = cos(game->player.theta);
//     forward_y = sin(game->player.theta);

//     strafe_x = -sin(game->player.theta);
//     strafe_y = +cos(game->player.theta);

//     // İleri/geri hareket
//     game->player.position.x += forward * SPEED * forward_x;
//     game->player.position.y += forward * SPEED * forward_y;

//     // Strafe hareket
//     game->player.position.x += strafe * SPEED * strafe_x;
//     game->player.position.y += strafe * SPEED * strafe_y;

//     return SUCCESS;
// }

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
	*position += (*axis) * sign * SPEED;
	return (SUCCESS);
}

int	key_press_handler(int key, t_game *game)
{
	if (key == RIGHT)
		game->player.theta += ROTATE;
	if (key == LEFT)
		game->player.theta -= ROTATE;
	if (key == W)
		input_system(+1, 0, +SPEED / 10);
	if (key == S)
		input_system(-1, 0, -SPEED / 10);
	if (key == A)
		input_system(0, -1, -SPEED / 10);
	if (key == D)
		input_system(0, +1, +SPEED / 10);
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
		exit_game();
	}
	if (key == M)
	{
		game->map->map_hl = !game->map->map_hl;
		minimap();
	}
	return (SUCCESS);
}
