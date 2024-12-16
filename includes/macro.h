/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macro.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:49:25 by ytop              #+#    #+#             */
/*   Updated: 2024/12/16 13:51:12 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACRO_H
# define MACRO_H

# if defined(__linux__)
#  define A		97
#  define S		115
#  define D		100
#  define W		119
#  define M		109
#  define ESC	65307
#  define LEFT	65361
#  define RIGHT	65363
#  define SPACE	32
# else
#  define A		0
#  define S		1
#  define D		2
#  define W		13
#  define M		46
#  define ESC		53
#  define LEFT	123
#  define RIGHT	124
#  define SPACE	49
# endif

#endif
