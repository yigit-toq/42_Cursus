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

void	draw_point(t_game *game, t_coord pos, t_coord angle, int color)
{
	t_size	dir;

	dir.x = abs((int)angle.x - (int)pos.x);
	dir.y = abs((int)angle.y - (int)pos.y);
	int sx = (pos.x < angle.x) ? 1 : -1;
	int sy = (pos.y < angle.y) ? 1 : -1;
	int err = dir.x - dir.y;

	while (pos.x != angle.x || pos.y != angle.y)
	{
        mlx_pixel_put(game->mlx, game->win, pos.x, pos.y, color);
        int e2 = 2 * err;
        if (e2 > -dir.y)
		{
            err -= dir.y;
            pos.x += sx;
        }
        if (e2 < dir.x)
		{
            err += dir.x;
            pos.y += sy;
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

	(void)dir;
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

		// draw_ray(pos, ray_angle * (PI / 180) , H_R);

		while (TRUE)
		{
			ray.x += dir.x;
			ray.y += dir.y;

			int map_x = (int)(ray.x / game->map->scale.x);
            int map_y = (int)(ray.y / game->map->scale.y);
			if (game->map->map[map_x][map_y] == WALL)
			{
				draw_point(game, pos, ray, H_R);
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
		while (coord.x < game->map->size.x)
		{
			if (game->map->map[(int)coord.y][(int)coord.x] == WALL)
				draw_rectangle(coord, game->map->scale, H_W);
			else
				draw_rectangle(coord, game->map->scale, H_B);
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
