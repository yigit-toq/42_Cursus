/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_enemy_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 23:52:50 by ytop              #+#    #+#             */
/*   Updated: 2024/06/11 17:21:08 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long_bonus.h"
#include "../../includes/libft.h"

static void	enemy_movement_control(t_game *game, t_enemy *enemy, char *str);
static void	enemy_movement(t_game *game, t_enemy *enemy, char **map);

void	enemy_init(t_game *game)
{
	t_enemy	**enemy;
	int		index;

	if (!game->count->enemy || game->player->death)
		return ;
	index = 0;
	enemy = ft_calloc(game->count->enemy, sizeof(t_enemy *));
	error_controller(game, 'A', "Malloc not allocated.", enemy);
	while (index < game->count->enemy)
	{
		enemy[index] = ft_calloc(1, sizeof(t_enemy));
		if (!enemy[index])
			error_controller(game, 'A', "Malloc not allocated.", 0);
		index++;
	}
	enemy_finder(enemy, game, 0, 0);
	game->enemy = enemy;
	return ;
}

void	enemy_controller(t_game *game, t_enemy **enemy)
{
	int	i;
	int	x;
	int	y;

	if (!game->count->enemy)
		return ;
	i = 0;
	while (i < game->count->enemy)
	{
		if (!enemy[i]->death)
		{
			x = enemy[i]->t_dir[0];
			y = enemy[i]->t_dir[1];
			enemy_animation(game, enemy[i]);
			enemy_movement(game, enemy[i], game->map->map);
			put_object(game, x, y, enemy[i]->img);
		}
		i++;
	}
	return ;
}

static void	enemy_movement(t_game *game, t_enemy *enemy, char **map)
{
	int	x;
	int	y;

	x = game->dynamite->transform[0];
	y = game->dynamite->transform[1];
	if (enemy->direction == 'F')
		enemy_movement_control(game, enemy, "11");
	else if (enemy->direction == 'B')
		enemy_movement_control(game, enemy, "10");
	else if (enemy->direction == 'L')
		enemy_movement_control(game, enemy, "00");
	else if (enemy->direction == 'R')
		enemy_movement_control(game, enemy, "01");
	if (enemy->m_dir[0] == (x / CONST) && enemy->m_dir[1] == (y / CONST))
	{
		game->dynamite->life_time = 0;
		game->dynamite->frame = 0;
		enemy->death = 1;
	}
	if (map[enemy->m_dir[1]][enemy->m_dir[0]] == PLAYER)
		game->player->death = 1;
}

static void	enemy_movement_utils(t_game *game, t_enemy *enemy, char *str)
{
	int	sign;
	int	i;

	sign = str[1] - 48;
	i = str[0] - 48;
	if (sign)
		enemy->t_dir[i] += ENEMY_SPEED;
	else
		enemy->t_dir[i] -= ENEMY_SPEED;
	if (enemy->t_dir[i] % CONST == 0)
	{
		if (game->map->map[enemy->m_dir[1]][enemy->m_dir[0]] == ENEMY)
			game->map->map[enemy->m_dir[1]][enemy->m_dir[0]] = FLOOR;
		if (sign)
			enemy->m_dir[i]++;
		else
			enemy->m_dir[i]--;
		if (game->map->map[enemy->m_dir[1]][enemy->m_dir[0]] == FLOOR)
			game->map->map[enemy->m_dir[1]][enemy->m_dir[0]] = ENEMY;
	}
	return ;
}

static void	enemy_movement_control(t_game *game, t_enemy *enemy, char *str)
{
	int		value;

	if (str[1] - 48)
		value = 1;
	else
		value = -1;
	if (str[0] - 48)
	{
		if (game->map->map[enemy->m_dir[1] + value][enemy->m_dir[0]] != WALL)
			enemy_movement_utils(game, enemy, str);
		else
			enemy_direction(game, enemy, enemy->m_dir[0], enemy->m_dir[1]);
	}
	else
	{
		if (game->map->map[enemy->m_dir[1]][enemy->m_dir[0] + value] != WALL)
			enemy_movement_utils(game, enemy, str);
		else
			enemy_direction(game, enemy, enemy->m_dir[0], enemy->m_dir[1]);
	}
	return ;
}
