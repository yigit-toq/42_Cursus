/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:10:27 by ytop              #+#    #+#             */
/*   Updated: 2025/03/09 16:10:27 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	render_player(int x, int y)
{
	t_game			*game;
	t_data			frame;
	t_size			img_p;
	unsigned int	color;

	game = get_game();
	frame = *game->player.slot->curr->frame;
	img_p.x = (x * frame.w_s) / WIN_W;
	img_p.y = (y * frame.h_s) / WIN_H;
	color = pixel_color(frame, img_p.x, img_p.y);
	if (image_filter(0, color, 'g', 200) || image_filter(1, color, 'g', 200)
		|| image_filter(2, color, 'g', 200) || image_filter(3, color, 'g', 200))
	{
		mlx_image_put(game->img->bgframe, x, y, color);
		return (TRUE);
	}
	return (FALSE);
}

static int	render_crossh(int x, int y)
{
	t_game			*game;
	t_size			cross;
	unsigned int	color;

	game = get_game();
	cross.x = (WIN_W / 2) - 32;
	cross.y = (WIN_H / 2) - 32;
	if ((x > cross.x && x < cross.x + 64) && (y > cross.y && y < cross.y + 64))
	{
		color = pixel_color(game->img->crossh, x - cross.x, y - cross.y);
		if (color == 0x000000)
		{
			mlx_image_put(game->img->bgframe, x, y, game->img->hex[0]);
			return (TRUE);
		}
	}
	return (FALSE);
}

int	render_object(int x, int y)
{
	if (render_player(x, y))
		return (TRUE);
	if (render_crossh(x, y))
		return (TRUE);
	return (FALSE);
}
