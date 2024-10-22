/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:59:38 by ytop              #+#    #+#             */
/*   Updated: 2024/10/22 15:01:59 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libraries/minilibx/mlx.h"

# include "./utils/libft.h"

# include <unistd.h>
# include <fcntl.h>

# define C_Y		"\033[33m"
# define C_G		"\033[32m"
# define C_R		"\033[31m"
# define C_E		"\033[0m"

# define H_B		0x00000000
# define H_W		0x00FFFFFF
# define H_R		0x00FF0000

# define NAME		"Cub3D"

# define ESC		65307
# define W			119
# define A			97
# define S			115
# define D			100
# define M			109

# define P_COUNT	1

# define SUCCESS	1
# define FAILURE	0

# define TRUE		1
# define FALSE		0

# define SIZE		16

# define NORTH		'N'
# define SOUTH		'S'
# define WEST		'W'
# define EAST		'E'

# define WALL		'1'
# define FLOOR		'0'

typedef struct s_img
{
	int			width;
	int			height;
	int			colors[2][3];
	void		*direction[4];
}				t_img;

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
	int			map_hl;
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
	t_player	player;
	t_count		count;
	t_img		*img;
	t_map		*map;
	void		*mlx;
	void		*win;
}				t_game;

t_game	*get_game(void);

void	init_game(void);

// File Functions

void	path_control(void);

void	files_controller(char *path);

// Error Functions

void	exten_controller(char *path);

void	error_controller(char *message, void *pointer);

// Utils Functions

int		open_file(char *path);

int		wspace_check(char c);

void	*xpm_check(char *file);

char	*wspace_trim(char *str);
#endif
