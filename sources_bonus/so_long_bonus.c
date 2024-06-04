/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:54:20 by ytop              #+#    #+#             */
/*   Updated: 2024/06/04 13:36:18 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"
#include "../includes/libft.h"
#include "../minilibx/mlx.h"
#include <unistd.h>

static void	mlx_controller(t_game *game, int width, int height);
static void	player_death(t_game *game);
static void	image_init(t_game *game);
static int	draw_init(t_game *game);

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
	if (count.v_obj[2] != count.enemy)
		error_controller(&game, 'M', "Enemy can't reach the player.", 0);
	mlx_controller(&game, game.map->w, game.map->h);
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
	enemy_init(game);
	mlx_hook(win, 2, 0, key_controller, game);
	mlx_hook(win, 3, 0, static_position, game);
	mlx_hook(win, 17, 0, close_controller, game);
	mlx_loop_hook(mlx, draw_init, game);
	mlx_loop(mlx);
}

static int	draw_init(t_game *game)
{
	usleep(25000);
	draw_map(game);
	door_animation(game);
	collect_animation(game);
	enemy_controller(game, game->enemy);
	dynamite_animation(game);
	player_death(game);
	put_object(game, game->player->t_x, game->player->t_y, game->player->img);
	return (0);
}

static void	image_init(t_game *game)
{
	t_dynamite	*dynamite;
	t_door		*door;
	t_key		*key;

	dynamite = ft_calloc(1, sizeof(t_dynamite));
	game->dynamite = dynamite;
	error_controller(game, 'A', "Malloc not allocated.", dynamite);
	door = ft_calloc(1, sizeof(t_door));
	game->door = door;
	error_controller(game, 'A', "Malloc not allocated.", door);
	key = ft_calloc(1, sizeof(t_key));
	game->key = key;
	error_controller(game, 'A', "Malloc not allocated.", key);
	add_image(game);
	game->img->floor = new_image(game, FLOOR_IMG, 0);
	game->img->wall = new_image(game, WALL_IMG, 0);
	game->img->collect = game->key->img[0];
	game->img->exit = game->door->img[0];
	game->player->img = game->player->img_f[0];
	return ;
}

static void	player_death(t_game *game)
{
	static int	speed;
	static int	frame;

	if (!game->player->death)
		return ;
	if (frame < 4)
	{
		game->player->img = game->player->img_die[frame];
	}
	else
	{
		sleep(1);
		ft_printf("%sYou're dead.\n%s", RED, END);
		close_controller(game);
	}
	if (speed % F_SPEED == 0)
		frame++;
	speed++;
	return ;
}
