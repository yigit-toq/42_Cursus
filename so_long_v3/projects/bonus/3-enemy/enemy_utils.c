/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 13:03:26 by ytop              #+#    #+#             */
/*   Updated: 2025/01/16 18:42:19 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"
#include "libft.h"

#include <stdlib.h>

static void	enemy_animation_utils(t_enemy *enemy, void **img);

void	enemy_finder(t_game *game, t_enemy **enemy, int x, int y)
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
				ft_bzero(enemy[i], sizeof(t_enemy));
				enemy[i]->m_dir[0] = x;
				enemy[i]->m_dir[1] = y;
				enemy[i]->t_dir[0] = x * CONST;
				enemy[i]->t_dir[1] = y * CONST;
				enemy_direction(game, enemy[i], x, y);
				i++;
			}
			x++;
		}
		y++;
	}
	return ;
}

char	enemy_direction(t_game *game, t_enemy *enemy, int x, int y)
{
	int			direction;

	while (1)
	{
		direction = rand() % 4;
		if (direction == 0 && game->map->map[y + 1][x] != WALL)
			return (enemy->direction = 'F');
		else if (direction == 1 && game->map->map[y - 1][x] != WALL)
			return (enemy->direction = 'B');
		else if (direction == 2 && game->map->map[y][x - 1] != WALL)
			return (enemy->direction = 'L');
		else if (direction == 3 && game->map->map[y][x + 1] != WALL)
			return (enemy->direction = 'R');
	}
}

void	enemy_animation(t_game *game, t_enemy *enemy)
{
	if (enemy->direction == 'F')
		enemy_animation_utils(enemy, game->img->enemy_f);
	else if (enemy->direction == 'B')
		enemy_animation_utils(enemy, game->img->enemy_b);
	else if (enemy->direction == 'L')
		enemy_animation_utils(enemy, game->img->enemy_l);
	else if (enemy->direction == 'R')
		enemy_animation_utils(enemy, game->img->enemy_r);
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
