/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:59:38 by ytop              #+#    #+#             */
/*   Updated: 2024/12/18 17:41:43 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libraries/minilibx/mlx.h"

# include "./utils/libft.h"

# include "./macro.h"

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

# define PI				3.14159265

# define NAME			"Cub3D"

# define WIN_W			1280
# define WIN_H			720

# define SPEED			0.10
# define ROTATE			0.08

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

# define FOV			60.00
# define SEV			64.00

typedef struct s_size
{
	int			x;
	int			y;
}				t_size;

typedef struct s_vect
{
	double		x;
	double		y;
}				t_vect;

typedef struct s_wall
{
	double		s_pos;
	double		e_pos;
	double		height;
}				t_wall;

typedef struct s_ray
{
	double		dist;
	t_wall		wall;
	t_vect		pos;
	t_vect		dir;
	char		hit;
}				t_ray;

typedef struct s_data
{
	t_vect		size;
	void		*img;
	char		*add;
	int			bit_pp;
	int			endian;
	int			length;
	int			w_s;
	int			h_s;
}				t_data;

typedef struct s_img
{
	int			rgb_color[2][3];
	int			hex_color[2];
	t_data		dir_symbl[4];
	t_data		minimap;
	t_data		frame;
	t_data		cross;
}				t_img;

typedef struct s_player
{
	char		direction;
	int			move[2];
	double		speed;
	double		theta;
	t_vect		axis;
	t_vect		plane;
	t_vect		position;
}				t_player;

typedef struct s_count
{
	int			wall;
	int			floor;
	int			player;
}				t_count;

typedef struct s_map
{
	int			is_map;
	char		**map;
	t_vect		scale;
	t_size		size;
	t_size		mini;
}				t_map;

typedef struct s_game
{
	t_player	player;
	t_count		count;
	t_img		*img;
	t_map		*map;
	void		*mlx;
	void		*win;
	t_ray		rays[WIN_W];
}				t_game;

t_game			*get_game(void);

void			init_game(void);

// Error Controller

void			exten_controller(char *path);

void			files_controller(char *path);

void			error_controller(char *message, void *pointer);

// Utils Controller

int				rgb_to_hex(int red, int green, int blue);

t_size			tc_size(t_vect vect);

t_vect			tc_vect(t_size size);

t_data			add_image(char *path, t_size size);

void			mlx_image_put(t_data img, int x, int y, unsigned int color);

unsigned int	get_pixel_color(t_data img, int x, int y);

double			grid_to_center(double pos, double scale, double pivot);

double			center_to_grid(double pos, double scale, double pivot);

char			*wtspace_trim(char *str);

int				wspace_check(char c);

int				path_control(void);

int				open_file(char *path);

void			delay(int ms);

// Input Controller

int				update_position(void);

int				exit_game(t_game *game);

int				key_press_handler(int key, t_game *game);

int				key_release_handler(int key, t_game *game);

// Render Controller

void			draw_rectangle(t_data data, t_vect center, t_vect size, int color);

int				draw_circle(t_data data, t_vect center, t_vect radius, int color);

void			draw_rays(t_data data, t_vect pos, double theta, int color);

void			draw_line(t_data data, t_vect pos, double theta, double range, int color);

void			draw_hit(t_data image, t_size start, t_size curr, int color);

// Raycasting Controller

int				raycast(void);

void			minimap_loop(void);

double			deg_to_rad(double degree);

double			rad_to_deg(double radian);
#endif
