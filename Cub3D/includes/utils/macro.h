/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macro.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:49:25 by ytop              #+#    #+#             */
/*   Updated: 2024/12/17 15:26:22 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACRO_H
# define MACRO_H

# if defined(__linux__)
#  define A			97
#  define S			115
#  define D			100
#  define W			119
#  define Y			121
#  define M			109
#  define ESC		65307
#  define LEFT		65361
#  define RIGHT		65363
#  define SPACE		32
# else
#  define A			0
#  define S			1
#  define D			2
#  define W			13
#  define Y			16
#  define M			46
#  define ESC		53
#  define LEFT		123
#  define RIGHT		124
#  define SPACE		49
# endif

# define C_E		"\033[0m"
# define C_R		"\033[31m"
# define C_G		"\033[32m"
# define C_Y		"\033[33m"

# define H_B		0x00000000
# define H_W		0x00FFFFFF
# define H_Y		0x00FFFF00
# define H_R		0x00FF0000

# define PI			3.14159265


# define WIN_W		1280
# define WIN_H		720

# define SPEED		0.10
# define ROTATE		0.08

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
