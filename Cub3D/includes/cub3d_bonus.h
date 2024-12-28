/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 12:29:56 by ytop              #+#    #+#             */
/*   Updated: 2024/12/27 17:41:19 by ytop             ###   ########.fr       */
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

# define KNF_IDLE_PATH	"./assets/textures/weapons/knife/idle/frame"
# define KNF_TAKE_PATH	"./assets/textures/weapons/knife/take/frame"

# define GUN_IDLE_PATH	"./assets/textures/weapons/vandal/idle/frame"
# define GUN_SKIN_PATH	"./assets/textures/weapons/vandal/skin/frame"

# define QSK_TAKE_PATH	"./assets/textures/character/reyna/q/take/frame"
# define QSK_IDLE_PATH	"./assets/textures/character/reyna/q/idle/frame"
# define QSK_PUSH_PATH	"./assets/textures/character/reyna/q/push/frame"

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

typedef struct s_slot
{
	int		index;
	t_anim	*curr;
	t_anim	*take;
	t_anim	*idle;
	t_anim	*skin;
	t_anim	*fire;
}			t_slot;

typedef struct s_gun
{
	int		ammo;
	int		total;
	int		range;
	int		reload;
	int		attack;
	int		damage;
}			t_gun;

typedef struct s_img
{
	int			rgb[2][3];
	int			hex[2];
	t_data		dir[4];
	t_data		bgframe;
	t_data		minimap;
	t_data		cross;
	t_anim		knife[4];
	t_anim		vandal[4];
	t_anim		qskill[4];
}				t_img;

typedef struct s_player
{
	char		direction;
	int			rotate[2];
	int			move[2];
	double		speed;
	double		theta;
	t_vect		pos;
	t_vect		axis;
	t_vect		plane;
	t_slot		*slot;
	t_slot		slots[3];
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

int				exit_game(t_game *game);

/*----------------------ERROR CONTROLLER----------------------*/

void			exten_controller(char *path);

void			error_controller(char *message, void *pointer);

/*----------------------INPUT CONTROLLER----------------------*/

int				update_position(void);

int				key_press_handler(int key, t_game *game);

int				key_release_handler(int key, t_game *game);

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

int				wtspace_check(char c);

char			*wtspace_trim(char *str);

/*----------------------ANIM  CONTROLLER----------------------*/

void			init_frame(t_data *frame, char *path, int *range);

void			swap_animation(t_anim *c_anim, t_anim *n_anim);

void			init_animation(t_anim *anim, int *range, int delay, char *path);

void			update_animation(t_anim	*anim);

/*----------------------DRAW  CONTROLLER----------------------*/

int				draw_circ(t_data data, t_vect center, t_vect radius, int color);

void			draw_rect(t_data data, t_vect center, t_vect size, int color);

/*------------------------------------------------------------*/

void			render_frame(t_ray *ray, int x);

/*------------------------------------------------------------*/

int				raycast(void);

void			minimap(void);

/*------------------------------------------------------------*/

int				image_filter(int index, int color, char filter, int limit);

/*------------------------------------------------------------*/
#endif
