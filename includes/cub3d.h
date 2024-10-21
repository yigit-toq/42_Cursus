/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:59:38 by ytop              #+#    #+#             */
/*   Updated: 2024/10/21 15:31:44 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./utils/libft.h"

# define C_Y		"\033[33m"
# define C_G		"\033[32m"
# define C_R		"\033[31m"
# define C_E		"\033[0m"

# define NAME		"Cub3D"

# define KEY_A		0
# define KEY_S		1
# define KEY_D		2

# define P_COUNT	1

# define SUCCESS	1
# define FAILURE	0

# define TRUE		1
# define FALSE		0

# define NORTH		'N'
# define SOUTH		'S'
# define WEST		'W'
# define EAST		'E'

# define WALL		'1'
# define FLOOR		'0'

typedef struct s_texture
{
	char		*direction[4];
	int			colors[2][3];
}				t_texture;

typedef struct s_player
{
	int			x;
	int			y;
	char		dir;
}				t_player;

typedef struct s_count
{
	int			wall;
	int			floor;
	int			player;
}				t_count;

typedef struct s_map
{
	int			height;
	int			width;
	char		**map;
}				t_map;

typedef struct s_game
{
	t_texture	texture;
	t_player	player;
	t_count		count;
	t_map		*map;
	void		*mlx;
	void		*win;
}				t_game;

t_game	*get_game(void);

// File Functions

void	file_controller(char *path);

void	path_handler(void);

// Error Functions

void	exten_controller(char *path);

void	error_controller(char *message, void *pointer);

// Utils Functions

char	*wspace_trim(char *line);
#endif
