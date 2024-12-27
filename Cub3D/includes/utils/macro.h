/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macro.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:49:25 by ytop              #+#    #+#             */
/*   Updated: 2024/12/27 17:04:23 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACRO_H
# define MACRO_H

# if defined(__linux__)
#  define A_KEY			97
#  define S_KEY			115
#  define D_KEY			100
#  define W_KEY			119
#  define Y_KEY			121
#  define M_KEY			109
#  define ESC_KEY		65307
#  define LEFT_KEY		65361
#  define RIGHT_KEY		65363
#  define SHIFT_KEY		65505
#  define SPACE_KEY		32
#  define ONE_KEY		49
#  define TWO_KEY		50
# else
#  define A_KEY			0
#  define S_KEY			1
#  define D_KEY			2
#  define W_KEY			13
#  define Y_KEY			16
#  define M_KEY			46
#  define ESC_KEY		53
#  define LEFT_KEY		123
#  define RIGHT_KEY		124
#  define SHIFT_KEY		257
#  define SPACE_KEY		49
#  define ONE_KEY		18
#  define TWO_KEY		19
# endif

# define C_E		"\033[0m"
# define C_R		"\033[31m"
# define C_G		"\033[32m"
# define C_Y		"\033[33m"

# define H_B		0x00000000
# define H_W		0x00FFFFFF
# define H_Y		0x00FFFF00
# define H_R		0x00FF0000
# define H_G		0x00D1DDDE

# define PI			3.14159265

# define WIN_W		1280
# define WIN_H		720

# define SPEED		0.050
# define ROTATE		0.050

# define DESTROY	17

# define P_COUNT	1

# define TRUE		1
# define FALSE		0

# define FAILURE	1
# define SUCCESS	0

# define NORTH		'N'
# define SOUTH		'S'
# define WEST		'W'
# define EAST		'E'

# define WALL		'1'
# define FLOOR		'0'

# define FOV		60.00
# define SEV		64.00
#endif
