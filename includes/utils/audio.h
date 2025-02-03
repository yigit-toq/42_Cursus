/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:01:47 by ytop              #+#    #+#             */
/*   Updated: 2024/12/24 23:01:47 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUDIO_H
# define AUDIO_H

# include <SDL2/SDL.h>

typedef struct s_audio
{
	Uint8	*audio_pos;
	Uint32	audio_len;
}			t_audio;

int	play_sound(char *file_path);

#endif
