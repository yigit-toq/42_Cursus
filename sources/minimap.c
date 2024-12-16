/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:34:37 by ytop              #+#    #+#             */
/*   Updated: 2024/12/16 17:28:38 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player(void)
{
	t_game	*game;

	game = get_game();
	draw_circle(game->img->minimap, game->player.plane, game->map->scale, H_R);
	for (int i = 0; i < WIN_W; i++)
	{
		draw_hit(game->img->minimap, typecast_size(game->player.plane), typecast_size(game->rays[i].pos), H_R);
	}
}

void	minimap(void)
{
	t_game	*game;
	t_vect	coord;
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

			if (value == FLOOR || value == game->player.direction)
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
