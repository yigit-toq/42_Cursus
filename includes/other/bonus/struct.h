/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:09:54 by ytop              #+#    #+#             */
/*   Updated: 2025/03/07 17:46:17 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "./macro.h"

# include <pthread.h>

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

typedef struct s_gun
{
	int			ammo;
	int			total;
	int			range;
	int			reload;
	int			damage;
}				t_gun;

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
	int			index;
	t_anim		*curr;
	t_anim		*take;
	t_anim		*idle;
	t_anim		*skin;
	t_anim		*fire;
	t_gun		*gun;
}				t_slot;

typedef struct s_door
{
	t_anim		anim;
	t_vect		coor;
	int			state;
	int			filter;
}				t_door;

typedef struct s_enmy
{
	t_vect		pos;
	t_anim		anim;
	double		dist;
}				t_enmy;

typedef struct s_objs
{
	double		contact;
	double		height;
	double		s_pos;
	double		e_pos;
	double		dist;
	int			coll;
	int			direct;
}				t_objs;

typedef struct s_ray
{
	char		*hit;
	int			axis;
	int			enmy;
	t_objs		wall;
	t_objs		door;
	t_vect		src;
	t_vect		dir;
	t_vect		step;
	t_vect		side;
	t_vect		delta;
	t_vect		plane;
}				t_ray;

typedef struct s_img
{
	t_anim		*next_anim;
	char		*paths[10];
	int			hex[2];
	int			rgb[2][3];
	t_data		direct[4];
	t_data		crossh;
	t_data		ground;
	t_data		minimap;
	t_data		bgframe;
	t_anim		knife[4];
	t_anim		vandal[4];
	t_anim		qskill[4];
	t_anim		rskill[4];
	t_data		skybox[4];
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
	double		velocity;
}				t_player;

typedef struct s_count
{
	int			door;
	int			wall;
	int			enmy;
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

typedef struct s_grp
{
	t_enmy		*enmy;
	t_door		*door;
	t_door		*curr;
	int			index;
}				t_grp;

typedef struct s_game
{
	t_player	player;
	t_sound		sound;
	t_count		count;
	t_img		*img;
	t_map		*map;
	t_grp		*grp;
	void		*mlx;
	void		*win;
	char		sfps[8];
	t_ray		rays[WIN_W];
}				t_game;
#endif
