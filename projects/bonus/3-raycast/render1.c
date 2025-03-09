/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:45:50 by ytop              #+#    #+#             */
/*   Updated: 2025/03/09 15:45:50 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

#include <math.h>

static int	draw_tex(t_objs obj, t_size pos, t_data *img, int filter)
{
	double	img_x;
	double	img_y;
	int		color;

	img_x = floor(img->w_s * obj.contact);
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

static void	render_skybx(t_data bg, int x, int ray_y)
{
	t_game	*game;
	double	angle;
	double	offst;
	t_size	img;

	game = get_game();
	angle = rad_to_deg(game->player.theta);
	offst = bg.w_s * ((angle / 90.0) + (x / (double)WIN_W));
	img.x = fmod(offst, bg.w_s);
	img.y = fmod(ray_y, bg.h_s);
	mlx_image_put(game->img->bgframe, x, ray_y, pixel_color(bg, img.x, img.y));
}

static void	render_floor(t_data fl, int x, int y, double angle)
{
	t_game	*game;
	t_vect	tile;
	t_vect	img;
	t_vect	dir;
	double	dist;

	game = get_game();
	dir.x = cos(angle);
	dir.y = sin(angle);
	dist = WIN_H / (2.0 * y - WIN_H);
	dist = dist / cos(game->player.theta - angle);
	tile.x = dist * dir.x + game->player.plane.x;
	tile.y = dist * dir.y + game->player.plane.y;
	img.x = (int)(floor(tile.x * fl.w_s)) % fl.w_s;
	img.y = (int)(floor(tile.y * fl.h_s)) % fl.h_s;
	mlx_image_put(game->img->bgframe, x, y, pixel_color(fl, img.x, img.y));
}

static void	render_walls(t_ray *ray, t_objs *obj, int x, int y)
{
	t_game	*game;
	t_data	*wall;
	t_door	*door;

	game = get_game();
	door = &game->grp->door[game->grp->d_i];
	if (game->count.door && draw_tex(*obj, (t_size){x, y},
		door->anim.frame, door->filter) == FALSE)
	{
		*obj = ray->wall;
		ray->door.coll = FALSE;
	}
	if (ray->door.coll == FALSE)
	{
		wall = &game->img->direct[ray->wall.direct];
		draw_tex(*obj, (t_size){x, y}, wall, -1);
	}
}

void	render_frame(t_ray *ray, int x, double angle)
{
	t_game	*game;
	t_objs	obj;
	int		y;

	y = 0;
	game = get_game();
	if (ray->door.coll)
		obj = ray->door;
	else
		obj = ray->wall;
	while (y < WIN_H)
	{
		if (render_object(x, y) == FALSE)
		{
			if (y < obj.s_pos)
				render_skybx(game->img->skybox, x, y);
			else if (y > obj.e_pos)
				render_floor(game->img->ground, x, y, deg_to_rad(angle));
			else
				render_walls(ray, &obj, x, y);
		}
		y++;
	}
	if (ray->door.coll)
		ray->door.coll = FALSE;
}
