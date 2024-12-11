/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:25:41 by ytop              #+#    #+#             */
/*   Updated: 2024/12/11 18:12:23 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_size	typecast_size(t_coord coord)
{
	t_size	size;

	size.x = (int)coord.x;
	size.y = (int)coord.y;
	return (size);
}

unsigned int	get_pixel_color(t_data img, int x, int y)
{
	char	*pixel_address;

	if (x < 0 || y < 0 || x >= img.w_s || y >= img.h_s)
		return (0);
	pixel_address = img.addr + (y * img.length) + (x * (img.bit_pp / 8));
	return (*(unsigned int *)pixel_address);
}

void	mlx_image_put(t_data img, int x, int y, unsigned int color)
{
    if (y >= 0 && y < img.h_s && x >= 0 && x < img.w_s)
    {
        char *pixel_address = img.addr + (y * img.length) + (x * (img.bit_pp / 8));
        *(unsigned int *)pixel_address = color;
    }
}

double	grid_to_center(double pos, double scale, double pivot)
{
	return (pos * scale + (scale / 2) + (pivot * scale));
}

double	center_to_grid(double pos, double scale, double pivot)
{
	return ((pos - (pivot * scale)) / scale);
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

t_data	add_image(char *path, int create, int w, int h)
{
	t_game	*game;
	t_data	data;

	game = get_game();
	ft_memset(&data, 0, sizeof(t_data));
	if (create)
		data.img = mlx_new_image(game->mlx, w, h);
	else
		data.img = mlx_xpm_file_to_image(game->mlx, path, &data.w_s, &data.h_s);
	error_controller("Invalid texture file.", data.img);
	data.addr = mlx_get_data_addr(data.img, &data.bit_pp, &data.length, &data.endian);
	error_controller("Invalid texture data.", data.addr);
	data.w_s = w;
	data.h_s = h;
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
