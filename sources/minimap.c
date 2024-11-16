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

//HEIGHT / game->map->height;
//WIDTH / game->map->width;

void	minimap(void)
{
	t_game	*game;
	t_coord	coord;

	ft_bzero(&coord, sizeof(t_coord));
	game = get_game();
	game->map->size.x = M_SIZE;
	game->map->size.y = M_SIZE;
	while (coord.y < game->map->height)
	{
		coord.x = 0;
		while (coord.x < game->map->width)
		{
			if (game->map->map[(int)coord.y][(int)coord.x] == WALL)
				draw_rectangle(coord, game->map->size, H_W);
			else
				draw_rectangle(coord, game->map->size, H_B);
			coord.x++;
		}
		coord.y++;
	}
}

void	minimap_loop(void)
{
	t_game	*game;
	t_coord	size;

	game = get_game();
	if (game->map->map_hl == FALSE)
	{
		return ;
	}
	minimap();
	size.x = game->map->size.x;
	size.y = game->map->size.y;
	draw_circle(game->player.position, size, H_R);
}
