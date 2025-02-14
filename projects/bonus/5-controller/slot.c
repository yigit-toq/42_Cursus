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
	if (anim[TAKE].frame)
		slot->take = &anim[TAKE];
	if (anim[IDLE].frame)
		slot->idle = &anim[IDLE];
	if (anim[FIRE].frame)
		slot->fire = &anim[FIRE];
	if (anim[SKIN].frame)
		slot->skin = &anim[SKIN];
	slot->curr = &anim[curr];
	slot->curr->loop = loop;
}

static t_gun	*init_gun(int total, int range, int damage)
{
	t_gun	*gun;

	gun = ft_calloc(1, sizeof(t_gun));
	gun->total = total;
	if (total < 30)
		gun->ammo = total;
	else
		gun->ammo = 30;
	gun->range = range;
	gun->damage = damage;
	return (gun);
}

// anim[0] = take, anim[1] = idle, anim[2] = skin, anim[3] = fire

void	init_slot(void)
{
	t_game	*game;

	game = get_game();
	init_animation(&game->img->knife[TAKE], (t_size){0, 15}, 2, KNIFE_TAKE);
	init_animation(&game->img->knife[IDLE], (t_size){0, 10}, 2, KNIFE_IDLE);
	add_slot(&game->player.slots[0], 1, game->img->knife, TRUE);
	init_animation(&game->img->vandal[TAKE], (t_size){0, 15}, 2, VANDAL_TAKE);
	init_animation(&game->img->vandal[IDLE], (t_size){0, 20}, 2, VANDAL_IDLE);
	init_animation(&game->img->vandal[FIRE], (t_size){0, 04}, 2, VANDAL_FIRE);
	init_animation(&game->img->vandal[SKIN], (t_size){0, 80}, 2, VANDAL_SKIN);
	add_slot(&game->player.slots[1], 1, game->img->vandal, TRUE);
	init_animation(&game->img->qskill[TAKE], (t_size){0, 07}, 2, QSKILL_TAKE);
	init_animation(&game->img->qskill[IDLE], (t_size){0, 35}, 2, QSKILL_IDLE);
	init_animation(&game->img->qskill[FIRE], (t_size){0, 05}, 2, QSKILL_FIRE);
	add_slot(&game->player.slots[2], 1, game->img->qskill, TRUE);
	init_animation(&game->img->rskill[FIRE], (t_size){2, 10}, 2, RSKILL_FIRE);
	add_slot(&game->player.slots[3], 3, game->img->rskill, FALSE);

	game->player.slot = &game->player.slots[0];
	game->player.slot->curr->play = TRUE;

	game->player.slots[1].gun = init_gun(120, 10, 10);
	game->player.slots[2].gun = init_gun(001, 10, 00);	

	game->door = ft_calloc(game->count.door, sizeof(t_door));
	while (game->count.door--)
	{
		init_animation(&game->door[game->count.door].anim, (t_size){0, 9}, 1, DOOR_PATH);
	}
	game->door->anim.play = TRUE;
}
