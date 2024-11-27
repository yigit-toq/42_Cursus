/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:34:37 by ytop              #+#    #+#             */
/*   Updated: 2024/11/27 18:05:33 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//HEIGHT / game->map->height;
//WIDTH / game->map->width;

void	draw_rays_in_pov(t_coord pos, double theta)
{
}

void	draw_player(void)
{
	t_game	*game;

	game = get_game();
	draw_circle(game->player.plane, game->map->size, H_R);

	draw_rays_in_pov(game->player.plane, game->player.theta);
}

void	minimap(void)
{
	t_game	*game;
	t_coord	coord;

	ft_bzero(&coord, sizeof(t_coord));
	game = get_game();
	game->map->size.x = MINIMAP * 2;
	game->map->size.y = MINIMAP * 2;
	game->player.plane.x = (game->player.position.x * game->map->size.x) + (game->map->size.x / 2);
	game->player.plane.y = (game->player.position.y * game->map->size.y) + (game->map->size.y / 2);
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
