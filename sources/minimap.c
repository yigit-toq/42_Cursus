/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:34:37 by ytop              #+#    #+#             */
/*   Updated: 2024/12/05 15:28:30 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//HEIGHT / game->map->height;
//WIDTH / game->map->width;

void draw_asc(t_game *game, int x0, int y0, int x1, int y1, int color) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (x0 != x1 || y0 != y1) {
        mlx_pixel_put(game->mlx, game->win, x0, y0, color);
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
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

			int map_x = (int)(ray.x / TILE / 4);
            int map_y = (int)(ray.y / TILE / 4);
			if (game->map->map[map_x][map_y] == WALL)
			{
				draw_asc(game, pos.x, pos.y, ray.x, ray.y, H_R);
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
	draw_circle(game->player.plane, game->map->size, H_R);

	draw_rays_in_pov(game->player.plane, game->player.theta);
}

void	minimap(void)
{
	t_game	*game;
	t_coord	coord;

	ft_bzero(&coord, sizeof(t_coord));
	game = get_game();
	game->map->size.x = TILE * 2;
	game->map->size.y = TILE * 2;
	game->player.plane.x = (game->player.position.x * game->map->size.x) + (game->map->size.x / 2);
	game->player.plane.y = (game->player.position.y * game->map->size.y) + (game->map->size.y / 2);
	while (coord.y < game->map->height)
	{
		coord.x = 0;
		while (coord.x < game->map->width)
		{
			if (game->map->map[(int)coord.y][(int)coord.x] == WALL)
				draw_rectangle(coord, game->map->size, H_W);
			else
				draw_rectangle(coord, game->map->size, H_B);
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
