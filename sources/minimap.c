/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:34:37 by ytop              #+#    #+#             */
/*   Updated: 2024/11/15 18:12:20 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	minimap(void)
{
	t_game	*game;
	t_coord	coord;
	t_coord	size;

	ft_bzero(&coord, sizeof(t_coord));
	game = get_game();
	size.x = SIZE; //WIDTH / game->map->width;
	size.y = SIZE; //HEIGHT / game->map->height;
	while (coord.y < game->map->height)
	{
		coord.x = 0;
		while (coord.x < game->map->width)
		{
			if (game->map->map[(int)coord.y][(int)coord.x] == WALL)
				draw_rectangle(coord, size, H_W);
			else
				draw_rectangle(coord, size, H_B);
			coord.x++;
		}
		coord.y++;
	}
	game->map->size = size;
}

void	minimap_loop(void)
{
	t_game	*game;
	t_coord size;

	game = get_game();
	if (game->map->map_hl == FALSE)
	{
		return ;
	}
	size.x = SIZE / 4;
	size.y = SIZE / 4;
	draw_circle(game->player.position, size, H_R);
}
