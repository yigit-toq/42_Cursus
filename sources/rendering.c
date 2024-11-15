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
}

int	draw_circle(t_coord center, t_coord radius, int color)
{
	t_game	*game;
	t_coord	pos;
	t_coord	rds;
	t_coord rot;

	game = get_game();
	rds.x = pow(radius.x, 2);
	rds.y = pow(radius.y, 2);
	pos.y = -radius.y;
	while (pos.y <= radius.y)
	{
		pos.x = -radius.x;
		while (pos.x <= radius.x)
		{
			if ((pow(pos.x, 2) / rds.x) + (pow(pos.y, 2) / rds.y) <= 1)
				mlx_pixel_put(game->mlx, game->win, center.x + pos.x, center.y + pos.y, color);
			pos.x++;
		}
		pos.y++;
	}
	rot.x = center.x + (cos(game->player.theta) * radius.x);
	rot.y = center.y + (sin(game->player.theta) * radius.y);
	mlx_pixel_put(game->mlx, game->win, rot.x, rot.y, H_W);
	if (radius.x == radius.y)
		return (SUCCESS);
	else
		return (FAILURE);
	// for (double angle = 0; angle < 2 * PI; angle += 0.001)
	// {
    //     p_coord.x = center.x + radius.x * cos(angle);
    //     p_coord.y = center.y + radius.y * sin(angle);
    //     mlx_pixel_put(game->mlx, game->win, p_coord.x, p_coord.y, 0xFFFFFF);
    // }
}
