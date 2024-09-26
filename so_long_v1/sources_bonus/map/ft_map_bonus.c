/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 13:43:33 by ytop              #+#    #+#             */
/*   Updated: 2024/06/07 17:40:12 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long_bonus.h"
#include "../../includes/libft.h"
#include <unistd.h>
#include <fcntl.h>

static void	map_controller(t_game *game, t_count *count, int x, int y);
static void	object_counter(t_game *game, char **map, int x, int y);

static int	open_file(char *name)
{
	int		fd;

	fd = open(name, O_RDONLY);
	if (fd < 0)
		error_controller(0, 'E', "Failed to open file.", 0);
	return (fd);
}

static void	map_width(t_game *game)
{
	int	y;

	y = 0;
	if (!game->map->map[y])
	{
		free(game->map->map);
		error_controller(game, 'E', "Empty line detected.", 0);
	}
	while (game->map->map[y][game->map->w])
		game->map->w++;
	while (game->map->map[++y])
	{
		if (game->map->w != (int)ft_strlen(game->map->map[y]))
		{
			ft_printf("%sHeight: %d\n%s", BLUE, y, END);
			error_controller(game, 'M', "Map is not rectangular.", 0);
		}
	}
	if (game->map->h != y)
	{
		game->map->h = y;
		error_controller(game, 'M', "Empty line detected.", 0);
	}
	return (ft_bzero(game->count, sizeof(t_count)));
}

void	map_reading(t_game *game, char *map, char *total_line)
{
	char	*temporary;
	char	*line;
	int		fd;

	fd = open_file(map);
	temporary = ft_strdup("");
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		total_line = ft_strjoin(temporary, line);
		free(temporary);
		free(line);
		temporary = total_line;
		game->map->h++;
	}
	close(fd);
	game->map->map = ft_split(total_line, '\n');
	free(total_line);
	if (!game->map->h)
		free(temporary);
	error_controller(0, 'E', "Map not found.", game->map->map);
	map_width(game);
	return (map_controller(game, game->count, -1, -1));
}

static void	map_controller(t_game *game, t_count *count, int x, int y)
{
	char	**path;

	path = ft_calloc(game->map->h, sizeof(char *));
	error_controller(game, 'M', "Malloc not allocated.", path);
	while (game->map->map[++y])
	{
		x = -1;
		while (game->map->map[y][++x])
		{
			object_counter(game, game->map->map, x, y);
			wall_control(game->map, x, y, path);
			char_control(game->map, x, y, path);
		}
		path[y] = ft_strdup(game->map->map[y]);
		if (!path[y])
		{
			array_free((void **)path, game->map->h);
			error_controller(game, 'M', "Malloc not allocated.", 0);
		}
	}
	path_finder(count, path, game->player->x, game->player->y);
	array_free((void **)path, game->map->h);
	object_control(game);
	if (count->v_obj[0] != count->collect || count->v_obj[1] != count->exit)
		error_controller(game, 'M', "Path is not valid.", 0);
}

static void	object_counter(t_game *game, char **map, int x, int y)
{
	if (map[y][x] == PLAYER)
	{
		game->count->player++;
		game->player->x = x;
		game->player->y = y;
		game->player->t_x = x * CONST;
		game->player->t_y = y * CONST;
	}
	else if (map[y][x] == ENEMY)
		game->count->enemy++;
	else if (map[y][x] == COLLECT)
		game->count->collect++;
	else if (map[y][x] == FLOOR)
		game->count->floor++;
	else if (map[y][x] == WALL)
		game->count->wall++;
	else if (map[y][x] == EXIT)
	{
		game->count->exit++;
		game->count->e_dir[0] = x;
		game->count->e_dir[1] = y;
	}
	return ;
}
