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
	return (c == ' ' || (c > 8 && c < 14));
}

char	*wspace_trim(char *str)
{
	int		len;

	len = 0;
	if (!str)
		return (0);
	while (str[len])
	{
		len++;
	}
	while (wspace_check(*str))
	{
		str++;
	}
	while (wspace_check(str[len - 1]))
	{
		len--;
	}
	return (ft_substr(str, 0, len));
}

void	*open_xpm(char *path)
{
	t_img	*img;
	void	*xpm;

	img = get_game()->img;
	xpm = mlx_xpm_file_to_image(get_game()->mlx, path, &img->width, &img->height);
	if (!xpm)
	{
		error_controller("Invalid texture file.", NULL);
	}
	return (xpm);
}

int	open_file(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		error_controller("Failed to open file.", NULL);
	}
	return (fd);
}
