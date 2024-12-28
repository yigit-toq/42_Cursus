// static void	fix_hit(t_size *s_pos, t_size *e_pos, int s_y, int e_y)
// {
// 	s_pos->y = s_y;
// 	e_pos->y = e_y;
// 	if (s_pos->y < 0)
// 		s_pos->y = 0;
// 	if (e_pos->y > WIN_H)
// 		e_pos->y = WIN_H;
// }

// static void	render_frame(t_ray *ray, int index)
// {
// 	t_game	*game;
// 	t_size	s_pos;
// 	t_size	e_pos;
// 	double	img_x;
//
// 	game = get_game();
// 	s_pos.x = index;
// 	e_pos.x = index;
//
// 	img_x = floor((int)(game->img->dir_symbl[0].w_s * (ray->src.x + ray->src.y)) % game->img->dir_symbl[0].w_s);
//
// 	draw_tex(index, img_x, ray->wall.height, game->img->dir_symbl[0]);
//
// 	fix_hit(&s_pos, &e_pos, (WIN_H / 2) - ray->wall.height, 0);
// 	draw_hit(game->img->bgframe, s_pos, e_pos, game->img->hex_color[1]);
//
// 	fix_hit(&s_pos, &e_pos, (WIN_H / 2) + ray->wall.height, WIN_H);
// 	draw_hit(game->img->bgframe, s_pos, e_pos, game->img->hex_color[0]);
//
// 	for (int y = 0; y < WIN_H; y++)
// 	{
// 		unsigned int color = get_pixel_color(*game->player.anim->frame, index, y);
//
// 		unsigned char blue = (color >> 0) & 255;
//
// 		int	cross_x = (WIN_W / 2) - 32;
// 		int	cross_y = (WIN_H / 2) - 32;
//
// 		if ((index > cross_x && index < cross_x + 64) && (y > cross_y && y < cross_y + 64))
// 		{
// 			unsigned int color = get_pixel_color(game->img->cross, index - cross_x, y - cross_y);
//
// 			if (color == 0)
// 				mlx_image_put(game->img->bgframe, index, y, color);
// 		}
// 		if (blue < 130)
// 		{
// 			mlx_image_put(game->img->bgframe, index, y, color);
// 		}
// 	}
// }

// static void	rays_in_povs(t_ray *ray, t_vect pos, double angle)
// {
// 	t_game	*game;
// 	t_size	map;
//
// 	game = get_game();
// 	ray->pos.x = pos.x;
// 	ray->pos.y = pos.y;
// 	ray->dir.x = cos(deg_to_rad(angle)) / SEV;
// 	ray->dir.y = sin(deg_to_rad(angle)) / SEV;
// 	while (TRUE)
// 	{
// 		ray->pos.x += ray->dir.x;
// 		ray->pos.y += ray->dir.y;
// 		map.x = floor(ray->pos.x / game->map->scale.x);
// 		map.y = floor(ray->pos.y / game->map->scale.y);
// 		if (game->map->map[map.y][map.x] == WALL)
// 			break ;
// 	}
// 	ray->dist = sqrt(pow(ray->pos.x - pos.x, 2) + pow(ray->pos.y - pos.y, 2));
//
// 	ray->dist = ray->dist * cos (deg_to_rad(angle) - game->player.theta);
//
// 	ray->wall.height = floor((WIN_H / 2) / ray->dist);
// }