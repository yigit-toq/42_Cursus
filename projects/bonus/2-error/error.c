/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 18:54:45 by ytop              #+#    #+#             */
/*   Updated: 2025/03/07 17:51:57 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

#include <mlx.h>

static void	free_game(void);

void	error_controller(char *message, void *pointer)
{
	if (pointer)
		return ;
	ft_dprintf(2, C_G"________________________________________\n");
	ft_dprintf(2, C_R"\nError: " C_Y"%s\n" C_E, message);
	ft_dprintf(2, C_G"________________________________________\n");
	ft_dprintf(2, C_E);
	exit_game(get_game(), EXIT_FAILURE);
}

int	exit_game(t_game *game, int status)
{
	if (game->img != NULL)
		free_game();
	if (game->mlx != NULL)
		mlx_destroy_display(game->mlx);
	clear_garbage();
	exit(status);
}

static void	destroy_images(t_data *frames, int total)
{
	t_game	*game;
	int		i;

	i = 0;
	game = get_game();
	while (i < total)
	{
		if (frames[i].img)
			mlx_destroy_image(game->mlx, frames[i].img);
		i++;
	}
}

static void	free_game_utils(void)
{
	t_game	*game;

	game = get_game();
	if (game->img->bgframe.img)
		mlx_destroy_image(game->mlx, game->img->bgframe.img);
	if (game->img->minimap.img)
		mlx_destroy_image(game->mlx, game->img->minimap.img);
	if (game->img->skybox.img)
		mlx_destroy_image(game->mlx, game->img->skybox.img);
	if (game->img->ground.img)
		mlx_destroy_image(game->mlx, game->img->ground.img);
	if (game->img->crossh.img)
		mlx_destroy_image(game->mlx, game->img->crossh.img);
	if (game->utl == NULL)
		return ;
	while (game->utl->door && game->count.door-- > 0)
	{
		destroy_images(game->utl->door[game->count.door].anim.frames,
			game->utl->door[game->count.door].anim.total);
	}
	while (game->enmy)
	{
		destroy_images(game->enmy->anim.frames, game->enmy->anim.total);
		game->enmy = game->enmy->next;
	}
}

static void	free_game(void)
{
	t_game	*game;

	game = get_game();
	if (game->win != NULL)
		mlx_destroy_window(game->mlx, game->win);
	destroy_images(game->img->direct, DIR);
	destroy_images(game->img->knife[0].frames, game->img->knife[0].total);
	destroy_images(game->img->knife[1].frames, game->img->knife[1].total);
	destroy_images(game->img->vandal[0].frames, game->img->vandal[0].total);
	destroy_images(game->img->vandal[1].frames, game->img->vandal[1].total);
	destroy_images(game->img->vandal[2].frames, game->img->vandal[2].total);
	destroy_images(game->img->vandal[3].frames, game->img->vandal[3].total);
	destroy_images(game->img->qskill[0].frames, game->img->qskill[0].total);
	destroy_images(game->img->qskill[1].frames, game->img->qskill[1].total);
	destroy_images(game->img->qskill[2].frames, game->img->qskill[2].total);
	destroy_images(game->img->rskill[2].frames, game->img->rskill[2].total);
	free_game_utils();
}
