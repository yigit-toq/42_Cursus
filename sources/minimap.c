/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:34:37 by ytop              #+#    #+#             */
/*   Updated: 2024/10/30 17:34:37 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	minimap(void)
{
	t_game	*game;
	int		size;
	int		x;
	int		y;

	x = 0;
	y = 0;
	game = get_game();
	size = (WIDTH / 4) / game->map->width;
	while (y < game->map->height)
	{
		x = 0;
		while (x < game->map->width)
		{
			if (game->map->map[y][x] == WALL)
				render_tile(x * size, y * size, size, H_W);
			else
				render_tile(x * size, y * size, size, H_B);
			x++;
		}
		y++;
	}
	game->map->size = size;
}

void	minimap_loop(void)
{
	t_game	*game;
	double	size;
	double	p[2];

	game = get_game();
	if (game->map->map_hl == FALSE)
	{
		return ;
	}
	size = game->map->size;
	p[0] = game->player.position.x;
	p[1] = game->player.position.y;
	render_tile(p[0] * size, p[1] * size, size, H_R);
}
