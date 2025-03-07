/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:29:44 by ytop              #+#    #+#             */
/*   Updated: 2025/03/07 18:53:33 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_mandatory.h"

static void	set_rgb_color(int *color, char *line)
{
	char	**rgb;
	char	*trim;
	int		i;
	int		j;

	line = wtspace_trim(line);
	if (line[ft_strlen(line) - 1] == ',')
		error_controller("Invalid color.", NULL); // will look again bonusa eklenmedi
	i = 0;
	rgb = ft_split(line, ',');
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
				set_rgb_color(game->img->rgb[i - DIR], line + len);
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
	static char	*names[] = {"NO", "SO", "WE", "EA", "F", "C", NULL};
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
	if (size != DIR + 2)
		error_controller("Missing path.", NULL);
	error_controller("Map is not found.", *file);
}
