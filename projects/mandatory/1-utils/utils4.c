/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 22:47:50 by ytop              #+#    #+#             */
/*   Updated: 2025/03/14 17:05:54 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_mandatory.h"

char	**copy_array(char **array, int size)
{
	char	**copy;
	int		i;

	i = 0;
	copy = ft_calloc(size + 1, sizeof(char *));
	error_controller("Failed to allocate memory.", copy);
	while (array[i])
	{
		copy[i] = ft_strdup(array[i]);
		error_controller("Failed to allocate memory.", copy[i]);
		i++;
	}
	return (copy);
}

int	wall_check(t_vect pos)
{
	t_game	*game;
	int		cell;

	game = get_game();
	cell = game->map->map[(int)grid_to_ct(pos.y, 1)][(int)grid_to_ct(pos.x, 1)];
	if (cell == WALL || cell == SPACE || cell == '\n' || cell == '\0')
	{
		return (FAILURE);
	}
	else
	{
		game->player.pos = pos;
		return (SUCCESS);
	}
}
