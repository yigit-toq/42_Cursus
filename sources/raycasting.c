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

// static void	rays_in_pov(t_game *game, t_vect pos, double theta)
// {
// 	int		index;
// 	double	angle;
// 	double	limit;
// 	double	ray_a;
// 	t_size	map;

// 	index = 0;
// 	angle = rad_to_deg(theta) - (FOV / 2);
// 	limit = rad_to_deg(theta) + (FOV / 2);
// 	ft_memset(game->rays, 0, sizeof(t_ray) * (FOV / INC));
// 	while (angle < limit)
// 	{
// 		game->rays[index].pos.x = pos.x;
// 		game->rays[index].pos.y = pos.y;
// 		ray_a = fmod(angle, 360);
// 		if (ray_a < 0)
// 			ray_a = 360;
// 		game->rays[index].dir.x = cos(deg_to_rad(ray_a));
// 		game->rays[index].dir.y = sin(deg_to_rad(ray_a));
// 		while (TRUE)
// 		{
// 			game->rays[index].pos.x += game->rays[index].dir.x;
// 			game->rays[index].pos.y += game->rays[index].dir.y;
// 			map.x = center_to_grid(game->rays[index].pos.x, game->map->scale.x, 0);
// 			map.y = center_to_grid(game->rays[index].pos.y, game->map->scale.y, 0);
// 			if (game->map->map[map.y][map.x] == WALL)
// 				break ;
// 		}
// 		angle += INC;
// 		if (index++ == (int)(FOV / INC))
// 			break ;
// 	}
// }

static void	rays_in_pov(t_game *game, t_vect pos, double theta)
{
	t_ray	*rays;
	double	angle;
	double	limit;
	int		index;
	t_size	map;

	rays = game->rays;
	(void)limit;
	index = 0;
	angle = rad_to_deg(theta) - (FOV / 2);
	limit = rad_to_deg(theta) + (FOV / 2);
	ft_memset(rays, 0, sizeof(t_ray) * WIN_W);
	while (index < WIN_W)
	{
		rays[index].pos.x = pos.x;
		rays[index].pos.y = pos.y;
		rays[index].dir.x = cos(deg_to_rad(angle)) / SEV;
		rays[index].dir.y = sin(deg_to_rad(angle)) / SEV;
		while (TRUE)
		{
			rays[index].pos.x += rays[index].dir.x;
			rays[index].pos.y += rays[index].dir.y;
			map.x = center_to_grid(rays[index].pos.x, game->map->scale.x, 0);
			map.y = center_to_grid(rays[index].pos.y, game->map->scale.y, 0);
			// map.x = rays[index].pos.x;
			// map.y = rays[index].pos.y;
			if (game->map->map[map.y][map.x] == WALL)
				break ;
		}
		rays[index].dist = sqrt(pow(rays[index].pos.x - pos.x, 2) + pow(rays[index].pos.y - pos.y, 2));
		rays[index].wall.height = WIN_H / rays[index].dist;
		rays[index].wall.s_pos = (WIN_H / 2) - (rays[index].wall.height / 2);
		rays[index].wall.e_pos = (WIN_H / 2) + (rays[index].wall.height / 2);
		angle += INC;
		index++;
	}
}

int	raycast(void)
{
	t_game	*game;

	game = get_game();
	game->player.plane.x = grid_to_center(game->player.position.x, game->map->scale.x, 0);
	game->player.plane.y = grid_to_center(game->player.position.y, game->map->scale.y, 0);
	rays_in_pov(game, game->player.plane, game->player.theta);
	return (SUCCESS);
}
