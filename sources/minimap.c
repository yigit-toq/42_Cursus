/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:34:37 by ytop              #+#    #+#             */
/*   Updated: 2024/12/10 17:53:31 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_hit(t_data image, t_size start, t_size curr, int color)
{
	t_game	*game;
	t_size	step;
	t_size	dir;
	int		er1;
	int		er2;

	game = get_game();
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
	er1 = dir.x - dir.y;
	while (start.x != curr.x || start.y != curr.y)
	{
		if (image.addr)
			put_pixel_to_image(image, start.x, start.y, color);
		else
			mlx_pixel_put(game->mlx, game->win, start.x, start.y, color);
		er2 = 2 * er1;
		if (er2 < +dir.x)
		{
			er1 += dir.x;
			start.y += step.y;
		}
		if (er2 > -dir.y)
		{
			er1 -= dir.y;
			start.x += step.x;
		}
	}
}

static void	rays_in_pov(t_coord pos, double theta)
{
	t_game	*game;
	double	angle;
	double	limit;
	t_size	map;
	int		index;

	game = get_game();
	ft_memset(game->rays, 0, sizeof(t_ray) * (FOV / HIT));
	index = 0;
	angle = theta * (180 / PI) - (FOV / 2);
	limit = theta * (180 / PI) + (FOV / 2);
	while (angle <= limit)
	{
		game->rays[index].pos.x = pos.x;
		game->rays[index].pos.y = pos.y;
		double ray_angle = fmod(angle, 360);
		if (ray_angle < 0)
			ray_angle = 360;
		game->rays[index].dir.x = cos(ray_angle * (PI / 180));
		game->rays[index].dir.y = sin(ray_angle * (PI / 180));
		while (TRUE)
		{
			game->rays[index].pos.x += game->rays[index].dir.x;
			game->rays[index].pos.y += game->rays[index].dir.y;
			// map.x = center_to_grid(game->rays[index].pos.x, game->map->scale.x, game->map->pivot.x);
            // map.y = center_to_grid(game->rays[index].pos.y, game->map->scale.y, game->map->pivot.y);
			map.x = center_to_grid(game->rays[index].pos.x, game->map->scale.x, 0);
            map.y = center_to_grid(game->rays[index].pos.y, game->map->scale.y, 0);
			if (game->map->map[map.y][map.x] == WALL)
			{
				draw_hit(game->img->minimap, typecast_size(game->player.plane), typecast_size(game->rays[index].pos), H_G);
				break ;
			}
		}
		angle += HIT;
		index++;
	}
}

void	draw_player(void)
{
	t_game	*game;

	game = get_game();
	draw_circle(game->img->minimap, game->player.plane, game->map->scale, H_R);
	
	rays_in_pov(game->player.plane, game->player.theta);
}

void	minimap(void)
{
	t_game	*game;
	t_coord	coord;
	t_coord	limit;
	int		value;

	game = get_game();
	// limit.x = game->map->size.x + game->map->pivot.x;
	// limit.y = game->map->size.y + game->map->pivot.y;
	limit.x = game->map->size.x;
	limit.y = game->map->size.y;
	coord.y = 0;
	while (coord.y < limit.y)
	{
		coord.x = 0;
		while (coord.x <= limit.x)
		{
			value = game->map->map
					[(int)coord.y]
					[(int)coord.x];
					// [(int)(coord.y - game->map->pivot.y)]
					// [(int)(coord.x - game->map->pivot.x)]
			if (value == WALL)
				draw_rectangle(game->img->minimap, coord, game->map->scale, H_W);
			else
				draw_rectangle(game->img->minimap ,coord, game->map->scale, H_Y);
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
