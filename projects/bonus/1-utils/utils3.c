/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 00:36:08 by ytop              #+#    #+#             */
/*   Updated: 2025/03/07 18:02:37 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

#include <mlx.h>

unsigned int	rgb_to_hexa(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | (b << 0));
}

unsigned int	pixel_color(t_data img, int x, int y)
{
	char	*pixel_address;

	if (x < 0 || y < 0 || x >= img.w_s || y >= img.h_s)
		return (FALSE);
	else
	{
		pixel_address = img.add + (y * img.length) + (x * (img.bit_pp / 8));
		return (*(unsigned int *)pixel_address);
	}
}

void	mlx_image_put(t_data img, int x, int y, unsigned int color)
{
	char	*pixel_address;

	if (x >= 0 && y >= 0 && x < img.w_s && y < img.h_s)
	{
		pixel_address = img.add + (y * img.length) + (x * (img.bit_pp / 8));
		*(unsigned int *)pixel_address = color;
	}
}

int	image_filter(int index, int color, char filter, int limit)
{
	t_game	*game;
	int		value;

	game = get_game();
	if (filter == 'g')
		value = (color >> 8) & 255;
	if (filter == 'b')
		value = (color >> 0) & 255;
	return (value < limit && game->player.slot->index == index);
}

int	mouse_inside_window(void)
{
	t_game	*game;
	int		x;
	int		y;

	game = get_game();
	mlx_mouse_get_pos(game->mlx, game->win, &x, &y);
	return (x >= 0 && x < WIN_W && y >= 0 && y < WIN_H);
}
