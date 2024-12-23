/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 12:29:56 by ytop              #+#    #+#             */
/*   Updated: 2024/12/23 14:57:40 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "../libraries/minilibx/mlx.h"

# include "./utils/libft.h"
# include "./utils/macro.h"

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>

# define MAX_PATH		4

# define WIN_NAME		"Cub3D Bonus"

# define GUN_PATH		"./assets/textures/character/frame"

# define CROSS_PATH		"./assets/textures/crosshair.xpm"

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
	double		contact;
	double		height;
	double		s_pos;
	double		e_pos;
}				t_wall;

typedef struct s_ray
{
	char		*hit;
	double		dist;
	t_wall		wall;
	t_vect		src;
	t_vect		dir;
	t_vect		step;
	t_vect		side;
	t_vect		delta;
	t_vect		plane;
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

typedef struct s_anim
{
	t_data		*frames;
	t_data		*frame;
	char		*path;
	int			total;
	int			index;
	int			delay;
	int			play;
	int			loop;
	int			counter;
}				t_anim;

typedef struct s_img
{
	int			rgb_color[2][3];
	int			hex_color[2];
	t_data		dir_symbl[4];
	t_data		minimap;
	t_data		bgframe;
	t_data		cross;
	t_anim		weapon[2];
}				t_img;

typedef struct s_player
{
	char		direction;
	int			move[2];
	double		speed;
	double		theta;
	t_anim		*anim;
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
	t_vect		pivot;
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

double			grid_to_center(double pos, double scale);

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

void			init_frame(t_data *frame, char *path, int *range);

void			init_animation(t_anim *anim, int *range, int delay, char *path);

void			update_animation(t_anim	*anim);
#endif