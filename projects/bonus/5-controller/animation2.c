/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 17:07:57 by ytop              #+#    #+#             */
/*   Updated: 2025/03/09 17:07:57 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	door_animation(t_anim *anim)
{
	t_game	*game;
	t_door	*door;

	game = get_game();
	door = game->utl->curr;
	if (anim == &door->anim)
	{
		if (door->state)
		{
			door->anim.index = 0;
			door->anim.frame = &door->anim.frames[door->anim.index];
			door->state = 0;
		}
		else
		{
			door->anim.index = door->anim.total - 1;
			door->anim.frame = &door->anim.frames[door->anim.index];
			door->state = 1;
		}
	}
}

static void	plyr_animation(t_anim *anim)
{
	t_game	*game;
	t_slot	*slot;

	game = get_game();
	slot = game->player.slot;
	if (anim == slot->skin || anim == slot->take)
	{
		swap_animation(anim, slot->idle);
	}
	if (anim == slot->fire)
	{
		slot = &game->player.slots[1];
		swap_animation(anim, slot->idle);
	}
}

void	updt_animation(t_anim *anim, int reverse)
{
	if (!anim->play)
		return ;
	if (++anim->counter == anim->delay)
	{
		anim->counter = 0;
		if (reverse)
			anim->index = (anim->index - 1) % anim->total;
		else
			anim->index = (anim->index + 1) % anim->total;
		anim->frame = anim->frames + anim->index;
		if (!anim->index && !anim->loop)
		{
			anim->play = FALSE;
			plyr_animation(anim);
			door_animation(anim);
		}
	}
}
