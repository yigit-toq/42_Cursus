/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:54:20 by ytop              #+#    #+#             */
/*   Updated: 2024/08/16 17:03:55 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx/mlx.h"
#include "so_long.h"
#include "libft.h"

static void	mlx_controller(t_game *game, int width, int height);
static void	image_init(t_game *game);

int	main(int argc, char *argv[])
{
	t_game		game;
	t_player	player;
	t_count		count;
	t_map		map;
	t_img		img;

	if (argc < 2)
		error_controller(0, 'E', "Usage: ./so_long [map.ber]", 0);
	else if (argc > 2)
		error_controller(0, 'E', "Too many arguments.", 0);
	extension_controller(argv[1]);
	ft_bzero(&game, sizeof(t_game));
	game.player = &player;
	game.count = &count;
	game.map = &map;
	game.img = &img;
	ft_bzero(&player, sizeof(t_player));
	ft_bzero(&map, sizeof(t_map));
	ft_bzero(&img, sizeof(t_img));
	player.x = -1;
	player.y = -1;
	map_reading(&game, argv[1], 0);
	mlx_controller(&game, game.map->w, game.map->h);
	return (0);
}

static void	mlx_controller(t_game *game, int width, int height)
{
	void	*mlx;
	void	*win;

	mlx = mlx_init();
	error_controller(game, 'M', "mlx_init() failed.", mlx);
	win = mlx_new_window(mlx, width * CONST, height * CONST, WIN_NAME);
	error_controller(game, 'M', "mlx_new_window() failed.", win);
	game->mlx = mlx;
	game->win = win;
	image_init(game);
	mlx_key_hook(win, key_controller, game);
	mlx_hook(win, 17, 0, close_controller, game);
	mlx_loop_hook(mlx, draw_map, game);
	mlx_loop(mlx);
}

static void	image_init(t_game *game)
{
	game->img->collect = new_image(game, COLLECTABLE_IMG);
	game->img->floor = new_image(game, FLOOR_IMG);
	game->img->wall = new_image(game, WALL_IMG);
	game->img->exit = new_image(game, DOOR_IMG);
	game->player->img = new_image(game, PLAYER_IMG);
	return ;
}