/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:13:20 by ytop              #+#    #+#             */
/*   Updated: 2024/12/05 16:45:38 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	raycast(void)
{
	t_game	*game;

	game = get_game();
	game->player.plane.x = grid_to_center(game->player.position.x, game->map->scale.x, game->map->pivot.x);
	game->player.plane.y = grid_to_center(game->player.position.y, game->map->scale.y, game->map->pivot.y);
	return (SUCCESS);
}
