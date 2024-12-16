/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:13:20 by ytop              #+#    #+#             */
/*   Updated: 2024/12/16 17:50:38 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	rays_in_pov(t_ray *ray, t_vect pos, double angle)
{
	t_game	*game;
	t_size	map;

	game = get_game();
	ray->pos.x = pos.x;
	ray->pos.y = pos.y;
	ray->dir.x = cos(deg_to_rad(angle)) / SEV;
	ray->dir.y = sin(deg_to_rad(angle)) / SEV;
	while (TRUE)
	{
		ray->pos.x += ray->dir.x;
		ray->pos.y += ray->dir.y;
		map.x = center_to_grid(ray->pos.x, game->map->scale.x, 0);
		map.y = center_to_grid(ray->pos.y, game->map->scale.y, 0);
		// map.x = ray->pos.x;
		// map.y = ray->pos.y;
		if (game->map->map[map.y][map.x] == WALL)
			break ;
	}
	ray->dist = sqrt(pow(ray->pos.x - pos.x, 2) + pow(ray->pos.y - pos.y, 2));
	ray->wall.height = WIN_H / ray->dist;
	ray->wall.s_pos = (WIN_H / 2) - (ray->wall.height / 2);
	ray->wall.e_pos = (WIN_H / 2) + (ray->wall.height / 2);
}

int	raycast(void)
{
	t_game	*game;
	t_ray	*rays;
	int		index;
	double	angle;

	game = get_game();
	rays = game->rays;
	game->player.plane.x = grid_to_center(game->player.position.x, game->map->scale.x, 0);
	game->player.plane.y = grid_to_center(game->player.position.y, game->map->scale.y, 0);
	index = 0;
	angle = rad_to_deg(game->player.theta) - (FOV / 2);
	ft_memset(rays, 0, WIN_W * sizeof(t_ray));
	while (index < WIN_W)
	{
		rays_in_pov(&rays[index], game->player.plane, angle);
		draw_hit(game->img->frame, (t_size){index, 0}, (t_size){index, (WIN_H / 2) - rays[index].wall.height}, game->img->hex_color[1]);
		draw_hit(game->img->frame, (t_size){index, (WIN_H / 2) + rays[index].wall.height}, (t_size){index, WIN_H}, game->img->hex_color[0]);
		draw_hit(game->img->frame, (t_size){index, (WIN_H / 2) - rays[index].wall.height}, (t_size){index, (WIN_H / 2) + rays[index].wall.height}, H_B);
		angle += INC;
		index++;
	}
	return (SUCCESS);
}
