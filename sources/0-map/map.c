/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 18:54:59 by ytop              #+#    #+#             */
/*   Updated: 2024/10/20 18:54:59 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <fcntl.h>
#include <unistd.h>

static void	object_counter(int x, int y)
{
	t_game	*game;
	char	*m;
	int		p;

	game = get_game();
	m = game->map->map[y];
	p = m[x] == NORTH || m[x] == SOUTH || m[x] == WEST || m[x] == EAST;
	if (p == TRUE)
	{
		game->player.dir = m[x];
		game->player.x = x;
		game->player.y = y;
		game->count.player++;
	}
	else if (m[x] == FLOOR)
		game->count.floor++;
	else if (m[x] == WALL)
		game->count.wall++;
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
		y++;
	}
	if (!game->count.player)
		error_controller("There is no player.", NULL);
	if (game->count.player > P_COUNT)
		error_controller("There can be only one player.", NULL);
}

static int	open_file(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		error_controller("Failed to open file.", NULL);
	return (fd);
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

char	*line_trim(char *line);

void	path_handler(void)
{
	char	**file;
	char	*line;
	int		y;

	y = 0;
	file = get_game()->map->map;
	while (file[y])
	{
		line = line_trim(file[y]);
		y++;
	}
	(void)line;
}

void	file_controller(char *path)
{
	reading_file(open_file(path));
	path_handler();
	map_controls();
}

char	*line_trim(char *line)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[i] == ' ' || (line[i] > 8 && line[i] < 14))
		i++;
	while (line[j])
		j++;
	while (line[j] == ' ' || (line[j] > 8 && line[j] < 14))
		j--;
	new = ft_substr(line, i, (j - i) + 1);
	return (new);
}
