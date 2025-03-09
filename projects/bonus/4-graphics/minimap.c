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

static void	draw_player(void)
{
	t_game	*game;
	t_vect	plane;
	t_vect	scale;

	game = get_game();
	scale.x = game->map->mini.x / (TILE * 1.5);
	scale.y = game->map->mini.y / (TILE * 1.5);
	plane.x = game->map->mini.x / 2;
    plane.y = game->map->mini.y / 2;
    draw_rect(game->img->minimap, plane, scale, H_R);
}

static void	draw_minimap_utils(int x, int y)
{
	t_game	*game;
	t_vect	coord;
	t_vect	mini;
	char	value;

	game = get_game();
	mini = tc_vect(game->map->mini);
	coord.x = (game->player.pos.x - (TILE / 2)) + (x * TILE) / mini.x;
	coord.y = (game->player.pos.y - (TILE / 2)) + (y * TILE) / mini.y;
	if (coord.x >= game->map->size.x || coord.y >= game->map->size.y)
		value = WALL;
	else
		value = game->map->map[(int)floor(coord.y)][(int)floor(coord.x)];
	if (value == FLOOR || value == game->player.direction)
		mlx_image_put(game->img->minimap, x, y, H_G);
	else
		mlx_image_put(game->img->minimap, x, y, H_W);
}

static void	draw_minimap(void)
{
	t_game	*game;
	t_size	index;

	game = get_game();
	ft_bzero(&index, sizeof(t_size));
	while (index.y < game->map->mini.y)
	{
		index.x = 0;
		while (index.x < game->map->mini.x)
		{
			draw_minimap_utils(index.x, index.y);
			index.x++;
		}
		index.y++;
	}
	draw_player();
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
