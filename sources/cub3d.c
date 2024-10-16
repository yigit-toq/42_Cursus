/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:59:18 by ytop              #+#    #+#             */
/*   Updated: 2024/10/16 18:23:12 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_game	*get_game(void)
{
	static t_game	game;

	return (&game);
}

int	main(int argc, char *argv[])
{
	t_game	*game;

	game = get_game();
	if (argc != 2)
	{
		ft_dprintf(2, RED "Error\n" END);
		ft_dprintf(2, YEL "Usage: %s <map.cub>\n" END, argv[0]);
		return (EXIT_FAILURE);
	}
	extension_controller(argv[1]);
	return (EXIT_SUCCESS);
}
