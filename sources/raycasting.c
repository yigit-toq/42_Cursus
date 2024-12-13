/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:13:20 by ytop              #+#    #+#             */
/*   Updated: 2024/12/13 19:03:43 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	rays_in_pov(t_game *game, t_coord pos, double theta)
{
	int		index;
	double	angle;
	double	limit;
	double	ray_a;
	t_size	map;

	index = 0;
	angle = theta * (180 / PI) - (FOV / 2);
	limit = theta * (180 / PI) + (FOV / 2);
	ft_memset(game->rays, 0, sizeof(t_ray) * (FOV / INCREMENT));
	while (angle < limit)
	{
		game->rays[index].pos.x = pos.x;
		game->rays[index].pos.y = pos.y;
		ray_a = fmod(angle, 360);
		if (ray_a < 0)
			ray_a = 360;
		game->rays[index].dir.x = cos(ray_a * (PI / 180));
		game->rays[index].dir.y = sin(ray_a * (PI / 180));
		while (TRUE)
		{
			game->rays[index].pos.x += game->rays[index].dir.x;
			game->rays[index].pos.y += game->rays[index].dir.y;
			map.x = center_to_grid(game->rays[index].pos.x, game->map->scale.x, 0);
			map.y = center_to_grid(game->rays[index].pos.y, game->map->scale.y, 0);
			if (game->map->map[map.y][map.x] == WALL)
				break ;
		}
		angle += INCREMENT;
		if (index++ == (int)(FOV / INCREMENT))
			break ;
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
