/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macro.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:49:25 by ytop              #+#    #+#             */
/*   Updated: 2025/01/16 19:17:20 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACRO_H
# define MACRO_H

# if defined(__linux__)
#  define A_KEY			97
#  define S_KEY			115
#  define D_KEY			100
#  define W_KEY			119
#  define Q_KEY			113
#  define R_KEY			114
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
#  define Q_KEY			12
#  define R_KEY			15
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

# define C_R			"\033[31m"
# define C_G			"\033[32m"
# define C_Y			"\033[33m"
# define C_B			"\033[34m"
# define END			"\033[0m"

# define CONST			64

# define DESTROY		17

# define P_COUNT		1
# define E_COUNT		1

# define SUCCESS		1
# define FAILURE		0

# define PLAYER			'P'
# define COLL			'C'
# define EXIT			'E'

# define WALL			'1'
# define FLOOR			'0'

# define VISITED		'V'

#endif
