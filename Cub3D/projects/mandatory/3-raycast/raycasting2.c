/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:13:24 by ytop              #+#    #+#             */
/*   Updated: 2024/12/17 14:30:37 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#include <math.h>

static void	draw_tex(double img_x, t_ray *ray, t_size pos, t_data img)
{
	double	img_y;
	int		color;

	img_y = ((pos.y - ray->wall.s_pos) * img.h_s) / (ray->wall.height * 2);
	if (img_y > img.h_s - 1)
		img_y = img.h_s - 1;
	color = pixel_color(img, img_x, img_y);
	mlx_image_put(get_game()->img->bgframe, pos.x, pos.y, color);
}

void	render_frame(t_ray *ray, int x)
{
	t_img	*img;
	double	i_x;
	int		y;

	y = 0;
	img = get_game()->img;
	i_x = floor((int)(img->dir[0].w_s * ray->wall.contact));
	while (y < WIN_H)
	{
		if (y < ray->wall.s_pos)
		{
			mlx_image_put(img->bgframe, x, y, img->hex[1]);
		}
		else if (y > ray->wall.e_pos - 1)
		{
			mlx_image_put(img->bgframe, x, y, img->hex[0]);
		}
		else
		{
			draw_tex(i_x, ray, (t_size){x, y}, img->dir[ray->wall.dir]);
		}
		y++;
	}
}
