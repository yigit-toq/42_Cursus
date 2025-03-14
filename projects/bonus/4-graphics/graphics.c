/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:13:24 by ytop              #+#    #+#             */
/*   Updated: 2025/03/14 16:39:00 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

#include <math.h>

#include <mlx.h>

void	draw_ray(t_data data, t_vect pos, double theta, int color)
{
	t_game	*game;
	t_vect	coord;

	game = get_game();
	coord.x = cos(theta);
	coord.y = sin(theta);
	while (TRUE)
	{
		if (data.add)
			mlx_image_put(data, pos.x, pos.y, color);
		else
			mlx_pixel_put(game->mlx, game->win, pos.x, pos.y, color);
		pos.x += coord.x;
		pos.y += coord.y;
		if (pos.x < 0 || pos.x >= WIN_W || pos.y < 0 || pos.y >= WIN_H)
			break ;
	}
}

void	draw_line(t_data data, t_vect pos, t_vect vect, int color)
{
	t_game	*game;
	t_vect	coord;
	t_vect	limit;
	double	steps;
	int		index;

	game = get_game();
	index = 0;
	limit.x = pos.x + vect.x * cos(vect.y);
	limit.y = pos.y + vect.x * sin(vect.y);
	coord.x = limit.x - pos.x;
	coord.y = limit.y - pos.y;
	steps = fmax(fabs(coord.x), fabs(coord.y));
	coord.x = coord.x / steps;
	coord.y = coord.y / steps;
	while (index <= (int)steps)
	{
		if (data.add)
			mlx_image_put(data, pos.x, pos.y, color);
		else
			mlx_pixel_put(game->mlx, game->win, pos.x, pos.y, color);
		pos.x += coord.x;
		pos.y += coord.y;
		index++;
	}
}

void	draw_rect(t_data data, t_vect center, t_vect size, int color)
{
	t_game	*game;
	t_vect	pos;
	t_vect	put;

	game = get_game();
	ft_bzero(&pos, sizeof(t_vect));
	while (pos.y < size.y)
	{
		pos.x = 0;
		while (pos.x < size.x)
		{
			put.x = center.x + pos.x;
			put.y = center.y + pos.y;
			if (data.add)
				mlx_image_put(data, put.x, put.y, color);
			else
				mlx_pixel_put(game->mlx, game->win, put.x, put.y, color);
			pos.x++;
		}
		pos.y++;
	}
}
