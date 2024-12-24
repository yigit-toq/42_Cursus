/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:13:20 by ytop              #+#    #+#             */
/*   Updated: 2024/12/24 16:37:10 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

// static void	fix_hit(t_size *s_pos, t_size *e_pos, int s_y, int e_y)
// {
// 	s_pos->y = s_y;
// 	e_pos->y = e_y;
// 	if (s_pos->y < 0)
// 		s_pos->y = 0;
// 	if (e_pos->y > WIN_H)
// 		e_pos->y = WIN_H;
// }

// static void	render_frame(t_ray *ray, int index)
// {
// 	t_game	*game;
// 	t_size	s_pos;
// 	t_size	e_pos;
// 	double	img_x;
//
// 	game = get_game();
// 	s_pos.x = index;
// 	e_pos.x = index;
//
// 	img_x = floor((int)(game->img->dir_symbl[0].w_s * (ray->src.x + ray->src.y)) % game->img->dir_symbl[0].w_s);
//
// 	draw_tex(index, img_x, ray->wall.height, game->img->dir_symbl[0]);
//
// 	fix_hit(&s_pos, &e_pos, (WIN_H / 2) - ray->wall.height, 0);
// 	draw_hit(game->img->bgframe, s_pos, e_pos, game->img->hex_color[1]);
//
// 	fix_hit(&s_pos, &e_pos, (WIN_H / 2) + ray->wall.height, WIN_H);
// 	draw_hit(game->img->bgframe, s_pos, e_pos, game->img->hex_color[0]);
//
// 	for (int y = 0; y < WIN_H; y++)
// 	{
// 		unsigned int color = get_pixel_color(*game->player.anim->frame, index, y);
//
// 		unsigned char blue = (color >> 0) & 255;
//
// 		int	cross_x = (WIN_W / 2) - 32;
// 		int	cross_y = (WIN_H / 2) - 32;
//
// 		if ((index > cross_x && index < cross_x + 64) && (y > cross_y && y < cross_y + 64))
// 		{
// 			unsigned int color = get_pixel_color(game->img->cross, index - cross_x, y - cross_y);
//
// 			if (color == 0)
// 				mlx_image_put(game->img->bgframe, index, y, color);
// 		}
// 		if (blue < 130)
// 		{
// 			mlx_image_put(game->img->bgframe, index, y, color);
// 		}
// 	}
// }

// static void	rays_in_povs(t_ray *ray, t_vect pos, double angle)
// {
// 	t_game	*game;
// 	t_size	map;
//
// 	game = get_game();
// 	ray->pos.x = pos.x;
// 	ray->pos.y = pos.y;
// 	ray->dir.x = cos(deg_to_rad(angle)) / SEV;
// 	ray->dir.y = sin(deg_to_rad(angle)) / SEV;
// 	while (TRUE)
// 	{
// 		ray->pos.x += ray->dir.x;
// 		ray->pos.y += ray->dir.y;
// 		map.x = floor(ray->pos.x / game->map->scale.x);
// 		map.y = floor(ray->pos.y / game->map->scale.y);
// 		if (game->map->map[map.y][map.x] == WALL)
// 			break ;
// 	}
// 	ray->dist = sqrt(pow(ray->pos.x - pos.x, 2) + pow(ray->pos.y - pos.y, 2));
//
// 	ray->dist = ray->dist * cos (deg_to_rad(angle) - game->player.theta);
//
// 	ray->wall.height = floor((WIN_H / 2) / ray->dist);
// }

static void draw_tex(int x_p, int y_p, double img_x, int start, double height, t_data img)
{
	t_game	*game;

	game = get_game();
    double tex_y = ((y_p - start) * img.h_s) / (height * 2);
    if (tex_y > img.h_s - 1)
        tex_y = img.h_s - 1;
    mlx_image_put(game->img->bgframe, x_p, y_p, get_pixel_color(img, img_x, tex_y));
}

static void	init_ray(t_ray *ray, double angle)
{
	t_game	*game;

	game = get_game();
	ray->src.x = game->player.plane.x;
	ray->src.y = game->player.plane.y;
	ray->dir.x = cos(deg_to_rad(angle));
	ray->dir.y = sin(deg_to_rad(angle));
	ray->delta.x = fabs(1 / ray->dir.x);
	ray->delta.y = fabs(1 / ray->dir.y);
	ray->plane.x = floor(ray->src.x / game->map->scale.x);
	ray->plane.y = floor(ray->src.y / game->map->scale.y);
}

static void	calculate_ray_dir(t_ray *ray)
{
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->side.x = (ray->src.x - ray->plane.x) * ray->delta.x;
	}
	else
	{
		ray->step.x = +1;
		ray->side.x = (ray->plane.x + 1.0 - ray->src.x) * ray->delta.x;
	}
	if (ray->dir.y > 0)
	{
		ray->step.y = +1;
		ray->side.y = (ray->plane.y + 1.0 - ray->src.y) * ray->delta.y;
	}
	else
	{
		ray->step.y = -1;
		ray->side.y = (ray->src.y - ray->plane.y) * ray->delta.y;
	}
}

static void calculate_ray_hit(t_ray *ray, double angle)
{
	t_game	*game;
	int		side;

	game = get_game();
	while (TRUE)
	{
		if (ray->side.x < ray->side.y)
		{
			ray->plane.x += ray->step.x;
			ray->side.x += ray->delta.x;
			side = 0;
		}
		else
		{
			ray->plane.y += ray->step.y;
			ray->side.y += ray->delta.y;
			side = 1;
		}
		if (game->map->map[(int)ray->plane.y][(int)ray->plane.x] == WALL)
			break;
	}
	if (side == 0)
	{
		ray->dist = (ray->plane.x - ray->src.x + (1 - ray->step.x) / 2) / ray->dir.x;
		if (ray->dir.x > 0)
			ray->wall.dir = 3;
		else
			ray->wall.dir = 2;
		ray->wall.contact = ray->src.y + ray->dist * ray->dir.y;
	}
	else
	{
		ray->dist = (ray->plane.y - ray->src.y + (1 - ray->step.y) / 2) / ray->dir.y;
		if (ray->dir.y > 0)
			ray->wall.dir = 1;
		else
			ray->wall.dir = 0;
		ray->wall.contact = ray->src.x + ray->dist * ray->dir.x;
	}
	ray->dist = cos(deg_to_rad(angle) - game->player.theta) * ray->dist;

	ray->wall.contact -= floor(ray->wall.contact);
}

static void	calculate_wal_hgt(t_ray *ray)
{
	ray->wall.height = floor((WIN_H / 2) / ray->dist);
	if (ray->wall.height > WIN_H / 2)
		ray->wall.height = WIN_H / 2;
	ray->wall.s_pos = (WIN_H / 2) - ray->wall.height;
	ray->wall.e_pos = (WIN_H / 2) + ray->wall.height;
}

static int	render_object(int x, int y)
{
	t_game			*game = get_game();
	unsigned int	color;

	color = get_pixel_color(*game->player.anim->frame, x, y);
	if (((color >> 0) & 255) < 130)
	{
		mlx_image_put(game->img->bgframe, x, y, color);
		return (TRUE);
	}
	int	cross_x = (WIN_W / 2) - 32;
	int	cross_y = (WIN_H / 2) - 32;
	if ((x > cross_x && x < cross_x + 64) && (y > cross_y && y < cross_y + 64))
	{
		color = get_pixel_color(game->img->cross, x - cross_x, y - cross_y);
		if (color == 0x000000)
		{
			mlx_image_put(game->img->bgframe, x, y, color);
			return (TRUE);
		}
	}
	return (FALSE);
}

static void	render_frame(t_ray *ray, int x)
{
	t_game	*game;
	int		y;

	y = 0;
	game = get_game();
	double img_x = floor((int)(game->img->dir_symbl[0].w_s * ray->wall.contact));
	while (y < WIN_H)
	{
		if (!render_object(x, y))
		{
			if (y < ray->wall.s_pos)
			{
				mlx_image_put(game->img->bgframe, x, y, game->img->hex_color[1]);
			}
			else
			{
				if (y >= ray->wall.e_pos)
				{
					mlx_image_put(game->img->bgframe, x, y, game->img->hex_color[0]);
				}
				else
				{
					draw_tex(x, y, img_x, ray->wall.s_pos, ray->wall.height, game->img->dir_symbl[ray->wall.dir]);
				}
			}
		}
		y++;
	}
}

int	raycast(void)
{
	t_game	*game;
	t_ray	*rays;
	int		index;
	double	angle;

	game = get_game();
	rays = game->rays;
	game->player.plane.x = grid_to_center(game->player.position.x, game->map->scale.x);
	game->player.plane.y = grid_to_center(game->player.position.y, game->map->scale.y);
	index = 0;
	angle = rad_to_deg(game->player.theta) - (FOV / 2);
	while (index < WIN_W)
	{
		init_ray(&rays[index], angle);
		calculate_ray_dir(&rays[index]);
		calculate_ray_hit(&rays[index], angle);
		calculate_wal_hgt(&rays[index]);
		render_frame(&rays[index], index);
		angle += FOV / WIN_W;
		index++;
	}
	return (SUCCESS);
}
// ft_memset(rays, 0, WIN_W * sizeof(t_ray));
