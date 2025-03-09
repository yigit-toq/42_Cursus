/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macro.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:49:25 by ytop              #+#    #+#             */
/*   Updated: 2025/03/07 18:38:43 by ytop             ###   ########.fr       */
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

# define WIN			"Cub3D"

# define ENMY_PATH		"./assets/textures/char/enemy/frame"
# define ENMY			'A'

# define DOOR1_PATH		"./assets/textures/env/door/1/frame"
# define DOOR2_PATH		"./assets/textures/env/door/2/frame"
# define DOOR			'D'

# define KNIFE_TAKE		"./assets/textures/gun/knife/take/frame"
# define KNIFE_IDLE		"./assets/textures/gun/knife/idle/frame"

# define VANDAL_TAKE	"./assets/textures/gun/vandal/take/frame"
# define VANDAL_IDLE	"./assets/textures/gun/vandal/idle/frame"
# define VANDAL_FIRE	"./assets/textures/gun/vandal/fire/frame"
# define VANDAL_SKIN	"./assets/textures/gun/vandal/skin/frame"

# define QSKILL_TAKE	"./assets/textures/char/reyna/q/take/frame"
# define QSKILL_IDLE	"./assets/textures/char/reyna/q/idle/frame"
# define QSKILL_FIRE	"./assets/textures/char/reyna/q/fire/frame"

# define RSKILL_FIRE	"./assets/textures/char/reyna/r/fire/frame"

# define TAKE			0
# define IDLE			1
# define FIRE			2
# define SKIN			3

# define DELAY			6

# define WIN_W			640
# define WIN_H			360

# define TOTAL			342

# define C_E			"\033[0m"
# define C_R			"\033[31m"
# define C_G			"\033[32m"
# define C_Y			"\033[33m"

# define H_B			0x00000000
# define H_R			0x00FF0000
# define H_Y			0x00FFFF00
# define H_W			0x00FFFFFF
# define H_P			0x00FF00FF
# define H_G			0x00D1DDDE

# define PI				3.14159265

# define MOUSE_SENS		0.050

# define ROTATE			0.050
# define SPEED			0.025

# define DESTROY		17

# define P_COUNT		1

# define TRUE			1
# define FALSE			0

# define FAILURE		1
# define SUCCESS		0

# define VISITED		'V'

# define NORTH			'N'
# define SOUTH			'S'
# define WEST			'W'
# define EAST			'E'

# define WALL			'1'
# define FLOOR			'0'
# define SPACE			' '

# define FOV			60.00
# define SEV			64.00

# define DIR			4

# define MINI           8
#endif
