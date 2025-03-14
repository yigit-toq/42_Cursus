/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 00:36:00 by ytop              #+#    #+#             */
/*   Updated: 2025/03/14 16:34:14 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

#include <math.h>

double	grid_to_ct(double pos, double scale)
{
	return (pos * scale + (scale / 2));
}

double	deg_to_rad(double degree)
{
	return (degree * (PI / 180));
}

double	rad_to_deg(double radian)
{
	return (radian * (180 / PI));
}

t_size	tc_size(t_vect vect)
{
	t_size	size;

	size.x = (int)vect.x;
	size.y = (int)vect.y;
	return (size);
}

t_vect	tc_vect(t_size size)
{
	t_vect	vect;

	vect.x = (double)size.x;
	vect.y = (double)size.y;
	return (vect);
}

double	calcul_dista(t_vect vect1, t_vect vect2)
{
	t_vect	dist;

	dist.x = vect1.x - vect2.x;
	dist.y = vect1.y - vect2.y;
	return (sqrt(dist.x * dist.x + dist.y * dist.y));
}

double	vector_angle(t_vect vect1, t_vect vect2)
{
	double	dot_product;
	t_vect	magnitude;

	dot_product = vect1.x * vect2.x + vect1.y * vect2.y;
	magnitude.x = sqrt(vect1.x * vect1.x + vect1.y * vect1.y);
	magnitude.y = sqrt(vect2.x * vect2.x + vect2.y * vect2.y);
	return (acos(dot_product / (magnitude.x * magnitude.y)));
}
