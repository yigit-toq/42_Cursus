/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_image_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 19:18:41 by ytop              #+#    #+#             */
/*   Updated: 2025/01/16 20:37:56 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long_bonus.h"
#include "../../includes/libft.h"
#include "../../minilibx/mlx.h"
#include <time.h>

static void	add_image_utils(t_game *game, char *string, int i);
static void	add_image_finder(t_game *game, char *path, char *str, void **img);

void	add_images(t_game *game)
{
	char	*string;
	char	*frame;
	int		i;

	i = 0;
	while (i < 9)
	{
		frame = ft_itoa(i);
		error_controller(game, 'A', "Malloc not allocated.", frame);
		string = ft_strjoin(frame, ".xpm");
		free(frame);
		error_controller(game, 'A', "Malloc not allocated.", string);
		add_image_finder(game, DYNAMITE_IMG, string, game->img->dynamite);
		add_image_finder(game, KEY_IMG, string, game->keys->img);
		add_image_utils(game, string, i);
		free(string);
		i++;
	}
	return ;
}

static void	add_image_utils(t_game *game, char *string, int i)
{
	if (i < 6)
		add_image_finder(game, EXPO_IMG, string, game->img->explosion);
	if (i < 5)
		add_image_finder(game, DIE_IMG, string, game->player->img_die);
	if (i < 4)
		add_image_finder(game, DOOR_IMG, string, game->door->img);
	if (i < 3)
	{
		add_image_finder(game, PLAYER_F_IMG, string, game->player->img_f);
		add_image_finder(game, PLAYER_B_IMG, string, game->player->img_b);
		add_image_finder(game, PLAYER_L_IMG, string, game->player->img_l);
		add_image_finder(game, PLAYER_R_IMG, string, game->player->img_r);
		add_image_finder(game, FLOOR_IMG, string, game->img->floor);
		if (game->count->enemy > 0)
		{
			add_image_finder(game, ENEMY_F_IMG, string, game->img->enemy_f);
			add_image_finder(game, ENEMY_B_IMG, string, game->img->enemy_b);
			add_image_finder(game, ENEMY_L_IMG, string, game->img->enemy_l);
			add_image_finder(game, ENEMY_R_IMG, string, game->img->enemy_r);
		}
	}
	return ;
}

static void	add_image_finder(t_game *game, char *path, char *string, void **img)
{
	char	*result;
	int		i;

	i = string[0] - 48;
	result = ft_strjoin(path, string);
	if (!result)
	{
		free(string);
		error_controller(game, 'A', "Malloc not allocated.", 0);
	}
	img[i] = new_image(game, result, string);
	free(result);
	return ;
}

void	*new_image(t_game *game, char *path, char *string)
{
	void	*img;

	img = mlx_xpm_file_to_image(game->mlx, path, &game->img->w, &game->img->h);
	if (!img)
	{
		ft_printf("%sPath: %s\n%s", BLUE, path, END);
		free(path);
		free(string);
		error_controller(game, 'A', "Failed to load image.", 0);
	}
	return (img);
}

void	floor_init(t_game *g, int x, int y, int i)
{
	srandom(time(NULL));
	g->map->f_map = ft_calloc(g->map->h, sizeof(int *));
	error_controller(g, 'A', "Malloc not allocated.", g->map->f_map);
	while (++y < g->map->h)
	{
		g->map->f_map[y] = ft_calloc(g->map->w, sizeof(int));
		error_controller(g, 'A', "Malloc not allocated.", g->map->f_map[y]);
		x = -1;
		while (++x < g->map->w)
		{
			if (g->map->map[y][x] == WALL)
				g->map->f_map[y][x] = 0;
			else
			{
				i = random() % 10;
				if (i < 6)
					g->map->f_map[y][x] = 1;
				else if (i < 8)
					g->map->f_map[y][x] = 2;
				else
					g->map->f_map[y][x] = 3;
			}
		}
	}
}
