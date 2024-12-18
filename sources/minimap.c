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

#include "cub3d.h"

void	draw_player(void)
{
	t_game	*game;

	game = get_game();
	draw_circle(game->img->minimap, game->player.plane, game->map->scale, 0x030180);
	for (int i = 0; i < WIN_W; i++)
	{
		draw_hit(game->img->minimap, tc_size(game->player.plane), tc_size((t_vect){game->rays[i].pos.x, game->rays[i].pos.y}), 0xFF3E00);
	}
}

void	minimap(void)
{
	t_game	*game;
	t_size	index;
	int		value;

	game = get_game();
	index.y = 0;
	while (index.y < game->map->size.y)
	{
		index.x = 0;
		while (index.x < game->map->size.x)
		{
			value = game->map->map[index.y][index.x];

			if (value == 0)
				break ;

			if (value == WALL)
				draw_rectangle(game->img->minimap, tc_vect(index), game->map->scale, H_W);

			if (value == FLOOR || value == game->player.direction)
				draw_rectangle(game->img->minimap, tc_vect(index), game->map->scale, 0xD1DDDE);

			index.x++;
		}
		index.y++;
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
	mlx_put_image_to_window(game->mlx, game->win, game->img->minimap.img, 0, WIN_H - (game->map->size.y * game->map->scale.y));
}
