/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:59:18 by ytop              #+#    #+#             */
/*   Updated: 2024/10/16 17:22:48 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_game	*get_game(void)
{
	static t_game	game;

	return (&game);
}

int	main(void)
{
	t_game	*game;

	game = get_game();
	return (EXIT_SUCCESS);
}
