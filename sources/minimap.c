/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:34:37 by ytop              #+#    #+#             */
/*   Updated: 2024/12/12 15:57:02 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		if (image.addr)
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

void	draw_player(void)
{
	t_game	*game;
	int		index;

	game = get_game();
	draw_circle(game->img->minimap, game->player.plane, game->map->scale, H_R);
	index = 0;
	while (index < FOV / HIT)
	{
		draw_hit(game->img->minimap, typecast_size(game->player.plane), typecast_size(game->rays[index].pos), H_G);
		index++;
	}
}

void	minimap(void)
{
	t_game	*game;
	t_coord	coord;
	int		value;

	game = get_game();
	coord.y = 0;
	while (coord.y < game->map->size.y)
	{
		coord.x = 0;
		while (coord.x < game->map->size.x)
		{
			value = game->map->map[(int)coord.y][(int)coord.x];
			if (value == WALL)
				draw_rectangle(game->img->minimap, coord, game->map->scale, H_W);
			else
				draw_rectangle(game->img->minimap, coord, game->map->scale, H_Y);
			coord.x++;
		}
		coord.y++;
	}
	draw_player();
}

void	minimap_loop(void)
{
	t_game	*game;

	game = get_game();
	if (game->map->is_map == FALSE)
	{
		return ;
	}
	minimap();
}
