/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:36:07 by ytop              #+#    #+#             */
/*   Updated: 2024/08/16 17:04:00 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx/mlx.h"
#include "so_long.h"
#include "libft.h"

static void	image_free(t_game *game);

void	extension_controller(char *path)
{
	char	*name;
	char	*extension;
	int		result;

	name = ft_strdup(path);
	error_controller(0, 'E', "Malloc not allocated.", name);
	extension = ft_strrchr(name, '.');
	if (!extension)
	{
		free(name);
		error_controller(0, 'E', "Wrong format.", 0);
	}
	if (ft_strlen(extension) == 4)
		result = ft_strncmp(extension, ".ber", 4);
	else
		result = 1;
	free(name);
	if (result)
		error_controller(0, 'E', "Wrong extension.", 0);
	return ;
}

void	error_controller(t_game *game, char type, char *message, void *ptr)
{
	if (ptr)
		return ;
	if (type == 'F' || type == 'A')
	{
		image_free(game);
		map_free(game->map->map, game->map->h);
		mlx_destroy_window(game->mlx, game->win);
	}
	if (type == 'M' || type == 'E' || type == 'A')
	{
		if (type == 'M')
			map_free(game->map->map, game->map->h);
		ft_printf("%sError%s", RED, END);
		ft_printf("%s\n%s\n%s", YELLOW, message, END);
		exit(EXIT_FAILURE);
	}
	return ;
}

void	map_free(char **map, int length)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (i < length)
	{
		if (map[i])
			free(map[i]);
		i++;
	}
	if (map)
		free(map);
	return ;
}

static void	image_free(t_game *game)
{
	if (game->img->collect)
		mlx_destroy_image(game->mlx, game->img->collect);
	if (game->img->floor)
		mlx_destroy_image(game->mlx, game->img->floor);
	if (game->img->wall)
		mlx_destroy_image(game->mlx, game->img->wall);
	if (game->img->exit)
		mlx_destroy_image(game->mlx, game->img->exit);
	if (game->player->img)
		mlx_destroy_image(game->mlx, game->player->img);
	return ;
}
