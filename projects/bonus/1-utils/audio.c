/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 19:54:18 by ytop              #+#    #+#             */
/*   Updated: 2025/03/07 16:59:23 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

#include "./bonus/audio.h"

static void	audio_callback(void *userdata, Uint8 *stream, Uint32 len)
{
	t_audio	*audio;

	audio = (t_audio *)userdata;
	if (audio->audio_len == 0)
	{
		return ;
	}
	if (len > audio->audio_len)
		len = audio->audio_len;
	SDL_memcpy(stream, audio->audio_pos, len);
	audio->audio_pos += len;
	audio->audio_len -= len;
}

int	play_sound(char *file_path)
{
	t_audio			wav_sound;
	SDL_AudioSpec	wav_spectr;
	Uint32			wav_length;
	Uint8			*wav_buffer;

	if (SDL_Init(SDL_INIT_AUDIO) < 0)
		error_controller((char *)SDL_GetError(), NULL);
	if (SDL_LoadWAV(file_path, &wav_spectr, &wav_buffer, &wav_length) == NULL)
	{
		SDL_Quit();
		error_controller((char *)SDL_GetError(), NULL);
	}
	wav_sound.audio_pos = wav_buffer;
	wav_sound.audio_len = wav_length;
	wav_spectr.userdata = &wav_sound;
	wav_spectr.callback = (SDL_AudioCallback)audio_callback;
	if (SDL_OpenAudio(&wav_spectr, NULL) < 0)
	{
		SDL_Quit();
		error_controller((char *)SDL_GetError(), NULL);
	}
	SDL_PauseAudio(0);
	while (wav_sound.audio_len > 0)
		SDL_Delay(100);
	return (SDL_CloseAudio(), SDL_FreeWAV(wav_buffer), SDL_Quit(), SUCCESS);
}

static void	*audio_control(t_sound *sound)
{
	while (sound->loop)
	{
		play_sound(sound->path);
	}
	return (NULL);
}

void	init_sound(t_sound *sound, char *path, int loop)
{
	sound->path = path;
	sound->loop = loop;
	if (pthread_create(&sound->thread, NULL, (void *)audio_control, sound) == 0)
	{
		pthread_detach(sound->thread);
	}
	else
	{
		error_controller("Failed to create thread.", NULL);
	}
}
