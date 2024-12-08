/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:34:37 by ytop              #+#    #+#             */
/*   Updated: 2024/12/05 16:54:16 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_hit(t_game *game, t_size start, t_size curr, int color)
{
	t_size	step;
	t_size	dir;
	int		err;
	int		e2;

	dir.x = abs(curr.x - start.x);
	dir.y = abs(curr.y - start.y);
	if (start.x < curr.x)
		step.x = +1;
	else
		step.x = -1;
	if (start.y < curr.y)
		step.y = +1;
	else
		step.y = -1;
	err = dir.x - dir.y;
	while (start.x != curr.x || start.y != curr.y)
	{
		mlx_pixel_put(game->mlx, game->win, start.x, start.y, color);
		e2 = 2 * err;
		if (e2 < dir.x)
		{
			err += dir.x;
			start.y += step.y;
		}
		if (e2 > -dir.y)
		{
			err -= dir.y;
			start.x += step.x;
		}
	}
}

void	draw_rays_in_pov(t_coord pos, double theta)
{
	t_game	*game;
	double	angle;
	double	limit;
	t_coord	ray;
	t_coord	dir;
	t_size	map;

	game = get_game();
	angle = theta * (180 / PI) - (FOV / 2);
	limit = theta * (180 / PI) + (FOV / 2);
	while (angle <= limit)
	{
		ray.x = pos.x;
		ray.y = pos.y;
		double ray_angle = fmod(angle, 360);
		if (ray_angle < 0)
			ray_angle += 360.0;
		dir.x = cos(ray_angle * (PI / 180));
		dir.y = sin(ray_angle * (PI / 180));
		while (TRUE)
		{
			ray.x += dir.x;
			ray.y += dir.y;
			map.x = (int)(ray.x / game->map->scale.x);
            map.y = (int)(ray.y / game->map->scale.y);
			if (game->map->map[map.y][map.x] == WALL)
			{
				draw_hit(game, (t_size){pos.x, pos.y}, (t_size){ray.x, ray.y}, H_G);
				break ;
			}
		}
		angle += 1;
	}
}

void	draw_player(void)
{
	t_game	*game;

	game = get_game();
	draw_circle(game->player.plane, game->map->scale, H_R);

	draw_rays_in_pov(game->player.plane, game->player.theta);
}

void	minimap(void)
{
	t_game	*game;
	t_coord	coord;

	game = get_game();
	coord.y = game->map->pivot.y;
	while (coord.y < game->map->size.y + game->map->pivot.y)
	{
		coord.x = game->map->pivot.x;
		while (coord.x < game->map->size.x + game->map->pivot.x)
		{
			if (game->map->map[(int)coord.y][(int)coord.x] == WALL)
				draw_rectangle(coord, game->map->scale, H_W);
			else
				draw_rectangle(coord, game->map->scale, H_Y);
			coord.x++;
		}
		coord.y++;
	}
	draw_player();
}

void	minimap_loop(void)
{
	t_game	*game;

	game = get_game();
	if (game->map->is_map == FALSE)
	{
		return ;
	}
	minimap();
}
