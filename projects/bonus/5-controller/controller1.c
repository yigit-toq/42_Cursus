/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 23:31:53 by ytop              #+#    #+#             */
/*   Updated: 2025/03/07 17:47:24 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

#include <mlx.h>

int	key_press_handler(int key, t_game *game)
{
	if (game->player.mctrl == FALSE)
	{
		if (key == R_ARR_KEY)
			game->player.rota[0] = TRUE;
		if (key == L_ARR_KEY)
			game->player.rota[1] = TRUE;
	}
	if (key == W_KEY)
		game->player.move[0] = +1;
	if (key == S_KEY)
		game->player.move[0] = -1;
	if (key == D_KEY)
		game->player.move[1] = +1;
	if (key == A_KEY)
		game->player.move[1] = -1;
	if (key == SHIFT_KEY)
	{
		game->player.speed = SPEED * 4;
	}
	return (SUCCESS);
}

int	key_relse_handler(int key, t_game *game)
{
	if (key == W_KEY || key == S_KEY)
		game->player.move[0] = FALSE;
	if (key == A_KEY || key == D_KEY)
		game->player.move[1] = FALSE;
	if (key == R_ARR_KEY)
		game->player.rota[0] = FALSE;
	if (key == L_ARR_KEY)
		game->player.rota[1] = FALSE;
	if (key == ESC_KEY)
		exit_game(game, EXIT_SUCCESS);
	if (key == E_KEY && game->grp->curr)
		game->grp->curr->anim.play = TRUE;
	if (key == M_KEY)
		game->map->is_map = !game->map->is_map;
	if (key == P_KEY)
	{
		game->player.mctrl = !game->player.mctrl;
		if (game->player.mctrl)
			mlx_mouse_hide(game->mlx, game->win);
		else
			mlx_mouse_show(game->mlx, game->win);
	}
	if (key == SHIFT_KEY)
		game->player.speed = SPEED * 2;
	return (inpt_animation(game, key), SUCCESS);
}

int	mouse_press_handler(int button, int x, int y)
{
	t_game	*game;

	game = get_game();
	(void)x;
	(void)y;
	if (button == L_CLICK)
	{
		game->player.attack = TRUE;
	}
	return (SUCCESS);
}

int	mouse_relse_handler(int button, int x, int y)
{
	t_game	*game;
	int		index;

	game = get_game();
	(void)x;
	(void)y;
	index = game->player.slot->index;
	if (button == L_CLICK)
	{
		game->player.attack = FALSE;
	}
	if (button == SCRL_UP || button == SCRL_DW)
	{
		if (button == SCRL_UP)
			index++;
		else
			index--;
		if (index < 0)
			index = 1;
		if (index > 1)
			index = 0;
		index += NUM_STR;
		inpt_animation(game, index);
	}
	return (SUCCESS);
}

int	mouse_moves_handler(int x, int y, t_game *game)
{
	static int	last_x = WIN_W / 2;
	int			delt_x;

	(void)y;
	if (game->player.mctrl == FALSE)
	{
		return (FAILURE);
	}
	delt_x = x - last_x;
	if (delt_x != 0)
	{
		game->player.velocity += deg_to_rad(delt_x * MOUSE_SENS);
	}
	last_x = x;
	return (SUCCESS);
}

// int	mouse_moves_handler(int x, int y)
// {
// 	static int	last_x = WIN_W / 2;
// 	int			delt_x;
//
// 	(void)y;
// 	if (get_game()->player.mctrl == FALSE)
// 		return (FAILURE);
// 	if ((delt_x = x - last_x) != 0)
// 	{
// 		get_game()->player.theta += deg_to_rad(delt_x * MOUSE_SENS);
// 	}
// 	last_x = x;
// 	return (SUCCESS);
// }

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
