/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:34:37 by ytop              #+#    #+#             */
/*   Updated: 2024/11/26 16:51:12 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//HEIGHT / game->map->height;
//WIDTH / game->map->width;

void	minimap(void)
{
	t_game	*game;
	t_coord	coord;
	t_coord	posit;

	ft_bzero(&coord, sizeof(t_coord));
	game = get_game();
	game->map->scale.x = MINIMAP;
	game->map->scale.y = MINIMAP;
	while (coord.y < game->map->height)
	{
		coord.x = 0;
		while (coord.x < game->map->width)
		{
			if (game->map->map[(int)coord.y][(int)coord.x] == WALL)
				draw_rectangle(coord, game->map->scale, H_W);
			else
				draw_rectangle(coord, game->map->scale, H_B);
			coord.x++;
		}
		coord.y++;
	}
	posit.x = (game->player.position.x * game->map->scale.x) + (game->map->scale.x / 2);
	posit.y = (game->player.position.y * game->map->scale.y) + (game->map->scale.y / 2);
	draw_circle(posit, game->map->scale, H_R);
	draw_line(posit, game->player.theta, 100, H_W);
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
