/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 18:54:59 by ytop              #+#    #+#             */
/*   Updated: 2024/12/10 16:59:57 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		game->player.position.x = x;
		game->player.position.y = y;
		game->player.direction = m[x];
	}
	else if (m[x] == WALL)
	{
		game->count.wall++;
	}
	else if (m[x] == FLOOR)
	{
		game->count.floor++;
	}
	if (wspace_check(m[x]) == FALSE)
		if (ft_strchr("01NSWE", m[x]) == NULL)
			error_controller("Invalid character in file.", NULL);
}

static void	map_controls(void)
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
	if (game->count.player == FALSE)
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
	map_controls();
	game = get_game();
	game->map->scale.x = (WIN_W / game->map->size.x);
	game->map->scale.y = (WIN_H / game->map->size.y);

	// game->map->pivot.y = (WIN_H - (game->map->scale.y * game->map->size.y)) / game->map->scale.y;
}
