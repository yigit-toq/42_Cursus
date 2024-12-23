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

static void	draw_tex(double x_p, double x_c, double height, t_data img)
{
	double		inc;
	double		y_p;
	double		y_c;

	y_c = 0;
	y_p = (WIN_H /  2) - height;
	inc = (height * 2) / img.h_s;
	while (y_c < img.h_s)
	{
		mlx_image_put(get_game()->img->bgframe, x_p, y_p, get_pixel_color(img, x_c, y_c));
		y_p += inc;
		y_c++;
	}
}

static void	render_frame(t_ray *ray, int index)
{
	t_game	*game;
	t_size	s_pos;
	t_size	e_pos;
	double	img_x;

	game = get_game();
	s_pos.x = index;
	e_pos.x = index;

	s_pos.y = 0;
	e_pos.y = (WIN_H / 2) - ray->wall.height;

	img_x = floor((int)(game->img->dir_symbl[0].w_s * (ray->src.x + ray->src.y)) % game->img->dir_symbl[0].w_s);

	draw_hit(game->img->bgframe, s_pos, e_pos, game->img->hex_color[1]);

	s_pos.y = (WIN_H / 2) + ray->wall.height;
	e_pos.y = (WIN_H);
	
	draw_hit(game->img->bgframe, s_pos, e_pos, game->img->hex_color[0]);
	
	s_pos.y = (WIN_H / 2) - ray->wall.height;
	e_pos.y = (WIN_H / 2) + ray->wall.height;

	draw_tex(index, img_x, ray->wall.height, game->img->dir_symbl[0]);
}

static void	rays_in_povs(t_ray *ray, t_vect pos, double angle)
{
	t_game	*game;
	t_size	map;

	game = get_game();
	ray->src.x = pos.x;
	ray->src.y = pos.y;
	ray->dir.x = cos(deg_to_rad(angle)) / SEV;
	ray->dir.y = sin(deg_to_rad(angle)) / SEV;
	while (TRUE)
	{
		ray->src.x += ray->dir.x;
		ray->src.y += ray->dir.y;
		map.x = center_to_grid(ray->src.x, game->map->scale.x, 0);
		map.y = center_to_grid(ray->src.y, game->map->scale.y, 0);
		if (game->map->map[map.y][map.x] == WALL)
			break ;
	}
	ray->dist = sqrt(pow(ray->src.x - pos.x, 2) + pow(ray->src.y - pos.y, 2));

	ray->dist = cos(deg_to_rad(angle) - game->player.theta) * ray->dist;

	ray->wall.height = floor((WIN_H / 2) / ray->dist);
}

int	raycast(void)
{
	t_game				*game;
	t_ray				*rays;
	int					index;
	double				angle;

	game = get_game();
	rays = game->rays;
	game->player.plane.x = grid_to_center(game->player.position.x, game->map->scale.x, 0);
	game->player.plane.y = grid_to_center(game->player.position.y, game->map->scale.y, 0);
	index = 0;
	angle = rad_to_deg(game->player.theta) - (FOV / 2);
	while (index < WIN_W)
	{
		rays_in_povs(&rays[index], game->player.plane, angle);
		render_frame(&rays[index], index);
		angle += FOV / WIN_W;
		index++;
	}
	return (SUCCESS);
}
// ft_memset(rays, 0, WIN_W * sizeof(t_ray));