/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:59:18 by ytop              #+#    #+#             */
/*   Updated: 2025/03/07 17:54:04 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_game	*get_game(void)
{
	static t_game	game;
	static int		init;

	if (!init)
	{
		ft_bzero(&game, sizeof(t_game));
		init = TRUE;
		game.map = ft_calloc(1, sizeof(t_map));
		error_controller("Failed to allocate memory.", game.map);
		game.img = ft_calloc(1, sizeof(t_img));
		error_controller("Failed to allocate memory.", game.img);
		game.grp = ft_calloc(1, sizeof(t_grp));
		error_controller("Failed to allocate memory.", game.grp);
	}
	return (&game);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		error_controller("Usage: ./cub3d <map.cub>", NULL);
	}
	else
	{
		get_game();
		argv++;
		exten_controller(*argv);
		files_controller(*argv);
	}
	return (init_game(), EXIT_SUCCESS);
}

//argv += arg_controller(argv);
