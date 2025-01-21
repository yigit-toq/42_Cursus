/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 19:53:49 by ytop              #+#    #+#             */
/*   Updated: 2025/01/16 20:26:01 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

#include "mlx.h"

unsigned int	pixel_color(t_data img, int x, int y)
{
	char	*pixel_address;

	if (x < 0 || y < 0 || x >= img.w_s || y >= img.h_s)
		return (0);
	pixel_address = img.add + (y * img.length) + (x * (img.bit_pp / 8));
	return (*(unsigned int *)pixel_address);
}

void	mlx_image_put(t_data img, int x, int y, unsigned int color)
{
	char	*pixel_address;

	if (x >= 0 && y >= 0 && x < img.w_s && y < img.h_s)
	{
		pixel_address = img.add + (y * img.length) + (x * (img.bit_pp / 8));
		*(unsigned int *)pixel_address = color;
	}
}
