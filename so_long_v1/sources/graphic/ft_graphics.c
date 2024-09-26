/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_graphics.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:26:25 by ytop              #+#    #+#             */
/*   Updated: 2024/05/24 22:55:54 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"
#include "../../includes/libft.h"
#include "../../minilibx/mlx.h"

static void	put_image(t_game *game, int x, int y, void *img);
static void	put_door(t_game *game, int x, int y);

int	draw_map(t_game *game)
{
	char	**map;
	int		x;
	int		y;

	y = 0;
	map = game->map->map;
	while (y < game->map->h)
	{
		x = 0;
		while (x < game->map->w)
		{
			put_image(game, x, y, game->img->floor);
			put_door(game, x, y);
			if (map[y][x] == WALL)
				put_image(game, x, y, game->img->wall);
			else if (map[y][x] == COLLECT)
				put_image(game, x, y, game->img->collect);
			else if (map[y][x] == PLAYER)
				put_image(game, x, y, game->player->img);
			x++;
		}
		y++;
	}
	return (0);
}

void	*new_image(t_game *game, char *path)
{
	void	*img;

	img = mlx_xpm_file_to_image(game->mlx, path, &game->img->w, &game->img->h);
	if (!img)
	{
		ft_printf("%sPath: %s\n%s", BLUE, path, END);
		error_controller(game, 'A', "Failed to load image.", 0);
	}
	return (img);
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
