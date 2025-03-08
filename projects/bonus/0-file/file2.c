/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:29:44 by ytop              #+#    #+#             */
/*   Updated: 2025/03/07 16:57:44 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	set_rgb_color(int *color, char *line)
{
	char	**rgb;
	char	*trim;
	int		i;
	int		j;

	i = 0;
	rgb = ft_split(line, ',');
	error_controller("Failed to allocate memory.", rgb);
	while (rgb[i])
	{
		j = 0;
		trim = wtspace_trim(rgb[i]);
		while (trim[j])
		{
			if (ft_isdigit(trim[j]) == FALSE)
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

static int	path_read(char *line, char **names, int *j)
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
			if (len == 1)
			{
				set_rgb_color(game->img->rgb[i - (sizeof(game->img->paths) / sizeof(char *))], line + len);
			}
			else
			{
				game->img->paths[i] = wtspace_trim(line + len);
			}
			(*j)++;
			break ;
		}
		i++;
	}
	return (wtspace_trim(line)[0] != WALL); // will look again
}

void	path_control(void)
{
	static char	*names[] = {"NO", "SO", "WE", "EA", "WP", "GR", "CR", "C", NULL};
	char		**file;
	char		*line;
	int			size;

	size = 0;
	file = get_game()->map->map;
	while (*file)
	{
		line = wtspace_trim(*file);
		if (path_read(line, names, &size) == FALSE)
			break ;
		file++;
	}
	get_game()->map->map = file;
	if (size != 8)
		error_controller("Missing path.", NULL);
	error_controller("Map is not found.", *file);
}
