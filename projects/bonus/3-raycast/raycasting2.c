/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 00:24:35 by ytop              #+#    #+#             */
/*   Updated: 2025/03/07 17:51:25 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

#include <math.h>

void	calculate_ray_dis(t_ray *ray, double angle, t_objs *obj)
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
	obj->contact -= floor(obj->contact);
	obj->dist = cos(deg_to_rad(angle) - game->player.theta) * obj->dist;
}

void	calculate_wal_hgt(t_ray *ray, double angle, t_objs *obj)
{
	(void)ray;
	(void)angle;
	obj->height = floor((WIN_H / 2) / obj->dist);
	obj->s_pos = (WIN_H / 2) - obj->height;
	obj->e_pos = (WIN_H / 2) + obj->height;
}

static void	middle_ray(t_ray *ray, int index, void *type)
{
	t_game	*game;

	game = get_game();
	if (index == WIN_W / 2)
	{
		if (game->grp->door == type)
		{
			if (ray->door.dist <= 2)
				game->grp->curr = &game->grp->door[game->grp->d_i];
			else
				game->grp->curr = NULL;
		}
	}
}

void	calculate_door(t_ray *ray, int index, double angle)
{
	t_game	*game;
	t_door	*door;
	int		i;

	i = 0;
	game = get_game();
	door = game->grp->door;
	while (i < game->count.door)
	{
		if (ray->plane.x == door[i].coor.x && ray->plane.y == door[i].coor.y)
		{
			game->grp->d_i = i;
			break ;
		}
		i++;
	}
	middle_ray(ray, index, door);
	calculate_ray_dis(ray, angle, &ray->door);
	calculate_wal_hgt(ray, angle, &ray->door);
	ray->door.coll = TRUE;
}
