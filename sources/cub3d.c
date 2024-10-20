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
	static int		init;

	if (!init)
	{
		ft_bzero(&game, sizeof(t_game));
		init = TRUE;
		game.map = ft_calloc(1, sizeof(t_map));
	}
	return (&game);
}

int	main(int argc, char *argv[])
{
	if (argc != 2)
		error_controller("Usage: ./cub3d <map.cub>", NULL);
	else
	{
		exten_controller(argv[1]);
		get_game();
	}
	file_controller(argv[1]);
	return (EXIT_SUCCESS);
}
