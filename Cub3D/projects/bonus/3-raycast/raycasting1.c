/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:13:20 by ytop              #+#    #+#             */
/*   Updated: 2024/12/27 14:01:43 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

#include <math.h>

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

static void	calculate_ray_dis(t_ray *ray, double angle)
{
	t_game	*game;

	game = get_game();
	if (ray->axis == 0)
	{
		ray->dist = (ray->plane.x - ray->src.x
				+ (1 - ray->step.x) / 2) / ray->dir.x;
		if (ray->dir.x > 0)
			ray->wall.dir = 3;
		else
			ray->wall.dir = 2;
		ray->wall.contact = ray->src.y + ray->dist * ray->dir.y;
	}
	else
	{
		ray->dist = (ray->plane.y - ray->src.y
				+ (1 - ray->step.y) / 2) / ray->dir.y;
		if (ray->dir.y > 0)
			ray->wall.dir = 1;
		else
			ray->wall.dir = 0;
		ray->wall.contact = ray->src.x + ray->dist * ray->dir.x;
	}
	ray->dist = cos(deg_to_rad(angle) - game->player.theta) * ray->dist;
	ray->wall.contact -= floor(ray->wall.contact);
}

static void	calculate_ray_hit(t_ray *ray)
{
	t_game	*game;

	game = get_game();
	while (TRUE)
	{
		if (ray->side.x < ray->side.y)
		{
			ray->plane.x += ray->step.x;
			ray->side.x += ray->delta.x;
			ray->axis = 0;
		}
		else
		{
			ray->plane.y += ray->step.y;
			ray->side.y += ray->delta.y;
			ray->axis = 1;
		}
		if (game->map->map[(int)ray->plane.y][(int)ray->plane.x] == WALL)
			break ;
	}
}

static void	calculate_wal_hgt(t_ray *ray)
{
	ray->wall.height = floor((WIN_H / 2) / ray->dist);
	if (ray->wall.height > WIN_H / 2)
		ray->wall.height = WIN_H / 2;
	ray->wall.s_pos = (WIN_H / 2) - ray->wall.height;
	ray->wall.e_pos = (WIN_H / 2) + ray->wall.height;
}

int	raycast(void)
{
	t_game	*game;
	t_ray	*rays;
	int		index;
	double	angle;

	game = get_game();
	rays = game->rays;
	game->player.plane.x = grid_to_ct(game->player.pos.x, game->map->scale.x);
	game->player.plane.y = grid_to_ct(game->player.pos.y, game->map->scale.y);
	index = 0;
	angle = rad_to_deg(game->player.theta) - (FOV / 2);
	while (index < WIN_W)
	{
		init_ray(&rays[index], angle);
		calculate_ray_dir(&rays[index]);
		calculate_ray_hit(&rays[index]);
		calculate_ray_dis(&rays[index], angle);
		calculate_wal_hgt(&rays[index]);
		render_frame(&rays[index], index);
		angle += FOV / WIN_W;
		index++;
	}
	return (SUCCESS);
}
