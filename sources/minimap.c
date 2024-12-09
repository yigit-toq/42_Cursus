/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:34:37 by ytop              #+#    #+#             */
/*   Updated: 2024/12/05 16:54:16 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_hit(t_game *game, t_size start, t_size curr, int color)
{
	t_size	step;
	t_size	dir;
	int		ero;
	int		ert;

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
	ero = dir.x - dir.y;
	while (start.x != curr.x || start.y != curr.y)
	{
		mlx_pixel_put(game->mlx, game->win, start.x, start.y, color);
		ert = 2 * ero;
		if (ert < dir.x)
		{
			ero += dir.x;
			start.y += step.y;
		}
		if (ert > -dir.y)
		{
			ero -= dir.y;
			start.x += step.x;
		}
	}
}

void	draw_player(void)
{
	t_game	*game;
	int		index;

	game = get_game();
	draw_circle(game->player.plane, game->map->scale, H_R);

	index = 0;
	while (index < FOV / HIT)
	{
		draw_hit(game, (t_size){game->player.plane.x, game->player.plane.y}, (t_size){game->rays[index].pos.x, game->rays[index].pos.y}, H_G);
		index++;
	}
}

void	minimap(void)
{
	t_game	*game;
	t_coord	coord;
	t_coord	limit;
	int		value;

	game = get_game();
	limit.x = game->map->size.x + game->map->pivot.x;
	limit.y = game->map->size.y + game->map->pivot.y;
	coord.y = game->map->pivot.y;
	while (coord.y < limit.y)
	{
		coord.x = game->map->pivot.x;
		while (coord.x < limit.x)
		{
			value = game->map->map
				[(int)(coord.y - game->map->pivot.y)]
				[(int)(coord.x - game->map->pivot.x)];
			if (value == WALL)
				draw_rectangle(coord, game->map->scale, H_W);
			else
				draw_rectangle(coord, game->map->scale, H_Y);
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
