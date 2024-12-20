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

#include "cub3d_bonus.h"

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
		mlx_image_put(get_game()->img->frame, x_p, y_p, get_pixel_color(img, x_c, y_c));
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

	img_x = floor((int)(game->img->dir_symbl[0].w_s * (ray->pos.x + ray->pos.y)) % game->img->dir_symbl[0].w_s);

	draw_hit(game->img->frame, s_pos, e_pos, game->img->hex_color[1]);

	s_pos.y = (WIN_H / 2) + ray->wall.height;
	e_pos.y = (WIN_H);
	
	draw_hit(game->img->frame, s_pos, e_pos, game->img->hex_color[0]);
	
	s_pos.y = (WIN_H / 2) - ray->wall.height;
	e_pos.y = (WIN_H / 2) + ray->wall.height;

	draw_tex(index, img_x, ray->wall.height, game->img->dir_symbl[0]);

	// draw_hit(game->img->frame, s_pos, e_pos, 0x007b14);

	for (int y = 0; y < 720; y++)
	{
		unsigned int color = get_pixel_color(*game->img->vandal, index, y);

		unsigned char green = (color >> 8) & 255;
		unsigned char blue = (color >> 0) & 255;

		int	cross_x = (WIN_W / 2) - 32;
		int	cross_y = (WIN_H / 2) - 32;

		if ((index > cross_x && index < cross_x + 64) && (y > cross_y && y < cross_y + 64))
		{
			unsigned int color = get_pixel_color(game->img->cross, index - cross_x, y - cross_y);

			if (color == 0)
				mlx_image_put(game->img->frame, index, y, color);
		}
		if (green < 200 && blue < 200)
		{
			mlx_image_put(game->img->frame, index, y, color);
		}
	}
}

static void	rays_in_povs(t_ray *ray, t_vect pos, double angle)
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

	ray->dist = cos(deg_to_rad(angle) - game->player.theta) * ray->dist;

	ray->wall.height = floor((WIN_H / 2) / ray->dist);
}

int	raycast(void)
{
	t_game				*game;
	t_ray				*rays;
	int					index;
	double				angle;
	static int			frame;
	static unsigned int	delay;

	game = get_game();
	rays = game->rays;
	if (delay % 3 == 0)
	{
		game->img->vandal = &game->img->gun_frame[frame];
		frame++;
	}
	if (frame == 74)
	{
		frame = 0;
		delay = 0;
	}
	else
	{
		delay++;
	}
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
