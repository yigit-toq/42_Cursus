/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:29:44 by ytop              #+#    #+#             */
/*   Updated: 2024/10/21 18:13:23 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_rgb_color(int *color, char *line)
{
	char	**rgb;
	char	*trim;
	int		i;
	int		j;

	i = 0;
	rgb = ft_split(line, ',');
	while (rgb[i])
	{
		j = 0;
		trim = wspace_trim(rgb[i]);
		while (trim[j])
		{
			if (!ft_isdigit(trim[j]))
				break ;
			j++;
		}
		color[i] = ft_atoi(rgb[i]);
		if (color[i] < 0 || color[i] > 255 || trim[j])
			break ;
		i++;
	}
	if (i != 3)
		error_controller("Invalid color.", NULL);
}

int	path_handle(char *line, char **names)
{
	t_game	*game;
	int		len;
	int		i;

	i = 0;
	game = get_game();
	while (names[i])
	{
		len = ft_strlen(names[i]);
		if (!ft_strncmp(line, names[i], len))
		{
			if (len == 2)
				game->texture.direction[i] = wspace_trim(line + len);
			else
				set_rgb_color(game->texture.colors[i - 4], line + len);
			return (SUCCESS);
		}
		i++;
	}
	return (FAILURE);
}

void	path_handler(void)
{
	static char	*names[] = {"NO", "SO", "WE", "EA", "F", "C"};
	char		**file;
	char		*line;

	file = get_game()->map->map;
	while (*file)
	{
		line = wspace_trim(*file);
		if (!path_handle(line, names))
			break ;
		file++;
		gfree(line);
	}
	get_game()->map->map = file;
}
