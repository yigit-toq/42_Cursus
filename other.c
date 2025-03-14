// init.c

// game->curr->ratio = (double)game->curr->anim.index / (double)game->curr->anim.total;

// controller.c

// int	mouse_moves_handler(int x, int y)
// {
// 	static int	last_x = WIN_W / 2;
// 	int			delt_x;
//
// 	(void)y;
// 	if (get_game()->player.mctrl == FALSE)
// 		return (FAILURE);
// 	if ((delt_x = x - last_x) != 0)
// 	{
// 		get_game()->player.theta += deg_to_rad(delt_x * MOUSE_SENS);
// 	}
// 	last_x = x;
// 	return (SUCCESS);
// }

// int	input_systm(int f, int s, double acceleration)
// {
// 	t_game	*game;
// 	t_coord	*axis;
// 	t_coord	forw;
// 	t_coord	side;
// 	t_coord line;
// 	int		dir;
//
// 	game = get_game();
// 	side.x = -sin(game->player.theta);
//     side.y = +cos(game->player.theta);
// 	forw.x = +cos(game->player.theta);
//     forw.y = +sin(game->player.theta);
// 	axis = &game->player.axis;
//     if (f)
//     {
//         game->player.move[0] = TRUE;
// 		line = forw;
// 		dir = f;
//     }
//     if (s)
//     {
//         game->player.move[1] = TRUE;
// 		line = side;
// 		dir = s;
//     }
// 	if (fabs(axis->x) < MAX_SPEED)
// 	{
// 		axis->x += acceleration * line.x * dir;
// 	}
// 	if (fabs(axis->y) < MAX_SPEED)
// 	{
// 		axis->y += acceleration * line.y * dir;
// 	}
// 	game->player.position.x += axis->x * SPEED * (f * forw.x + s * side.x);
// 	game->player.position.y += axis->y * SPEED * (f * forw.y + s * side.y);
// 	// if (direction == 'N' || direction == 'S')
// 	// {
// 	// 	game->player.move[0] = TRUE;
// 	// 	axis = &game->player.axis.y;
// 	// 	game->player.position.y -= SPEED * (*axis);
// 	// }
// 	// if (direction == 'W' || direction == 'E')
// 	// {
// 	// 	game->player.move[1] = TRUE;
// 	// 	axis = &game->player.axis.x;
// 	// 	game->player.position.x += SPEED * (*axis);
// 	// }
// 	// if (fabs(*axis) < MAX_SPEED)
// 	// {
// 	// 	*axis += acceleration;
// 	// }
// 	return (SUCCESS);
// }

// graphics.c

// void	draw_hit(t_data image, t_size start, t_size curr, int color)
// {
// 	t_game	*game;
// 	t_size	step;
// 	t_size	dir;
// 	int		er1;
// 	int		er2;
//
// 	game = get_game();
// 	dir.x = abs(curr.x - start.x);
// 	dir.y = abs(curr.y - start.y);
// 	if (start.x < curr.x)
// 		step.x = +1;
// 	else
// 		step.x = -1;
// 	if (start.y < curr.y)
// 		step.y = +1;
// 	else
// 		step.y = -1;
// 	er1 = dir.x - dir.y;
// 	while (start.x != curr.x || start.y != curr.y)
// 	{
// 		if (image.add)
// 			mlx_image_put(image, start.x, start.y, color);
// 		else
// 			mlx_pixel_put(game->mlx, game->win, start.x, start.y, color);
// 		er2 = 2 * er1;
// 		if (er2 < +dir.x)
// 		{
// 			er1 += dir.x;
// 			start.y += step.y;
// 		}
// 		if (er2 > -dir.y)
// 		{
// 			er1 -= dir.y;
// 			start.x += step.x;
// 		}
// 	}
// }

// int	draw_circ(t_data data, t_vect center, t_vect radius, int color)
// {
// 	t_game	*game;
// 	t_vect	pos;
// 	t_vect	rds;
// 	t_vect	put;
//
// 	game = get_game();
// 	radius.x /= 2;
// 	radius.y /= 2;
// 	rds.x = pow(radius.x, 2);
// 	rds.y = pow(radius.y, 2);
// 	pos.y = -radius.y;
// 	while (pos.y <= radius.y)
// 	{
// 		pos.x = -radius.x;
// 		while (pos.x <= radius.x)
// 		{
// 			if ((pow(pos.x, 2) / rds.x) + (pow(pos.y, 2) / rds.y) <= 1)
// 			{
// 				put.x = center.x + pos.x;
// 				put.y = center.y + pos.y;
// 				if (data.add)
// 					mlx_image_put(data, put.x, put.y, color);
// 				else
// 					mlx_pixel_put(game->mlx, game->win, put.x, put.y, color);
// 			}
// 			pos.x++;
// 		}
// 		pos.y++;
// 	}
// 	if (radius.x == radius.y)
// 		return (SUCCESS);
// 	else
// 		return (FAILURE);
// }

// rot.x = center.x + (cos(game->player.theta) * radius.x);
// rot.y = center.y + (sin(game->player.theta) * radius.y);
// mlx_pixel_put(game->mlx, game->win, rot.x, rot.y, H_W);
//
// for (double angle = 0; angle < 2 * PI; angle += 0.001)
// {
//     p_coord.x = center.x + radius.x * cos(angle);
//     p_coord.y = center.y + radius.y * sin(angle);
//     mlx_pixel_put(game->mlx, game->win, p_coord.x, p_coord.y, 0xFFFFFF);
// }

// utils1.c

// void	delay(int ms)
// {
// 	struct timeval	time[2];
// 	long long int	t_time;
// 	long long int	c_time;
// 
// 	gettimeofday(&time[0], NULL);
// 	gettimeofday(&time[1], NULL);
// 	t_time = time[0].tv_sec * 1000 + time[0].tv_usec / 1000 + ms;
// 	c_time = time[1].tv_sec * 1000 + time[1].tv_usec / 1000;
// 	while (c_time < t_time)
// 	{
// 		gettimeofday(&time[1], NULL);
// 		c_time = time[1].tv_sec * 1000 + time[1].tv_usec / 1000;
// 	}
// }
