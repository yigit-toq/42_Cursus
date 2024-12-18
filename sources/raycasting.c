/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:13:20 by ytop              #+#    #+#             */
/*   Updated: 2024/12/18 15:47:38 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static void	draw_texture(t_data img, int index, double height, double position)
// {
// 	double		inc;
// 	double		y;

// 	inc = height / img.h_s;
// 	y = WIN_H / 2 - height / 2;
// 	while (y < WIN_H / 2 + height / 2)
// 	{
// 		mlx_image_put(img, index, y, get_pixel_color(img, position, y));
// 		y += inc;
// 	}
// }

static void	render_frame(t_ray *ray, int index)
{
	t_game	*game;
	t_size	s_pos;
	t_size	e_pos;

	game = get_game();
	s_pos.x = index;
	e_pos.x = index;
	s_pos.y = 0;
	e_pos.y = (WIN_H / 2) - ray->wall.height;
	
	draw_hit(game->img->frame, s_pos, e_pos, game->img->hex_color[1]);

	s_pos.y = (WIN_H / 2) + ray->wall.height;
	e_pos.y = (WIN_H);
	
	draw_hit(game->img->frame, s_pos, e_pos, game->img->hex_color[0]);
	
	s_pos.y = (WIN_H / 2) - ray->wall.height;
	e_pos.y = (WIN_H / 2) + ray->wall.height;

	// draw_texture(game->img->dir_symbl[0], index, ray->wall.height, ray->wall.tex_x);

	draw_hit(game->img->frame, s_pos, e_pos, 0x007b13);
}

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
	ray->dist = (ray->dist * cos(deg_to_rad(angle) - game->player.theta)) / W_INC;

	ray->wall.height = WIN_H / ray->dist;

	// ray->wall.height = floor((WIN_H / 2) / ray->dist);

	// ray->wall.tex_x = floor((int)(game->img->dir_symbl[0].w_s * (ray->pos.x + ray->pos.y)) % game->img->dir_symbl[0].w_s);

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
		render_frame(&rays[index], index);
		angle += FOV / WIN_W;
		index++;
	}
	return (SUCCESS);
}
