/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:09:54 by ytop              #+#    #+#             */
/*   Updated: 2024/12/27 16:25:47 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

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
	int			dir;
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
#endif
