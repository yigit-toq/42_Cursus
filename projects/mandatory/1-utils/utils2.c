/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 00:03:39 by ytop              #+#    #+#             */
/*   Updated: 2025/03/07 16:54:01 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_mandatory.h"

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
