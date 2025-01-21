/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_animations_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:39:05 by ytop              #+#    #+#             */
/*   Updated: 2025/01/16 20:37:56 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long_bonus.h"

void	dynamite_animation(t_game *game)
{
	t_dynamite	*bomb;

	bomb = game->dynamite;
	if (!bomb->available)
		return ;
	if (bomb->life_time > 0)
	{
		if (bomb->frame < 9)
			bomb->img = game->img->dynamite[bomb->frame];
		else
			bomb->frame = 0;
		bomb->life_time--;
	}
	else if (bomb->frame < 6)
		bomb->img = game->img->explosion[bomb->frame];
	else
	{
		bomb->transform[0] = 0;
		bomb->transform[1] = 0;
		bomb->available = 0;
	}
	if (bomb->available)
		put_object(game, bomb->transform[0], bomb->transform[1], bomb->img);
	bomb->frame++;
}

void	collect_animation(t_game *game)
{
	if (game->keys->frame < 9)
		game->img->collect = game->keys->img[game->keys->frame];
	else
		game->keys->frame = 0;
	game->keys->frame++;
	return ;
}

void	door_animation(t_game *game)
{
	if (game->door->frame < 3 && game->door->unlock)
	{
		game->img->exit = game->door->img[game->door->frame + 1];
		game->door->frame++;
	}
	return ;
}

void	dynamite_drop(t_game *game)
{
	game->dynamite->transform[0] = game->player->t_x;
	game->dynamite->transform[1] = game->player->t_y;
	game->dynamite->life_time = 100;
	game->dynamite->available = 1;
	game->dynamite->frame = 0;
	return ;
}

int	static_position(int keycode, t_game *game)
{
	if (game->player->death)
		return (0);
	if (game->player->direction == 'B' && keycode == KEY_W)
		game->player->img = game->player->img_b[0];
	else if (game->player->direction == 'L' && keycode == KEY_A)
		game->player->img = game->player->img_l[0];
	else if (game->player->direction == 'F' && keycode == KEY_S)
		game->player->img = game->player->img_f[0];
	else if (game->player->direction == 'R' && keycode == KEY_D)
		game->player->img = game->player->img_r[0];
	else if (!game->dynamite->available && keycode == KEY_SPACE)
		dynamite_drop(game);
	game->player->frame = 0;
	return (0);
}
