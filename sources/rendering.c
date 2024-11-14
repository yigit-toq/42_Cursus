/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:13:24 by ytop              #+#    #+#             */
/*   Updated: 2024/11/14 16:22:07 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_tile(int x, int y, int size, int color, double theta)
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
	int center_x = x + size / 2;
	int center_y = y + size / 2;

	// Karakterin yönünü gösteren çizgi uzunluğu
	int line_length = size; // Çizginin uzunluğunu karakterin boyutuna göre ayarlayabilirsin

	// Çizginin bitiş noktasını hesapla
	int line_x = center_x + (int)(cos(theta) * line_length);
	int line_y = center_y + (int)(sin(theta) * line_length);

	// Çizgiyi çiz (karakterin baktığı yön)
	mlx_pixel_put(game->mlx, game->win, line_x, line_y, 0xFFFFFF);
}
