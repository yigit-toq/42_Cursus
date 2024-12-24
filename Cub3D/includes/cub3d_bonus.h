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

# define GUN_PATH	"./assets/textures/character/frame"

# define CROSS_PATH	"./assets/textures/crosshair.xpm"

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
#endif
