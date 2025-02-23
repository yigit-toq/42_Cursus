/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 19:54:18 by ytop              #+#    #+#             */
/*   Updated: 2024/12/30 13:42:37 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
	Uint8			*wav_buffer;
	Uint32			wav_length;
	SDL_AudioSpec	wav_spec;
	t_audio			audio;

	if (SDL_Init(SDL_INIT_AUDIO) < 0)
		error_controller((char *)SDL_GetError(), NULL);
	if (SDL_LoadWAV(file_path, &wav_spec, &wav_buffer, &wav_length) == NULL)
	{
		SDL_Quit();
		error_controller((char *)SDL_GetError(), NULL);
	}
	audio.audio_pos = wav_buffer;
	audio.audio_len = wav_length;
	wav_spec.userdata = &audio;
	wav_spec.callback = (SDL_AudioCallback)audio_callback;
	if (SDL_OpenAudio(&wav_spec, NULL) < 0)
	{
		SDL_FreeWAV(wav_buffer);
		SDL_Quit();
		error_controller((char *)SDL_GetError(), NULL);
	}
	SDL_PauseAudio(0);
	while (audio.audio_len > 0)
		SDL_Delay(100);
	return (SDL_CloseAudio(), SDL_FreeWAV(wav_buffer), SDL_Quit(), SUCCESS);
}

void	*audio_control(t_sound *sound)
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
	if (pthread_create(&sound->thread, NULL, (void *)audio_control, sound) == FALSE)
	{
		pthread_detach(sound->thread);
	}
	else
	{
		error_controller("Failed to create thread.", NULL);
	}
}
