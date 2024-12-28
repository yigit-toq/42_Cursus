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

# include "./utils/struct.h"
# include "./utils/macro.h"

# include "./utils/libft.h"

# define WIN_NAME	"Cub3D"

# define MAX_PATH	4

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
	int			rotate[2];
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

int				raycast(void);

/*------------------------------------------------------------*/
#endif
