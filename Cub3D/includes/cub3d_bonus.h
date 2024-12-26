/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 12:29:56 by ytop              #+#    #+#             */
/*   Updated: 2024/12/24 20:12:48 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "./utils/struct.h"
# include "./utils/macro.h"
# include "./utils/audio.h"

# include "./utils/libft.h"

# define WIN_NAME	"Cub3D"

# define MAX_PATH	4

# define CRS_PATH	"./assets/textures/crosshair.xpm"

# define GUN_PATH	"./assets/textures/weapons/vandal/frame"

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
	int			rgb[2][3];
	int			hex[2];
	t_data		dir[4];
	t_data		minimap;
	t_data		bgframe;
	t_data		cross;
	t_anim		weapon[2];
}				t_img;

typedef struct s_player
{
	char		direction;
	int			rotate[2];
	int			move[2];
	double		speed;
	double		theta;
	t_anim		*anim;
	t_vect		pos;
	t_vect		axis;
	t_vect		plane;
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

/*----------------------ERROR CONTROLLER----------------------*/

void			error_controller(char *message, void *pointer);

void			exten_controller(char *path);

/*----------------------INPUT CONTROLLER----------------------*/

int				update_position(void);

int				exit_game(t_game *game);

int				key_press_handler(int key, t_game *game);

int				key_release_handler(int key, t_game *game);

/*----------------------COLOR CONTROLLER----------------------*/

void			mlx_image_put(t_data img, int x, int y, unsigned int color);

unsigned int	pixel_color(t_data img, int x, int y);

unsigned int	rgb_to_hexa(int r, int g, int b);

/*----------------------FILE  CONTROLLER----------------------*/

void			files_controller(char *path);

int				path_control(void);

/*----------------------INIT  CONTROLLER----------------------*/

void			init_game(void);

/*----------------------MATH  CONTROLLER----------------------*/

double			grid_to_ct(double pos, double scale);

double			deg_to_rad(double degree);
double			rad_to_deg(double radian);

t_size			tc_size(t_vect vect);
t_vect			tc_vect(t_size size);

/*----------------------UTIL  CONTROLLER----------------------*/

t_data			add_image(char *path, t_size size);

int				open_file(char *path);

int				wspace_check(char c);

char			*wtspace_trim(char *str);

/*------------------------------------------------------------*/

void			render_frame(t_ray *ray, int x);

/*------------------------------------------------------------*/

int				raycast(void);

/*------------------------------------------------------------*/

void			init_frame(t_data *frame, char *path, int *range);

void			init_animation(t_anim *anim, int *range, int delay, char *path);

void			update_animation(t_anim	*anim);

/*------------------------------------------------------------*/

void			minimap(void);

/*------------------------------------------------------------*/

int				draw_circle(t_data data, t_vect center, t_vect radius, int color);

void			draw_rectangle(t_data data, t_vect center, t_vect size, int color);
#endif
