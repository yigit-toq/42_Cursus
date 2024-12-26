/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:13:24 by ytop              #+#    #+#             */
/*   Updated: 2024/12/17 14:30:37 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_hit(t_data image, t_size start, t_size curr, int color)
{
	t_game	*game;
	t_size	step;
	t_size	dir;
	int		er1;
	int		er2;

	game = get_game();
	dir.x = abs(curr.x - start.x);
	dir.y = abs(curr.y - start.y);
	if (start.x < curr.x)
		step.x = +1;
	else
		step.x = -1;
	if (start.y < curr.y)
		step.y = +1;
	else
		step.y = -1;
	er1 = dir.x - dir.y;
	while (start.x != curr.x || start.y != curr.y)
	{
		if (image.add)
			mlx_image_put(image, start.x, start.y, color);
		else
			mlx_pixel_put(game->mlx, game->win, start.x, start.y, color);
		er2 = 2 * er1;
		if (er2 < +dir.x)
		{
			er1 += dir.x;
			start.y += step.y;
		}
		if (er2 > -dir.y)
		{
			er1 -= dir.y;
			start.x += step.x;
		}
	}
}

void	draw_rays(t_data data, t_vect pos, double theta, int color)
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

void	draw_line(t_data data, t_vect pos, double theta, double range, int color)
{
	t_game	*game;
	t_vect	coord;
	t_vect	limit;
	double	steps;
	int		index;

	game = get_game();
	index = 0;
	limit.x = pos.x + range * cos(theta);
	limit.y = pos.y + range * sin(theta);
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

void	draw_rectangle(t_data data, t_vect center, t_vect size, int color)
{
	t_game	*game;
	t_vect	pos;
	t_vect	put;

	game = get_game();
	center.x *= size.x;
	center.y *= size.y;
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

int	draw_circle(t_data data, t_vect center, t_vect radius, int color)
{
	t_game	*game;
	t_vect	pos;
	t_vect	rds;
	t_vect	put;

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
			{
				put.x = center.x + pos.x;
				put.y = center.y + pos.y;
				if (data.add)
					mlx_image_put(data, put.x, put.y, color);
				else
					mlx_pixel_put(game->mlx, game->win, put.x, put.y, color);
			}
			pos.x++;
		}
		pos.y++;
	}
	if (radius.x == radius.y)
		return (SUCCESS);
	else
		return (FAILURE);
}

// rot.x = center.x + (cos(game->player.theta) * radius.x);
// rot.y = center.y + (sin(game->player.theta) * radius.y);
// mlx_pixel_put(game->mlx, game->win, rot.x, rot.y, H_W);

// for (double angle = 0; angle < 2 * PI; angle += 0.001)
// {
//     p_coord.x = center.x + radius.x * cos(angle);
//     p_coord.y = center.y + radius.y * sin(angle);
//     mlx_pixel_put(game->mlx, game->win, p_coord.x, p_coord.y, 0xFFFFFF);
// }
