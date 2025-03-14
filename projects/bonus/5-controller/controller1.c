/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 23:31:53 by ytop              #+#    #+#             */
/*   Updated: 2025/03/12 18:38:57 by ytop             ###   ########.fr       */
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
