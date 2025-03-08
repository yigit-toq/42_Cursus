/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 22:48:55 by ytop              #+#    #+#             */
/*   Updated: 2025/02/16 22:48:55 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

#include <sys/time.h>
#include <stdio.h>

#include <mlx.h>

static long double	sys_time(void)
{
	struct timeval	time_value;

	if (gettimeofday(&time_value, NULL) == -1)
		return (sys_time());
	return (time_value.tv_sec + (time_value.tv_usec / 1000000.0));
}

char	*get_fps(char *fps)
{
	static long double	second = 0;
	long double			start;
	int					value;

	start = sys_time();
	value = (int)(1 / (start - second));
	ft_strlcpy(fps, "FPS: ", 6);
	fps[5] = (value / 10) + '0';
	fps[6] = (value % 10) + '0';
	fps[7] = '\0';
	return (second = start, fps);
}

void	get_load(void)
{
	t_game	*game;
	char	string[30];

	game = get_game();
	sprintf(string, "Loading... %d%%", ++game->count.count * 100 / TOTAL);
	mlx_clear_window(game->mlx, game->win);
	mlx_string_put(game->mlx, game->win, WIN_W / 2 - 42, WIN_H / 2, H_W, string);
}

// void	get_load(t_game *game)
// {
// 	char	string[30];
// 	char	*val;
//
// 	val = ft_itoa(++game->count.count * 100 / TOTAL);
// 	ft_strlcpy(string, "Loading... ", sizeof(string));
// 	ft_strlcat(string, val, sizeof(string));
// 	ft_strlcat(string, "%", sizeof(string));
// 	mlx_string_put(game->mlx, game->win, WIN_W / 2 - 40, WIN_H / 2, H_W, string);
// }

char	**copy_array(char **array, int size)
{
	char	**copy;
	int		i;

	i = 0;
	copy = ft_calloc(size + 1, sizeof(char *));
	error_controller("Memory allocation failed.", copy);
	while (array[i])
	{
		copy[i] = ft_strdup(array[i]);
		error_controller("Memory allocation failed.", copy[i]);
		i++;
	}
	return (copy);
}
