/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:59:38 by ytop              #+#    #+#             */
/*   Updated: 2024/11/27 18:03:01 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libraries/minilibx/mlx.h"

# include "./utils/libft.h"

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>

# define C_E			"\033[0m"
# define C_R			"\033[31m"
# define C_G			"\033[32m"
# define C_Y			"\033[33m"

# define H_B			0x00000000
# define H_W			0x00FFFFFF
# define H_R			0x00FF0000

# define PI				3.14159265

# define NAME			"Cub3D"

# define FOV			60

# define WIDTH			2560
# define HEIGHT			1440

# define MAX_SPEED		1.0

# define SPEED			0.2
# define ROTATE			0.1
# define FRICTION		0.1

# define P_COUNT		1

# define TRUE			1
# define FALSE			0

# define SUCCESS		0
# define FAILURE		1

# define MAX_PATH		4

# define NORTH			'N'
# define SOUTH			'S'
# define WEST			'W'
# define EAST			'E'

# define WALL			'1'
# define FLOOR			'0'

# define DESTROY		17

# define MINIMAP		32

typedef struct s_coord
{
	double		x;
	double		y;
}				t_coord;

typedef struct s_wall
{
	int			end;
	int			start;
	int			height;
}				t_wall;

typedef struct s_ray
{
	double		dist;
	t_wall		wall;
	t_coord		pos;
	t_coord		dir;
	t_coord		side;
	t_coord		step;
	t_coord		delta;
	t_coord		plane;
}				t_ray;

typedef struct s_img
{
	int			w_s;
	int			h_s;
	int			colors[2][3];
	void		*dir_syml[4];
}				t_img;

typedef struct s_data
{
	t_coord		size;
	void		*img;
	char		*addr;
	int			bit_pp;
	int			endian;
	int			length;
}				t_data;

typedef struct s_player
{
	char		direction;
	double		move[2];
	double		speed;
	double		theta;
	t_coord		axis;
	t_coord		plane;
	t_coord		position;
}				t_player;

typedef struct s_count
{
	int			wall;
	int			floor;
	int			player;
}				t_count;

typedef struct s_map
{
	char		**map;
	int			is_map;
	int			height;
	int			width;
	t_coord		size;
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

//int			save;
//int			load;

t_game	*get_game(void);

void	init_game(void);

void	minimap_loop(void);

// Error Controller

void	exten_controller(char *path);

void	files_controller(char *path);

void	error_controller(char *message, void *pointer);

// Utils Controller

int		path_control(void);

int		open_file(char *path);

void	*open_xpm(char *path);

// Input Controller

int		exit_game(t_game *game);

int		update_position(void);

int		key_press_handler(int key, t_game *game);

int		key_release_handler(int key, t_game *game);

// Render Controller

int		draw_circle(t_coord center, t_coord radius, int color);

void	draw_rectangle(t_coord center, t_coord size, int color);

void	draw_line(t_coord pos, double theta, double range, int color);

// Other Controller

int		wspace_check(char c);

char	*wspace_trim(char *str);

// Raycasting Controller

int		raycast(void);

void	draw_ray(t_coord pos, double theta, int color);

#endif
