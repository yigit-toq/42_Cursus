/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:13:20 by ytop              #+#    #+#             */
/*   Updated: 2025/02/25 18:01:34 by ytop             ###   ########.fr       */
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

static void	calculate_ray_dis(t_ray *ray, double angle, t_objs *obj)
{
	t_game	*game;

	game = get_game();
	if (ray->axis == 0)
	{
		obj->dist = (ray->plane.x - ray->src.x
				+ (1 - ray->step.x) / 2) / ray->dir.x;
		if (ray->dir.x > 0)
			obj->direct = 3;
		else
			obj->direct = 2;
		obj->contact = ray->src.y + obj->dist * ray->dir.y;
	}
	else
	{
		obj->dist = (ray->plane.y - ray->src.y
				+ (1 - ray->step.y) / 2) / ray->dir.y;
		if (ray->dir.y > 0)
			obj->direct = 1;
		else
			obj->direct = 0;
		obj->contact = ray->src.x + obj->dist * ray->dir.x;
	}
	obj->dist = cos(deg_to_rad(angle) - game->player.theta) * obj->dist;
	obj->contact -= floor(obj->contact);
}

static void	calculate_wal_hgt(t_ray *ray, double angle, t_objs *obj)
{
	(void)ray;
	(void)angle;
	obj->height = floor((WIN_H / 2) / obj->dist);
	obj->s_pos = (WIN_H / 2) - obj->height;
	obj->e_pos = (WIN_H / 2) + obj->height;
}

static void	calculate_door(t_ray *ray, int index, double angle)
{
	t_game	*game;
	int		i;

	i = 0;
	game = get_game();
	while (i < game->count.door)
	{
		if (ray->plane.x == game->door[i].coor.x && ray->plane.y == game->door[i].coor.y)
		{
			game->index = i;
			break;
		}
		i++;
	}
	if (index == WIN_W / 2)
	{
		if (ray->door.dist <= 2)
			game->curr = &game->door[game->index];
		else
			game->curr = NULL;
	}
	calculate_ray_dis(ray, angle, &ray->door);
	calculate_wal_hgt(ray, angle, &ray->door);
	ray->door.coll = TRUE;
}

static void	calculate_ray_hit(t_ray *ray, int index, double angle)
{
	t_game	*game;
	int		cell;

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
		cell = game->map->map[(int)ray->plane.y][(int)ray->plane.x];
		if (cell == DOOR)
			calculate_door(ray, index, angle);
		if (cell == WALL)
			break ;
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
	game->player.plane.x = grid_to_ct(game->player.pos.x, game->map->scale.x);
	game->player.plane.y = grid_to_ct(game->player.pos.y, game->map->scale.y);
	index = 0;
	angle = rad_to_deg(game->player.theta) - (FOV / 2);
	while (index < WIN_W)
	{
		init_ray(&rays[index], angle);
		calculate_ray_dir(&rays[index]);
		calculate_ray_hit(&rays[index], index, angle);
		calculate_ray_dis(&rays[index], angle, &rays[index].wall);
		calculate_wal_hgt(&rays[index], angle, &rays[index].wall);
		render_frame(&rays[index], index, angle);
		angle += FOV / WIN_W;
		index++;
	}
	return (SUCCESS);
}
