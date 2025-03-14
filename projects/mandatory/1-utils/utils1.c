/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:25:41 by ytop              #+#    #+#             */
/*   Updated: 2025/03/14 16:41:26 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_mandatory.h"

#include <sys/time.h>
#include <fcntl.h>

#include <mlx.h>

t_data	add_image(char *path, t_size size)
{
	t_game	*game;
	t_data	data;

	game = get_game();
	ft_memset(&data, 0, sizeof(t_data));
	if (path)
	{
		data.img = mlx_xpm_file_to_image(game->mlx, path, &data.w_s, &data.h_s);
	}
	else
	{
		data.img = mlx_new_image(game->mlx, size.x, size.y);
		data.w_s = size.x;
		data.h_s = size.y;
	}
	error_controller("Invalid texture file.", data.img);
	data.add = mlx_get_data_addr(data.img, &data.bit_pp,
			&data.length, &data.endian);
	error_controller("Invalid texture data.", data.add);
	return (data);
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

int	wtspace_check(char c)
{
	return (c == ' ' || (c > 8 && c < 14));
}

char	*wtspace_trim(char *str)
{
	char	*result;
	char	*start;
	int		len;

	start = str;
	if (!str)
		return (NULL);
	len = ft_strlen(str);
	while (wtspace_check(*start) && *start)
	{
		start++;
		len--;
	}
	while (len > 0 && wtspace_check(start[len - 1]))
	{
		len--;
	}
	if (len <= 0)
		result = ft_substr(start, 0, 0);
	else
		result = ft_substr(start, 0, len);
	error_controller("Failed to allocate memory.", result);
	return (result);
}
