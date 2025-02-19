/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 12:29:56 by ytop              #+#    #+#             */
/*   Updated: 2025/02/19 20:16:48 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "./other/struct.h"
# include "./other/macro.h"

# include "./bonus/audio.h"

# include "./utils/libft.h"

# include <pthread.h>

# define WIN_NAME		"Cub3D"

# define KNIFE_TAKE		"./assets/textures/gun/knife/take/frame"
# define KNIFE_IDLE		"./assets/textures/gun/knife/idle/frame"

# define VANDAL_TAKE	"./assets/textures/gun/vandal/take/frame"
# define VANDAL_IDLE	"./assets/textures/gun/vandal/idle/frame"
# define VANDAL_FIRE	"./assets/textures/gun/vandal/fire/frame"
# define VANDAL_SKIN	"./assets/textures/gun/vandal/skin/frame"

# define QSKILL_TAKE	"./assets/textures/char/reyna/q/take/frame"
# define QSKILL_IDLE	"./assets/textures/char/reyna/q/idle/frame"
# define QSKILL_FIRE	"./assets/textures/char/reyna/q/fire/frame"

# define RSKILL_FIRE	"./assets/textures/char/reyna/r/fire/frame"

# define DOOR_PATH		"./assets/textures/env/door/frame"
# define DOOR			'D'

# define TAKE			0
# define IDLE			1
# define FIRE			2
# define SKIN			3

# define MOUSE_SENS		0.1f

typedef struct s_gun
{
	int		ammo;
	int		total;
	int		range;
	int		reload;
	int		damage;
}			t_gun;

typedef struct s_anim
{
	t_data		*frames;
	t_data		*frame;
	int			total;
	int			index;
	int			delay;
	int			play;
	int			loop;
	int			counter;
}				t_anim;

typedef struct s_door
{
	t_anim	anim;
	int		coll;
	int		open;
	int		close;
	int		state;
}			t_door;

typedef struct s_slot
{
	int			index;
	t_anim		*curr;
	t_anim		*take;
	t_anim		*idle;
	t_anim		*skin;
	t_anim		*fire;
	t_gun		*gun;
}			t_slot;

typedef struct s_img
{
	t_anim		*next_anim;
	char		*paths[6];
	int			rgb[2][3];
	int			hex[2];
	t_data		dir[4];
	t_data		crossh;
	t_data		ground;
	t_data		minimap;
	t_data		bgframe;
	t_anim		knife[4];
	t_anim		vandal[4];
	t_anim		qskill[4];
	t_anim		rskill[4];
}				t_img;

typedef struct s_sound
{
	pthread_t	thread;
	char		*path;
	int			play;
	int			loop;
	int			volume;
}				t_sound;

typedef struct s_player
{
	char		direction;
	int			move[2];
	int			rota[2];
	int			attack;
	int			mctrl;
	double		speed;
	double		theta;
	t_sound		sound;
	t_vect		pos;
	t_vect		axis;
	t_vect		plane;
	t_slot		*slot;
	t_slot		slots[4];
}				t_player;

typedef struct s_count
{
	int			door;
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
	t_sound		sound;
	t_count		count;
	t_door		*door;
	t_img		*img;
	t_map		*map;
	void		*mlx;
	void		*win;
	char		sfps[8];
	t_ray		rays[WIN_W];
}				t_game;

t_game			*get_game(void);

int				exit_game(t_game *game);

/*----------------------ERROR CONTROLLER----------------------*/

void			exten_controller(char *path);

void			error_controller(char *message, void *pointer);

/*----------------------INPUT CONTROLLER----------------------*/

int				update_position(void);

int				key_press_handler(int key, t_game *game);

int				key_relse_handler(int key, t_game *game);

int				mouse_moves_handler(int x, int y);

int				mouse_press_handler(int button, int x, int y);

int				mouse_relse_handler(int button, int x, int y);

/*----------------------COLOR CONTROLLER----------------------*/

unsigned int	rgb_to_hexa(int r, int g, int b);

unsigned int	pixel_color(t_data img, int x, int y);

void			mlx_image_put(t_data img, int x, int y, unsigned int color);

/*----------------------FILE  CONTROLLER----------------------*/

int				path_control(void);

void			files_controller(char *path);

/*----------------------INIT  CONTROLLER----------------------*/

void			init_game(void);

/*----------------------MATH  CONTROLLER----------------------*/

t_size			tc_size(t_vect vect);
t_vect			tc_vect(t_size size);

double			deg_to_rad(double degree);
double			rad_to_deg(double radian);

double			grid_to_ct(double pos, double scale);

/*----------------------UTIL  CONTROLLER----------------------*/

t_data			add_image(char *path, t_size size);

int				open_file(char *path);

/*------------------------------------------------------------*/

int				wtspace_check(char c);

char			*wtspace_trim(char *str);

/*----------------------ANIM  CONTROLLER----------------------*/

void			input_animation(int key);

void			updt_animation(t_anim *anim, int reverse);

void			swap_animation(t_anim *anim, t_anim *new);

void			init_animation(t_anim *anim, t_size range, int delay, char *path);

/*----------------------DRAW  CONTROLLER----------------------*/

void			draw_rect(t_data data, t_vect center, t_vect size, int color);

int				draw_circ(t_data data, t_vect center, t_vect radius, int color);

/*------------------------------------------------------------*/

void			render_frame(t_ray *ray, int x);

int				image_filter(int index, int color, char filter, int limit);

/*------------------------------------------------------------*/

int				raycast(void);

void			minimap(void);

/*------------------------------------------------------------*/

void			init_slot(void);

/*------------------------------------------------------------*/

char			**copy_array(char **array, int size);

/*------------------------------------------------------------*/
#endif