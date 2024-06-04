/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_enemy_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 13:03:26 by ytop              #+#    #+#             */
/*   Updated: 2024/05/18 18:06:34 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long_bonus.h"

static void	enemy_animation_utils(t_enemy *enemy, void **img);

void	enemy_finder(t_enemy **enemy, t_game *game, int x, int y)
{
	int		i;

	i = 0;
	while (game->map->map[y])
	{
		x = 0;
		while (game->map->map[y][x])
		{
			if (game->map->map[y][x] == ENEMY)
			{
				enemy[i]->frame = 0;
				enemy[i]->death = 0;
				enemy[i]->speed = 0;
				enemy[i]->m_dir[0] = x;
				enemy[i]->m_dir[1] = y;
				enemy[i]->t_dir[0] = x * CONST;
				enemy[i]->t_dir[1] = y * CONST;
				enemy_direction(enemy[i], game, x, y);
				i++;
			}
			x++;
		}
		y++;
	}
	return ;
}

void	enemy_direction(t_enemy *enemy, t_game *game, int x, int y)
{
	if (game->map->map[y - 1][x] != WALL)
	{
		enemy->direction = 'B';
		enemy->img = game->img->enemy_b[0];
	}
	else if (game->map->map[y][x + 1] != WALL)
	{
		enemy->direction = 'R';
		enemy->img = game->img->enemy_r[0];
	}
	else if (game->map->map[y + 1][x] != WALL)
	{
		enemy->direction = 'F';
		enemy->img = game->img->enemy_f[0];
	}
	else if (game->map->map[y][x - 1] != WALL)
	{
		enemy->direction = 'L';
		enemy->img = game->img->enemy_l[0];
	}
	return ;
}

void	enemy_animation(t_game *game, t_enemy *enemy)
{
	if (enemy->direction == 'R')
		enemy_animation_utils(enemy, game->img->enemy_r);
	else if (enemy->direction == 'L')
		enemy_animation_utils(enemy, game->img->enemy_l);
	else if (enemy->direction == 'F')
		enemy_animation_utils(enemy, game->img->enemy_f);
	else if (enemy->direction == 'B')
		enemy_animation_utils(enemy, game->img->enemy_b);
	if (enemy->speed % (F_SPEED * 2) == 0)
		enemy->frame++;
	enemy->speed++;
	return ;
}

static void	enemy_animation_utils(t_enemy *enemy, void **img)
{
	if (enemy->frame < 3)
		enemy->img = img[enemy->frame];
	else
		enemy->frame = 0;
	return ;
}
