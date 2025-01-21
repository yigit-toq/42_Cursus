/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_graphics_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:26:25 by ytop              #+#    #+#             */
/*   Updated: 2025/01/16 20:29:49 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long_bonus.h"
#include "../../includes/libft.h"
#include "../../minilibx/mlx.h"

static void	put_image(t_game *game, int x, int y, void *img);
static void	put_door(t_game *game, int x, int y);
static void	put_str(t_game *game, int x, int y);

void	draw_level(t_game *game)
{
	t_map	*map;
	int		x;
	int		y;

	y = 0;
	map = game->map;
	while (y < map->h)
	{
		x = 0;
		while (x < map->w)
		{
			if (map->f_map[y][x])
				put_image(game, x, y, game->img->floor[map->f_map[y][x] - 1]);
			put_door(game, x, y);
			if (map->map[y][x] == WALL)
				put_image(game, x, y, game->img->wall);
			else if (map->map[y][x] == COLLECT)
				put_image(game, x, y, game->img->collect);
			x++;
		}
		y++;
	}
	return (put_str(game, 16, 16));
}

static void	put_image(t_game *game, int x, int y, void *img)
{
	mlx_put_image_to_window(game->mlx, game->win, img, x * CONST, y * CONST);
	return ;
}

static void	put_door(t_game *game, int x, int y)
{
	t_count	*count;

	count = game->count;
	if (x == count->e_dir[0] && y == count->e_dir[1])
		put_image(game, count->e_dir[0], count->e_dir[1], game->img->exit);
	return ;
}

static void	put_str(t_game *game, int x, int y)
{
	char	*step;
	char	*score;

	step = ft_itoa(game->count->step);
	mlx_string_put(game->mlx, game->win, x, y, 0xFFFFFF, "STEP: ");
	mlx_string_put(game->mlx, game->win, x + 72, y, 0xFFFFFF, step);
	score = ft_itoa(game->count->score);
	mlx_string_put(game->mlx, game->win, x, y + 16, 0xFFFFFF, "SCORE: ");
	mlx_string_put(game->mlx, game->win, x + 72, y + 16, 0xFFFFFF, score);
	free(step);
	free(score);
	return ;
}

void	put_object(t_game *game, int x, int y, void *img)
{
	mlx_put_image_to_window(game->mlx, game->win, img, x, y);
	return ;
}
