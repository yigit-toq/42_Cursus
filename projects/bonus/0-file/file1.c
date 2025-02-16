/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 18:54:59 by ytop              #+#    #+#             */
/*   Updated: 2024/12/27 16:34:25 by ytop             ###   ########.fr       */
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
	int		p;

	game = get_game();
	m = game->map->map[y];
	p = (m[x] == NORTH || m[x] == SOUTH || m[x] == WEST || m[x] == EAST);
	if (p == TRUE)
	{
		game->count.player++;
		game->player.pos.x = x;
		game->player.pos.y = y;
		game->player.direction = m[x];
	}
	else if (m[x] == DOOR)
	{
		game->count.door++;
	}
	else if (m[x] == WALL)
	{
		game->count.wall++;
	}
	else if (m[x] == FLOOR)
	{
		game->count.floor++;
	}
	if (wtspace_check(m[x]) == FALSE) // will look again
		if (ft_strchr("01NSWED", m[x]) == NULL)
			error_controller("Invalid character in file.", NULL);
}

// if (flood_fill(x, y))
	// 	error_controller("Map is not closed.", NULL);

static void	maps_control(void)
{
	t_game	*game;
	int		x;
	int		y;

	x = 0;
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
	if (flood_fill((int)game->player.pos.x, (int)game->player.pos.y))
		error_controller("Map is not closed!!", NULL);
	if (game->count.player < P_COUNT)
		error_controller("There is no player.", NULL);
	if (game->count.player > P_COUNT)
		error_controller("There can be only one player.", NULL);
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
	game->map->mini.x = 4;
	game->map->mini.y = 4;
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
	game->map->pivot.y = WIN_H - (game->map->size.y * game->map->mini.y);
}
