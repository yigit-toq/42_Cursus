/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:25:41 by ytop              #+#    #+#             */
/*   Updated: 2024/10/22 15:01:14 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	wspace_check(char c)
{
	return (c == ' ' || (c > '\t' && c < '\r'));
}

char	*wspace_trim(char *line)
{
	char	*new;
	int		i;
	int		j;

	if (!line)
		return (NULL);
	i = 0;
	j = 0;
	while (wspace_check(line[i]))
		i++;
	while (line[j])
		j++;
	while (wspace_check(line[j]))
		j--;
	new = ft_substr(line, i, (j - i) + 1);
	return (new);
}

void	*xpm_check(char *path)
{
	t_game	*game;
	t_img	*img;
	void	*xpm;

	game = get_game();
	img = game->img;
	xpm = mlx_xpm_file_to_image(game->mlx, path, &img->width, &img->height);
	if (!xpm)
		error_controller("Invalid texture file.", NULL);
	return (xpm);
}

int	open_file(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		error_controller("Failed to open file.", NULL);
	return (fd);
}
