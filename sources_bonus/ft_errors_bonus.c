/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:36:07 by ytop              #+#    #+#             */
/*   Updated: 2024/06/07 18:54:43 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"
#include "../includes/libft.h"
#include "../minilibx/mlx.h"

static void	image_free(t_game *game);
static void	image_free_utils(t_game *game, int i);

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
		array_free((void **)game->enemy, game->count->enemy);
		array_free((void **)game->map->f_map, game->map->h);
		array_free((void **)game->map->map, game->map->h);
		mlx_destroy_window(game->mlx, game->win);
		free(game->dynamite);
		free(game->door);
		free(game->key);
	}
	if (type == 'M' || type == 'E' || type == 'A')
	{
		if (type == 'M')
			array_free((void **)game->map->map, game->map->h);
		ft_printf("%sError%s", RED, END);
		ft_printf("%s\n%s\n%s", YELLOW, message, END);
		exit(EXIT_FAILURE);
	}
	return ;
}

void	array_free(void **ptr, int length)
{
	int	i;

	i = 0;
	if (!ptr)
		return ;
	while (i < length)
	{
		if (ptr[i])
			free(ptr[i]);
		i++;
	}
	if (ptr)
		free(ptr);
	return ;
}

static void	image_free(t_game *game)
{
	int		i;

	i = 0;
	if (!game->dynamite || !game->door || !game->key)
		return ;
	while (i < 9)
	{
		if (game->key->img[i])
			mlx_destroy_image(game->mlx, game->key->img[i]);
		if (game->img->dynamite[i])
			mlx_destroy_image(game->mlx, game->img->dynamite[i]);
		if (i < 6)
			if (game->img->explosion[i])
				mlx_destroy_image(game->mlx, game->img->explosion[i]);
		if (i < 5)
			if (game->player->img_die[i])
				mlx_destroy_image(game->mlx, game->player->img_die[i]);
		if (i < 4)
			if (game->door->img[i])
				mlx_destroy_image(game->mlx, game->door->img[i]);
		image_free_utils(game, i);
		i++;
	}
	if (game->img->wall)
		mlx_destroy_image(game->mlx, game->img->wall);
}

static void	image_free_utils(t_game *game, int i)
{
	if (i < 3)
	{
		if (game->player->img_f[i])
			mlx_destroy_image(game->mlx, game->player->img_f[i]);
		if (game->player->img_b[i])
			mlx_destroy_image(game->mlx, game->player->img_b[i]);
		if (game->player->img_l[i])
			mlx_destroy_image(game->mlx, game->player->img_l[i]);
		if (game->player->img_r[i])
			mlx_destroy_image(game->mlx, game->player->img_r[i]);
		if (game->img->floor[i])
			mlx_destroy_image(game->mlx, game->img->floor[i]);
		if (game->count->enemy > 0)
		{
			if (game->img->enemy_f[i])
				mlx_destroy_image(game->mlx, game->img->enemy_f[i]);
			if (game->img->enemy_b[i])
				mlx_destroy_image(game->mlx, game->img->enemy_b[i]);
			if (game->img->enemy_l[i])
				mlx_destroy_image(game->mlx, game->img->enemy_l[i]);
			if (game->img->enemy_r[i])
				mlx_destroy_image(game->mlx, game->img->enemy_r[i]);
		}
	}
	return ;
}
