/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 17:30:09 by ytop              #+#    #+#             */
/*   Updated: 2024/12/27 17:19:20 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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

void	init_frame(t_data *frame, char *path, int *range)
{
	char	t_path[100];
	int		temp;

	temp = range[0];
	while (range[0] < range[1])
	{
		snprintf(t_path, 100, "%s (%d).xpm", path, range[0] + 1);
		frame[range[0] - temp] = add_image(t_path, (t_size){0, 0});
		range[0]++;
	}
}

void	init_animation(t_anim *anim, int *range, int delay, char *path)
{
	int	total;

	total = range[1] - range[0];
	ft_bzero(anim, sizeof(t_anim));
	anim->frames = ft_calloc(total, sizeof(t_data));
    anim->total = total;
    anim->delay = delay;
	anim->frame = anim->frames;
	init_frame(anim->frames, path, (int[2]){range[0], range[1]});
}

void	swap_animation(t_anim *c_anim, t_anim *n_anim)
{
	t_game	*game;

	game = get_game();
	if (c_anim->play == FALSE)
	{
		game->player.slot->curr = n_anim;
		n_anim->play = TRUE;
		c_anim->counter = 0;
		c_anim->index = 0;
	}
}

void	update_animation(t_anim	*anim)
{
	if (!anim->play)
		return ;
	if (++anim->counter == anim->delay)
    {
        anim->counter = 0;
        anim->index = (anim->index + 1) % anim->total;
        anim->frame = anim->frames + anim->index;
		if (!anim->index && !anim->loop)
			anim->play = FALSE;
    }
}
