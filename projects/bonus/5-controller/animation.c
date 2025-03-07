/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 17:30:09 by ytop              #+#    #+#             */
/*   Updated: 2025/03/07 18:40:46 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

#include <stdio.h>

// void	init_frame(t_data *frame, char *path, int *range)
// {
// 	char	t_path[100];
// 	char	*fstr;
// 	int		temp;
// 	int		size;
//
// 	size = 100;
// 	temp = range[0];
// 	while (range[0] < range[1])
// 	{
// 		fstr = ft_itoa(range[0] + 1);
// 		ft_strlcpy(t_path, path, size);
// 		ft_strlcat(t_path, fstr, size);
// 		ft_strlcat(t_path, ").xpm", size);
// 		frame[range[0] - temp] = add_image(t_path, (t_size){0, 0});
// 		range[0]++;
// 		gfree(fstr);
// 	}
// }

static void	init_frame(t_data *frame, char *path, int start, int end)
{
	char	t_path[100];
	int		temp;

	temp = start;
	while (start < end)
	{
		snprintf(t_path, 100, "%s (%d).xpm", path, start + 1);
		frame[start - temp] = add_image(t_path, (t_size){0, 0});
		start++;
	}
}

void	input_animation(int key)
{
	t_game	*game;

	game = get_game();
	if (key == Y_KEY)
	{
		if (!game->player.slot->skin)
			return ;
		game->player.slot->curr->play = FALSE;
		game->img->next_anim = game->player.slot->skin;
	}
	if (key == ONE_KEY || key == TWO_KEY || key == C_KEY)
	{
		if (key == ONE_KEY)
			game->player.slot = &game->player.slots[0];
		if (key == TWO_KEY)
			game->player.slot = &game->player.slots[1];
		if (key == C_KEY)
			game->player.slot = &game->player.slots[2];
		game->player.slot->curr->play = FALSE;
		game->img->next_anim = game->player.slot->take;
	}
	if (key == X_KEY)
	{
		game->player.slot->curr->play = FALSE;
		game->player.slot = &game->player.slots[3];
		game->img->next_anim = game->player.slot->fire;
		game->player.slot->curr->index = 0;
	}
}

void	updt_animation(t_anim *anim, int reverse)
{
	t_game	*game;

	game = get_game();
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
			if (anim == game->player.slot->skin || anim == game->player.slot->take)
			{
				swap_animation(anim, game->player.slot->idle);
			}
			if (anim == game->player.slot->fire)
			{
				game->player.slot = &game->player.slots[1];
				swap_animation(anim, game->player.slot->idle);
			}
			if (anim == &game->grp->curr->anim)
			{
				if (game->grp->curr->state)
				{
					game->grp->curr->anim.index = 0;
					game->grp->curr->anim.frame = game->grp->curr->anim.frames;
					game->grp->curr->state = FALSE;
				}
				else
				{
					game->grp->curr->anim.index = game->grp->curr->anim.total - 1;
					game->grp->curr->anim.frame = &game->grp->curr->anim.frames[game->grp->curr->anim.total - 1];
					game->grp->curr->state = TRUE;
				}
			}
		}
	}
}

void	swap_animation(t_anim *anim, t_anim *new)
{
	t_game	*game;

	game = get_game();
	if (anim->play == FALSE)
	{
		game->player.slot->curr = new;
		new->frame = new->frames;
		new->index = 0;
		new->play = TRUE;
	}
	updt_animation(game->player.slot->curr, FALSE);
}

void	init_animation(t_anim *anim, t_size range, int delay, char *path)
{
	int	total;

	ft_bzero(anim, sizeof(t_anim));
	total = range.y - range.x;
	anim->frames = ft_calloc(total, sizeof(t_data));
	error_controller("Memory failed", anim->frames);
	anim->total = total;
	anim->delay = delay;
	anim->frame = anim->frames;
	init_frame(anim->frames, path, range.x, range.y);
}
