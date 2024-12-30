/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 20:35:40 by ytop              #+#    #+#             */
/*   Updated: 2024/12/30 13:58:32 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	add_slot(t_slot *slot, int curr, t_anim *anim, int *active)
{
	static int	index;

	slot->index = index++;
	if (active[0])
		slot->take = &anim[0];
	if (active[1])
		slot->idle = &anim[1];
	if (active[2])
		slot->skin = &anim[2];
	if (active[3])
		slot->fire = &anim[3];
	if (active[curr])
		slot->curr = &anim[curr];
	slot->curr->loop = TRUE;
}

void	init_slot(void)
{
	t_game	*game;

	game = get_game();
	init_animation(&game->img->knife[0], (int[2]){0, 15}, 2, KNF_TAKE);
	init_animation(&game->img->knife[1], (int[2]){0, 10}, 2, KNF_IDLE);
	init_animation(&game->img->vandal[0], (int[2]){0, 15}, 2, GUN_TAKE);
	init_animation(&game->img->vandal[1], (int[2]){0, 20}, 2, GUN_IDLE);
	init_animation(&game->img->vandal[2], (int[2]){0, 80}, 2, GUN_SKIN);
	init_animation(&game->img->qskill[0], (int[2]){0, 07}, 2, QSK_TAKE);
	init_animation(&game->img->qskill[1], (int[2]){0, 35}, 2, QSK_IDLE);
	init_animation(&game->img->qskill[3], (int[2]){0, 05}, 2, QSK_FIRE);
	init_animation(&game->img->rskill[3], (int[2]){0, 10}, 2, RSK_FIRE);
	add_slot(&game->player.slots[0], 1, game->img->knife, (int[4]){1, 1, 0, 0});
	add_slot(&game->player.slots[1], 1, game->img->vandal, (int[4]){1, 1, 1, 0});
	add_slot(&game->player.slots[2], 1, game->img->qskill, (int[4]){1, 1, 0, 1});
	add_slot(&game->player.slots[3], 3, game->img->rskill, (int[4]){0, 0, 0, 1});
	game->player.slots[3].curr->loop = FALSE;
	game->player.slot = &game->player.slots[0];
	game->player.slot->curr->play = TRUE;
}
