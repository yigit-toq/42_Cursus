/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macro.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:49:25 by ytop              #+#    #+#             */
/*   Updated: 2025/01/24 12:22:10 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACRO_H
# define MACRO_H

# if defined(__linux__)
#  define A_KEY			97
#  define S_KEY			115
#  define D_KEY			100
#  define W_KEY			119

#  define C_KEY			99
#  define Q_KEY			113
#  define E_KEY			101
#  define X_KEY			120

#  define R_KEY			114

#  define Y_KEY			121
#  define P_KEY			112
#  define M_KEY			109

#  define ESC_KEY		65307
#  define L_ARR_KEY		65361
#  define R_ARR_KEY		65363
#  define SHIFT_KEY		65505
#  define SPACE_KEY		32

#  define ONE_KEY		49
#  define TWO_KEY		50

#  define L_CLICK		1
#  define R_CLICK		3
#  define SCRL_UP		4
#  define SCRL_DW		5

#  define NUM_STR		49
# else
#  define A_KEY			0
#  define S_KEY			1
#  define D_KEY			2
#  define W_KEY			13

#  define C_KEY			8
#  define Q_KEY			12
#  define E_KEY			14
#  define X_KEY			7

#  define R_KEY			15

#  define Y_KEY			16
#  define P_KEY			35
#  define M_KEY			46

#  define ESC_KEY		53
#  define L_ARR_KEY		123
#  define R_ARR_KEY		124
#  define SHIFT_KEY		257
#  define SPACE_KEY		49

#  define ONE_KEY		18
#  define TWO_KEY		19

#  define L_CLICK		1
#  define R_CLICK		2
#  define SCRL_UP		4
#  define SCRL_DW		5

#  define NUM_STR		18
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
# define SPACE		' '

# define VISITED	'V'

# define FOV		60.00
# define SEV		64.00

# define DIR_SIZE   4
#endif
