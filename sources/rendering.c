/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:13:24 by ytop              #+#    #+#             */
/*   Updated: 2024/10/29 14:13:24 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_tile(int x, int y, int size, int color)
{
	t_game	*game;
	int		h;
	int		w;

	game = get_game();
	h = 0;
	w = 0;
	while (h < size)
	{
		w = 0;
		while (w < size)
		{
			mlx_pixel_put(game->mlx, game->win, x + w, y + h, color);
			w++;
		}
		h++;
	}
}
