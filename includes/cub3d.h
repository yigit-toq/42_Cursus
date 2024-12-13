/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:59:38 by ytop              #+#    #+#             */
/*   Updated: 2024/12/13 19:03:52 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libraries/minilibx/mlx.h"

# include "./utils/libft.h"

# include <sys/time.h>

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
# define H_Y			0x00FFFF00
# define H_R			0x00FF0000
# define H_G			0x0000FF00

# define PI				3.14159265

# define NAME			"Cub3D"

# define FOV			60.0
# define INCREMENT		60.0

# define WIN_W			1000
# define WIN_H			600

# define MAX_SPEED		1.0

# define SPEED			0.1
# define ROTATE			0.1
# define FRICTION		0.1

# define DESTROY		17

# define P_COUNT		1

# define TRUE			1
# define FALSE			0

# define FAILURE		1
# define SUCCESS		0

# define MAX_PATH		4

# define NORTH			'N'
# define SOUTH			'S'
# define WEST			'W'
# define EAST			'E'

# define WALL			'1'
# define FLOOR			'0'

typedef struct s_coord
{
	double		x;
	double		y;
}				t_coord;

typedef struct s_size
{
	int			x;
	int			y;
}				t_size;

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

typedef struct s_data
{
	t_coord		size;
	void		*img;
	char		*addr;
	int			bit_pp;
	int			endian;
	int			length;
	int			w_s;
	int			h_s;
}				t_data;

typedef struct s_img
{
	int			hex[2];
	int			colors[2][3];
	t_data		dir_symbl[4];
	t_data		minimap;
	t_data		frame;
}				t_img;

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
	t_coord		scale;
	t_size		size;
}				t_map;

typedef struct s_game
{
	t_player	player;
	t_count		count;
	t_img		*img;
	t_map		*map;
	void		*mlx;
	void		*win;
	t_ray		*rays;
}				t_game;

//int			save;
//int			load;

t_game			*get_game(void);

void			init_game(void);

void			minimap_loop(void);

// Error Controller

void			exten_controller(char *path);

void			files_controller(char *path);

void			error_controller(char *message, void *pointer);

// Utils Controller

int				rgb_to_hex(int red, int green, int blue);

int				path_control(void);

int				open_file(char *path);

t_size			typecast_size(t_coord coord);

t_data			add_image(char *path, int create, int w, int h);

double			grid_to_center(double pos, double scale, double pivot);

double			center_to_grid(double pos, double scale, double pivot);

void			mlx_image_put(t_data img, int x, int y, unsigned int color);

unsigned int	get_pixel_color(t_data img, int x, int y);

// Input Controller

int				exit_game(t_game *game);

int				update_position(void);

int				key_press_handler(int key, t_game *game);

int				key_release_handler(int key, t_game *game);

// Render Controller

int				draw_circle(t_data data, t_coord center, t_coord radius, int color);

void			draw_rectangle(t_data data, t_coord center, t_coord size, int color);

void			draw_line(t_data data, t_coord pos, double theta, double range, int color);

void			draw_rays(t_data data, t_coord pos, double theta, int color);

// Other Controller

int				wspace_check(char c);

char			*wspace_trim(char *str);

// Raycasting Controller

int				raycast(void);
#endif
