/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:09:54 by ytop              #+#    #+#             */
/*   Updated: 2025/03/07 16:25:27 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "./macro.h"

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
#endif
