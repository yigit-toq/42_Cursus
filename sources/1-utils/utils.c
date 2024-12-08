/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:25:41 by ytop              #+#    #+#             */
/*   Updated: 2024/12/05 16:39:42 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <sys/time.h>

double	grid_to_center(double grid, double scale, double pivot)
{
	return (grid * scale + (scale / 2) + pivot);
}

int rgb_to_hex(int red, int green, int blue)
{
	return ((red << 16) | (green << 8) | blue);
}

void	delay(int ms)
{
	struct timeval	time[2];
	long long int	c_time;
	long long int	t_time;

	gettimeofday(&time[0], NULL);
	gettimeofday(&time[1], NULL);	
	t_time = time[0].tv_sec * 1000 + time[0].tv_usec / 1000 + ms;
	c_time = time[1].tv_sec * 1000 + time[1].tv_usec / 1000;
	while (c_time < t_time)
	{
		gettimeofday(&time[1], NULL);
		c_time = time[1].tv_sec * 1000 + time[1].tv_usec / 1000;
	}
}

t_data	open_xpm(char *path)
{
	t_game	*game;
	t_img	*img;
	t_data	data;

	game = get_game();
	img = game->img;
	ft_memset(&data, 0, sizeof(t_data));
	data.img = mlx_xpm_file_to_image(game->mlx, path, &img->w_s, &img->h_s);
	error_controller("Invalid texture file.", data.img);
	data.addr = mlx_get_data_addr(data.img, &data.bit_pp, &data.length, &data.endian);
	error_controller("Invalid texture data.", data.addr);
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
