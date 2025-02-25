/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 00:24:35 by ytop              #+#    #+#             */
/*   Updated: 2025/02/25 18:10:50 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

#include <math.h>

static int	draw_tex(t_objs obj, t_size pos, t_data *img, int filter)
{
	double	img_x;
	double	img_y;
	int		color;

	img_x = floor((int)(img->w_s * obj.contact));
	img_y = ((pos.y - obj.s_pos) * img->h_s) / (obj.height * 2);
	if (img_y > img->h_s - 1)
		img_y = img->h_s - 1;
	color = pixel_color(*img, img_x, img_y);
	if (color != filter)
	{
		mlx_image_put(get_game()->img->bgframe, pos.x, pos.y, color);
		return (TRUE);
	}
	return (FALSE);
}

static void	render_skybox(t_data bg, int x, int y)
{
	t_game	*game;
	double	angle;
	double	offst;
	t_size	img;

	game = get_game();
	angle = rad_to_deg(game->player.theta);
	offst = bg.w_s * ((angle / 90.0) + (x / (double)WIN_W));
	img.x = fmod(offst, bg.w_s);
	img.y = fmod(y    , bg.h_s);
	mlx_image_put(game->img->bgframe, x, y, pixel_color(bg, img.x, img.y));
}

static void	render_floor(t_data fl, int x, int y, double angle)
{
	t_game	*game;
	t_vect	direction;
	t_vect	texture;
	t_vect	tile;
	double	distance;

	game = get_game();
	direction.x = cos(angle);
	direction.y = sin(angle);
	distance = WIN_H / (2.0 * y - WIN_H);
	distance = distance / cos(game->player.theta - angle);
	tile.x = distance * direction.x + game->player.plane.x;
	tile.y = distance * direction.y + game->player.plane.y;
	texture.x = (int)(floor(tile.x * fl.w_s)) % fl.w_s;
	texture.y = (int)(floor(tile.y * fl.h_s)) % fl.h_s;
	mlx_image_put(game->img->bgframe, x, y, pixel_color(fl, texture.x, texture.y));
}

static int	render_object(int x, int y)
{
	t_game			*game = get_game();
	t_size			cross;
	unsigned int	color;

	color = pixel_color(*game->player.slot->curr->frame, x, y);
	if (image_filter(0, color, 'g', 200) || image_filter(1, color, 'g', 200)
		|| image_filter(2, color, 'g', 200) || image_filter(3, color, 'g', 200))
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
			mlx_image_put(game->img->bgframe, x, y, 0xFFFFFF);
			return (TRUE);
		}
	}
	return (FALSE);
}

void	render_frame(t_ray *ray, int x, double angle)
{
	t_game	*game;
	t_door	*door;
	t_objs	wall;
	int		y;

	y = 0;
	game = get_game();
	door = &game->door[game->index];
	if (ray->door.coll)
		wall = ray->door;
	else
		wall = ray->wall;
	while (y < WIN_H)
	{
		if (render_object(x, y) == FALSE)
		{
			if (y < wall.s_pos)
				render_skybox(*game->img->skybox, x, y);
			else if (y > wall.e_pos)
				render_floor(game->img->ground, x, y, deg_to_rad(angle));
			else
			{
				if (draw_tex(wall, (t_size){x, y}, door->anim.frame, door->filter) == FALSE)
				{
					ray->door.coll = FALSE;
					wall = ray->wall;
				}
				if (ray->door.coll == FALSE)
					draw_tex(wall, (t_size){x, y}, &game->img->dir[ray->wall.direct], -1);
			}
		}
		y++;
	}
	if (ray->door.coll)
		ray->door.coll = FALSE;
}
