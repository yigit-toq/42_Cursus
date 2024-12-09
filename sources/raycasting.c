/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:13:20 by ytop              #+#    #+#             */
/*   Updated: 2024/12/05 16:45:38 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	rays_in_pov(t_coord pos, double theta)
{
	t_game	*game;
	double	angle;
	double	limit;
	t_coord	dir;
	t_size	map;
	int		index;

	game = get_game();
	index = 0;
	angle = theta * (180 / PI) - (FOV / 2);
	limit = theta * (180 / PI) + (FOV / 2);
	while (angle <= limit)
	{
		game->rays[index].pos.x = pos.x;
		game->rays[index].pos.y = pos.y;
		double ray_angle = fmod(angle, 360);
		if (ray_angle < 0)
			ray_angle += 360;
		dir.x = cos(ray_angle * (PI / 180));
		dir.y = sin(ray_angle * (PI / 180));
		while (TRUE)
		{
			game->rays[index].pos.x += dir.x;
			game->rays[index].pos.y += dir.y;
			map.x = (int)(game->rays[index].pos.x / game->map->scale.x);
            map.y = (int)(game->rays[index].pos.y / game->map->scale.y);
			if (game->map->map[map.y][map.x] == WALL)
			{
				break ;
			}
		}
		angle += HIT;
		index++;
	}
	ft_memset(game->rays, 0, sizeof(t_ray) * (FOV / HIT));
}

int	raycast(void)
{
	t_game	*game;

	game = get_game();
	game->player.plane.x = grid_to_center(game->player.position.x, game->map->scale.x, game->map->pivot.x);
	game->player.plane.y = grid_to_center(game->player.position.y, game->map->scale.y, game->map->pivot.y);

	rays_in_pov(game->player.plane, game->player.theta);
	return (SUCCESS);
}
