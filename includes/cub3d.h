/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:59:38 by ytop              #+#    #+#             */
/*   Updated: 2024/12/27 16:26:17 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./other/struct.h"
# include "./other/macro.h"

# include "./utils/libft.h"

# define WIN_NAME	"Cub3D"

# define WIN_W		1280
# define WIN_H		720

# define SPEED		0.050
# define ROTATE		0.050

typedef struct s_wall
{
	double		contact;
	double		height;
	double		s_pos;
	double		e_pos;
	int			direct;
}				t_wall;

typedef struct s_ray
{
	char		*hit;
	int			axis;
	double		dist;
	t_wall		wall;
	t_vect		src;
	t_vect		dir;
	t_vect		step;
	t_vect		side;
	t_vect		delta;
	t_vect		plane;
}				t_ray;

typedef struct s_img
{
	int			rgb[2][3];
	int			hex[2];
	t_data		dir[4];
	t_data		frame;
}				t_img;

typedef struct s_player
{
	char		direction;
	int			rota[2];
	int			move[2];
	double		speed;
	double		theta;
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
	t_size		size;
	t_vect		scale;
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

double			deg_to_rad(double degree);
double			rad_to_deg(double radian);

double			grid_to_ct(double pos, double scale);

/*----------------------UTIL  CONTROLLER----------------------*/

t_data			add_image(char *path, t_size size);

int				open_file(char *path);

int				wtspace_check(char c);

char			*wtspace_trim(char *str);

/*------------------------------------------------------------*/

void			render_frame(t_ray *ray, int x);

/*------------------------------------------------------------*/

char			**copy_array(char **array, int size);

/*------------------------------------------------------------*/

int				raycast(void);

/*------------------------------------------------------------*/
#endif
