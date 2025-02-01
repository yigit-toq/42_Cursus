/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 20:35:40 by ytop              #+#    #+#             */
/*   Updated: 2025/01/24 13:19:55 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	add_slot(t_slot *slot, int curr, t_anim *anim, int loop)
{
	static int	index;

	slot->index = index++;
	slot->take = &anim[0];
	slot->idle = &anim[1];
	slot->skin = &anim[2];
	slot->fire = &anim[3];
	slot->curr = &anim[curr];
	slot->curr->loop = loop;
}

// anim[0] = take, anim[1] = idle, anim[2] = skin, anim[3] = fire

void	init_slot(void)
{
	t_game	*game;

	game = get_game();
	init_animation(&game->img->knife[0], (t_size){0, 15}, 2, KNIFE_TAKE);
	init_animation(&game->img->knife[1], (t_size){0, 10}, 2, KNIFE_IDLE);
	add_slot(&game->player.slots[0], 1, game->img->knife, TRUE);
	init_animation(&game->img->vandal[0], (t_size){0, 15}, 2, VANDAL_TAKE);
	init_animation(&game->img->vandal[1], (t_size){0, 20}, 2, VANDAL_IDLE);
	init_animation(&game->img->vandal[2], (t_size){0, 80}, 2, VANDAL_SKIN);
	init_animation(&game->img->vandal[3], (t_size){0, 05}, 2, VANDAL_SKIN);
	add_slot(&game->player.slots[1], 1, game->img->vandal, TRUE);
	init_animation(&game->img->qskill[0], (t_size){0, 07}, 2, QSKILL_TAKE);
	init_animation(&game->img->qskill[1], (t_size){0, 35}, 2, QSKILL_IDLE);
	init_animation(&game->img->qskill[3], (t_size){0, 05}, 2, QSKILL_FIRE);
	add_slot(&game->player.slots[2], 1, game->img->qskill, TRUE);
	init_animation(&game->img->rskill[3], (t_size){2, 10}, 2, RSKILL_FIRE);
	add_slot(&game->player.slots[3], 3, game->img->rskill, FALSE);
	game->player.slot = &game->player.slots[0];
	game->player.slot->curr->play = TRUE;
}
