/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:13:24 by ytop              #+#    #+#             */
/*   Updated: 2024/11/15 18:14:55 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

void	draw_rectangle(t_coord coord, t_coord size, int color)
{
	t_game	*game;
	t_coord	s_i;

	game = get_game();
	coord.x *= size.x;
	coord.y *= size.y;
	ft_bzero(&s_i, sizeof(t_coord));
	while (s_i.y < size.y)
	{
		s_i.x = 0;
		while (s_i.x < size.x)
		{
			mlx_pixel_put(game->mlx, game->win, coord.x + s_i.x, coord.y + s_i.y, color);
			s_i.x++;
		}
		s_i.y++;
	}
	// int center_x = x + size / 2;
	// int center_y = y + size / 2;

	// int line_length = size;

	// int line_x = center_x + (int)(cos(theta) * line_length);
	// int line_y = center_y + (int)(sin(theta) * line_length);

	// mlx_pixel_put(game->mlx, game->win, line_x, line_y, 0xFFFFFF);
}

#include <stdio.h>

int	draw_circle(t_coord center, t_coord radius)
{
	t_game	*game;
	double x, y;
    double r_squared = radius.x * radius.x;

	game = get_game();
    for (y = -radius.y; y <= radius.y; y++)
	{
        for (x = -radius.x; x <= radius.x; x++)
		{
            if (x * x + y * y <= r_squared) {
                mlx_pixel_put(game->mlx, game->win, center.x + x, center.y + y, 0xFF0000);
            }
        }
    }
	// for (double angle = 0; angle < 2 * PI; angle += 0.001)
	// {
    //     p_coord.x = center.x + radius.x * cos(angle);
    //     p_coord.y = center.y + radius.y * sin(angle);
    //     mlx_pixel_put(game->mlx, game->win, p_coord.x, p_coord.y, 0xFFFFFF);
    // }
	if (radius.x == radius.y)
		return (SUCCESS);
	else
		return (FAILURE);
}
