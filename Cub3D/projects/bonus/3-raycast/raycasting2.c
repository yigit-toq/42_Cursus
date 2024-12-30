/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 00:24:35 by ytop              #+#    #+#             */
/*   Updated: 2024/12/30 15:20:42 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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

static int	render_object(int x, int y)
{
	t_game	*game = get_game();
	t_size	cross;
	int		color;

	color = pixel_color(*game->player.slot->curr->frame, x, y);
	if (image_filter(0, color, 'g', 200) || image_filter(1, color, 'b', 130)
		|| image_filter(2, color, 'g', 160)
		|| image_filter(3, color, 'g', 160))
	{
		mlx_image_put(game->img->bgframe, x, y, color);
		return (TRUE);
	}
	cross.x = (WIN_W / 2) - 32;
	cross.y = (WIN_H / 2) - 32;
	if ((x > cross.x && x < cross.x + 64) && (y > cross.y && y < cross.y + 64))
	{
		color = pixel_color(game->img->crossh, x - cross.x, y - cross.y);
		if (color == 0x000000)
		{
			mlx_image_put(game->img->bgframe, x, y, color);
			return (TRUE);
		}
	}
	return (FALSE);
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
		if (!render_object(x, y))
		{
			if (y < ray->wall.s_pos)
			{
				mlx_image_put(img->bgframe, x, y, img->hex[1]);
			}
			else if (y > ray->wall.e_pos)
			{
				mlx_image_put(img->bgframe, x, y, img->hex[0]);
			}
			else
			{
				draw_tex(i_x, ray, (t_size){x, y}, img->dir[ray->wall.dir]);
			}
		}
		y++;
	}
}
