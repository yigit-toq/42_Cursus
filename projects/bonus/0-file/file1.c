/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 18:54:59 by ytop              #+#    #+#             */
/*   Updated: 2025/03/07 16:56:13 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

#include <unistd.h>

static int	flood_fill(int x, int y)
{
	static char	**map;

	if (map == NULL)
	{
		map = copy_array(get_game()->map->map, get_game()->map->size.y);
	}
	if (y < 0 || x < 0 || !map[y] || map[y][x] == '\0')
		return (FAILURE);
	else if (map[y][x] == VISITED || map[y][x] == WALL || map[y][x] == DOOR)
		return (SUCCESS);
	else if (map[y][x] != SPACE)
	{
		map[y][x] = VISITED;
	}
	else
		return (FAILURE);
	if (flood_fill(x - 1, y) == FAILURE)
		return (FAILURE);
	if (flood_fill(x, y - 1) == FAILURE)
		return (FAILURE);
	if (flood_fill(x + 1, y) == FAILURE)
		return (FAILURE);
	if (flood_fill(x, y + 1) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static void	object_counter(int x, int y)
{
	t_game	*game;
	char	*m;

	game = get_game();
	m = game->map->map[y];
	if (m[x] == NORTH || m[x] == SOUTH || m[x] == WEST || m[x] == EAST)
	{
		game->count.player++;
		game->player.pos.x = x;
		game->player.pos.y = y;
		game->player.direction = m[x];
	}
	else if (m[x] == ENMY)
		game->count.enmy++;
	else if (m[x] == DOOR)
		game->count.door++;
	else if (m[x] == WALL)
		game->count.wall++;
	else if (m[x] == FLOOR)
		game->count.floor++;
	if (x == 0 && (m[x] == '\n' || m[x] == '\r'))
		error_controller("Empty line detect", NULL);
	else
		error_controller("Invalid character", ft_strchr("01NSWEAD \r\n", m[x]));
}

static void	maps_control(void)
{
	t_game	*game;
	int		x;
	int		y;

	y = 0;
	game = get_game();
	while (game->map->map[y])
	{
		x = 0;
		while (game->map->map[y][x])
		{
			object_counter(x, y);
			x++;
		}
		if (game->map->size.x < x)
			game->map->size.x = x - 1;
		y++;
	}
	game->map->size.y = y;
	if (game->count.player < P_COUNT)
		error_controller("There is no player", NULL);
	if (game->count.player > P_COUNT)
		error_controller("Too many players!!", NULL);
	if (flood_fill(game->player.pos.x, game->player.pos.y))
		error_controller("Map is not closed!", NULL);
}

static void	reading_file(int fd)
{
	char	**file;
	char	*total;
	char	*line;

	total = ft_strdup("");
	while (TRUE)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		total = ft_strjoin(total, line);
	}
	close(fd);
	file = ft_split(total, '\n');
	error_controller("File not found.", get_game()->map->map = file);
}

void	files_controller(char *path)
{
	t_game	*game;

	reading_file(open_file(path));
	path_control();
	maps_control();
	game = get_game();
	game->map->mini.x = WIN_H / 3;
	game->map->mini.y = WIN_H / 3;
	game->map->scale.x = 1;
	game->map->scale.y = 1;
	game->player.speed = SPEED;
	if (game->player.direction == EAST)
		game->player.theta = deg_to_rad(00);
	if (game->player.direction == SOUTH)
		game->player.theta = deg_to_rad(90);
	if (game->player.direction == WEST)
		game->player.theta = deg_to_rad(180);
	if (game->player.direction == NORTH)
		game->player.theta = deg_to_rad(270);
	game->map->pivot.x = 0;
	game->map->pivot.y = WIN_H - (game->map->mini.y);
}
