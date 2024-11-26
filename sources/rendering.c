/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:13:24 by ytop              #+#    #+#             */
/*   Updated: 2024/11/26 16:39:55 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_line(t_coord pos, double theta, double range, int color)
{
	t_game	*game;
	double	steps;
	int		index;
	t_coord	coord;
	t_coord	end;

	game = get_game();
	index = 0;
	end.x = pos.x + range * cos(theta);
	end.y = pos.y + range * sin(theta);
	coord.x = end.x - pos.x;
	coord.y = end.y - pos.y;
	steps = fmax(fabs(coord.x), fabs(coord.y));
	coord.x = coord.x / steps;
	coord.y = coord.y / steps;
	while (index <= (int)steps)
	{
		mlx_pixel_put(game->mlx, game->win, (int)pos.x, (int)pos.y, color);
		pos.x += coord.x;
		pos.y += coord.y;
		index++;
	}
}

void	draw_rectangle(t_coord center, t_coord size, int color)
{
	t_game	*game;
	t_coord	pos;

	game = get_game();
	center.x *= size.x;
	center.y *= size.y;
	ft_bzero(&pos, sizeof(t_coord));
	while (pos.y < size.y)
	{
		pos.x = 0;
		while (pos.x < size.x)
		{
			mlx_pixel_put(game->mlx, game->win, center.x + pos.x, center.y + pos.y, color);
			pos.x++;
		}
		pos.y++;
	}
}

int	draw_circle(t_coord center, t_coord radius, int color)
{
	t_game	*game;
	t_coord	pos;
	t_coord	rot;
	t_coord	rds;

	game = get_game();
	radius.x /= 2;
	radius.y /= 2;
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
}

// for (double angle = 0; angle < 2 * PI; angle += 0.001)
// {
//     p_coord.x = center.x + radius.x * cos(angle);
//     p_coord.y = center.y + radius.y * sin(angle);
//     mlx_pixel_put(game->mlx, game->win, p_coord.x, p_coord.y, 0xFFFFFF);
// }
