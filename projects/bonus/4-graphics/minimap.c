/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:34:37 by ytop              #+#    #+#             */
/*   Updated: 2025/03/07 17:39:00 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

#include <math.h>

#include <mlx.h>

static void	draw_player(t_size scale)
{
	t_game	*game;
	t_vect	plane;
	t_size	index;
	int		i;

	game = get_game();
	plane.x = grid_to_ct(game->player.pos.x, scale.x);
	plane.y = grid_to_ct(game->player.pos.y, scale.y);
	draw_circ(game->img->minimap, plane, tc_vect(scale), 0x030180);
	i = 0;
	while (i < WIN_W)
	{
		index.x = floor((game->rays[i].plane.x / game->map->scale.x) * scale.x);
		index.y = floor((game->rays[i].plane.y / game->map->scale.y) * scale.y);
		i++;
	}
	(void)index;
}

// draw_hit(game->img->minimap, tc_size(plane), index, 0xFF3E00);

static void	draw_minimap(void)
{
	t_game	*game;
	t_size	index;
	int		value;

	game = get_game();
	ft_bzero(&index, sizeof(t_size));
	while (index.y < game->map->size.y)
	{
		index.x = 0;
		while (index.x < game->map->size.x)
		{
			value = game->map->map[index.y][index.x];
			if (value == 0)
				break ;
			if (value == WALL)
				draw_rect(game->img->minimap, tc_vect(index),
					tc_vect(game->map->mini), H_W);
			if (value == FLOOR || value == game->player.direction)
				draw_rect(game->img->minimap, tc_vect(index),
					tc_vect(game->map->mini), H_G);
			index.x++;
		}
		index.y++;
	}
	draw_player(game->map->mini);
}

void	minimap(void)
{
	t_size	pivot;
	t_game	*game;
	void	*img;

	game = get_game();
	if (game->map->is_map == FALSE)
	{
		return ;
	}
	draw_minimap();
	img = game->img->minimap.img;
	pivot.x = game->map->pivot.x;
	pivot.y = game->map->pivot.y;
	mlx_put_image_to_window(game->mlx, game->win, img, pivot.x, pivot.y);
}
