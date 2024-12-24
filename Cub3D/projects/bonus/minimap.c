/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:34:37 by ytop              #+#    #+#             */
/*   Updated: 2024/12/18 18:19:54 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_player(t_size scale)
{
	t_game	*game;
	t_vect	plane;
	t_size	index;

	game = get_game();
	plane.x = grid_to_center(game->player.pos.x, scale.x);
	plane.y = grid_to_center(game->player.pos.y, scale.y);

	draw_circle(game->img->minimap, plane, tc_vect(scale), 0x030180);

	for (int i = 0; i < WIN_W; i++)
	{
		index.x = floor((game->rays[i].plane.x / game->map->scale.x) * scale.x);
		index.y = floor((game->rays[i].plane.y / game->map->scale.y) * scale.y);
		// draw_hit(game->img->minimap, tc_size(plane), index, 0xFF3E00);
	}
	(void)index;
}

void	minimap(void)
{
	t_game	*game;
	t_size	index;
	t_size	scale;
	int		value;

	game = get_game();
	ft_bzero(&index, sizeof(t_size));
	scale.x = game->map->mini.x;
	scale.y = game->map->mini.y;
	while (index.y < game->map->size.y)
	{
		index.x = 0;
		while (index.x < game->map->size.x)
		{
			value = game->map->map[index.y][index.x];

			if (value == 0)
				break ;

			if (value == WALL)
				draw_rectangle(game->img->minimap, tc_vect(index), tc_vect(scale), H_W);

			if (value == FLOOR || value == game->player.direction)
				draw_rectangle(game->img->minimap, tc_vect(index), tc_vect(scale), H_G);

			index.x++;
		}
		index.y++;
	}
	draw_player(scale);
}

void	minimap_loop(void)
{
	t_game	*game;
	t_map	*map;
	void	*img;

	game = get_game();
	map = game->map;
	if (map->is_map == FALSE)
	{
		return ;
	}
	minimap();
	img = game->img->minimap.img;
	mlx_put_image_to_window(game->mlx, game->win, img, map->pivot.x, map->pivot.y);
}
