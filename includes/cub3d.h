/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:59:38 by ytop              #+#    #+#             */
/*   Updated: 2024/10/16 18:22:49 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./utils/libft.h"

# define YEL		"\033[33m"
# define GRE		"\033[32m"
# define RED		"\033[31m"
# define END		"\033[0m"

# define WIN_NAME	"Cub3D"

# define KEY_A		0
# define KEY_S		1
# define KEY_D		2

# define WALL		'1'
# define FLOOR		'0'

# define NORTH		'N'
# define SOUTH		'S'
# define WEST		'W'
# define EAST		'E'

# define PLAYER_COUNT	1

# define SUCCESS		1
# define FAILURE		0

typedef struct s_player
{
	int			x;
	int			y;
	char		dir;
}				t_player;

typedef struct s_map
{
	int			height;
	int			width;
	char		**map;
}				t_map;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_player	player;
}				t_game;

t_game	*get_game(void);

void	extension_controller(char *path);
#endif
