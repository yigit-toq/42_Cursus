/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 13:56:33 by ytop              #+#    #+#             */
/*   Updated: 2024/08/08 14:22:51 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"
#include "libft.h"

void	wall_control(t_map *map, int x, int y, char **path)
{
	int	is_border;

	is_border = (y == 0 || x == 0 || y == map->h - 1 || x == map->w - 1);
	if (is_border && map->map[y][x] != WALL)
	{
		array_free((void **)path, map->h);
		array_free((void **)map->map, map->h);
		ft_printf("%sHeight: %d, Width: %d\n%s", BLUE, y + 1, x + 1, END);
		error_controller(0, 'E', "Map is not walled.", 0);
	}
	return ;
}

void	char_control(t_map *map, int x, int y, char **path)
{
	if (!ft_strchr("01PECA", map->map[y][x]))
	{
		array_free((void **)path, map->h);
		array_free((void **)map->map, map->h);
		ft_printf("%sHeight: %d, Width: %d\n%s", BLUE, y + 1, x + 1, END);
		error_controller(0, 'E', "Invalid object detected.", 0);
	}
	return ;
}

void	object_control(t_game *game)
{
	if (!game->count->collect)
		error_controller(game, 'M', "There is no collectible.", 0);
	if (!game->count->player)
		error_controller(game, 'M', "There is no player.", 0);
	if (!game->count->exit)
		error_controller(game, 'M', "There is no exit.", 0);
	if (game->count->player > PLAYER_COUNT)
		error_controller(game, 'M', "There can be only one player.", 0);
	if (game->count->exit > EXIT_COUNT)
		error_controller(game, 'M', "There can be only one exit.", 0);
	return ;
}

void	path_finder(t_count *count, char **map, int x, int y)
{
	if (x < 0 || y < 0 || !map[y] || !map[y][x])
		return ;
	if (map[y][x] == VISITED || map[y][x] == WALL)
		return ;
	if (map[y][x] == COLLECT)
		count->v_obj[0]++;
	if (map[y][x] == EXIT)
		count->v_obj[1]++;
	if (map[y][x] == ENEMY)
		count->v_obj[2]++;
	map[y][x] = VISITED;
	path_finder(count, map, x - 1, y);
	path_finder(count, map, x + 1, y);
	path_finder(count, map, x, y - 1);
	path_finder(count, map, x, y + 1);
}
