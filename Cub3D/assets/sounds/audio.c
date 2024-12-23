#include <SDL2/SDL.h>
#include <stdio.h>

Uint8			*audio_buf;

Uint32			audio_len;

SDL_AudioSpec	spec;

void play_audio(const char *filename)
{
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
	{
		fprintf(stderr, "SDL_InitError: %s\n", SDL_GetError());
		return;
	}
	if (SDL_LoadWAV(filename, &spec, &audio_buf, &audio_len) == NULL)
	{
		fprintf(stderr, "SDL_LoadWAV Error: %s\n", SDL_GetError());
		SDL_Quit();
		return;
	}
	if (SDL_OpenAudio(&spec, NULL) < 0)
	{
		fprintf(stderr, "SDL_OpenAudio Error: %s\n", SDL_GetError());
		SDL_FreeWAV(audio_buf);
		SDL_Quit();
		return;
	}
	SDL_PauseAudio(0);

	SDL_Delay((audio_len / spec.freq) * 1000);

	SDL_CloseAudio();

	SDL_FreeWAV(audio_buf);

	SDL_Quit();
}

int	main()
{
	play_audio("../../../../backup/bg_music.wav");
	return (0);
}
