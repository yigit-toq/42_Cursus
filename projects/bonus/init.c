/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 00:52:41 by ytop              #+#    #+#             */
/*   Updated: 2025/03/03 18:53:11 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

#include <mlx.h>

#include <sys/time.h>

long double	sys_time(void)
{
	struct timeval	time_value;

	if (gettimeofday(&time_value, NULL) == -1)
		return (sys_time());
	return (time_value.tv_sec + (time_value.tv_usec / 1000000.0));
}

char	*get_fps(char *fps)
{
	static long double	second = 0;
	long double			start;
	int					value;

	start = sys_time();
	value = (int)(1 / (start - second));
	ft_strlcpy(fps, "FPS: ", 6);
	fps[5] = (value / 10) + '0';
	fps[6] = (value % 10) + '0';
	fps[7] = '\0';
	return (second = start, fps);
}

static void	init_objs(void)
{
	t_game	*game;
	t_size	index;

	ft_bzero(&index, sizeof(t_size));
	game = get_game();
	game->door = ft_calloc(game->count.door, sizeof(t_door));
	error_controller("Failed to allocate memory.", game->door);
	game->enemy = ft_calloc(game->count.enemy, sizeof(t_enemy));
	error_controller("Failed to allocate memory.", game->enemy);
	while (game->map->map[index.y])
	{
		index.x = 0;
		while (game->map->map[index.y][index.x])
		{
			if (game->map->map[index.y][index.x] == DOOR)
			{
				game->door[game->index].coor.x = index.x;
				game->door[game->index].coor.y = index.y;
				game->door[game->index].filter = 0x980088;
				init_animation(&game->door[game->index].anim, (t_size){0, 64}, ANIM_SPEED / 2, DOOR1_PATH);
				game->index++;
			}
			if (game->map->map[index.y][index.x] == ENEMY)
			{
				game->enemy->pos.x = index.x;
				game->enemy->pos.y = index.y;
			}
			index.x++;
		}
		index.y++;
	}
	init_animation(&game->enemy->anim, (t_size){0, 6}, ANIM_SPEED, ENEMY_PATH);
}

static void	update_animtion(void)
{
	t_game	*game;

	game = get_game();
	if (game->player.slot->fire && game->player.attack)
	{
		if (game->player.slot->gun->ammo > 0)
		{
			if (game->player.slot->gun)
			{
				game->player.slot->gun->reload = 0;
				game->player.slot->gun->ammo--;
			}
			game->player.slot->curr->play = FALSE;
			game->img->next_anim = game->player.slot->fire;
		}
	}
	if (game->curr && game->curr->anim.play == TRUE)
	{
		if (game->curr->state == FALSE)
			updt_animation(&game->curr->anim, FALSE);
		else
			updt_animation(&game->curr->anim, TRUE);
		//game->curr->ratio = (double)game->curr->anim.index / (double)game->curr->anim.total;
	}
}

void	update_enemy(void)
{
	t_game	*game;
	t_vect	d;
	int		i;

	i = 0;
	game = get_game();
	while (i < game->count.enemy)
	{
		d.x = game->enemy[i].pos.x - game->player.pos.x;
		d.y = game->enemy[i].pos.y - game->player.pos.y;
		game->enemy[i].dist = sqrt(d.x * d.x + d.y * d.y);
		i++;
	}
}

static int	next_frame(void)
{
	t_game	*game;

	game = get_game();
	update_position();
	update_animtion();
	swap_animation(game->player.slot->curr, game->img->next_anim);
	mlx_put_image_to_window(game->mlx, game->win, game->img->bgframe.img, 0, 0);
	mlx_string_put(game->mlx, game->win, 10, 16, 0x000000, get_fps(game->sfps));
	raycast();
	minimap();
	update_enemy();
	return (SUCCESS);
}

static void	init_img(void)
{
	t_size	size;
	t_img	*img;
	t_map	*map;
	int		len;
	int		i;

	img = get_game()->img;
	map = get_game()->map;
	len = (int)(sizeof(img->paths) / sizeof(char *));
	size.x = WIN_W;
	size.y = WIN_H;
	i = 0;
	while (i < len)
	{
		error_controller("Texture path is not found.", img->paths[i]);
		if (i < DIR_SIZE)
			img->direct[i] = add_image(img->paths[i], (t_size){0, 0});
		else if (i < DIR_SIZE + 4)
			img->skybox[i - DIR_SIZE] = add_image(img->paths[i], (t_size){0, 0});
		i++;
	}
	img->ground = add_image(img->paths[len - 2], (t_size){0, 0});
	img->crossh = add_image(img->paths[len - 1], (t_size){0, 0});
	img->bgframe = add_image(NULL, size);
	size.x = map->size.x * map->mini.x;
	size.y = map->size.y * map->mini.y;
	img->minimap = add_image(NULL, size);
	img->hex[0] = rgb_to_hexa(img->rgb[0][0], img->rgb[0][1], img->rgb[0][2]);
	img->hex[1] = rgb_to_hexa(img->rgb[1][0], img->rgb[1][1], img->rgb[1][2]);
	init_slot();
	init_objs();
}

void	init_game(void)
{
	t_game		*game;

	game = get_game();
	game->mlx = addgarbage(mlx_init());
	game->win = mlx_new_window(game->mlx, WIN_W, WIN_H, WIN_NAME);
	init_img();
	mlx_loop_hook(game->mlx, next_frame, NULL);
	mlx_hook(game->win, 2, 1L << 0, key_press_handler, game);
	mlx_hook(game->win, 3, 1L << 1, key_relse_handler, game);
	mlx_hook(game->win, 4, 1L << 2, mouse_press_handler, game);
	mlx_hook(game->win, 5, 1L << 3, mouse_relse_handler, game);
	mlx_hook(game->win, 6, 1L << 6, mouse_moves_handler, game);
	mlx_hook(game->win, DESTROY, 1L << DESTROY, exit_game, game);
	mlx_mouse_hook(game->win, mouse_press_handler, game);
	mlx_loop(game->mlx);
}
