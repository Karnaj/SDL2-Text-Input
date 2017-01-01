#include <SDL2/SDL.h>
#include <stdio.h>
#include <string.h>
#define LEN_MAX 80
#undef main

int run(void);

int run(void)
{
	char rep[LEN_MAX + 1] = {0};
	size_t len = 0;
	SDL_Event event;
	SDL_bool quit = SDL_FALSE;
	while(!quit)
	{
		SDL_bool has_type = SDL_FALSE;
		SDL_WaitEvent(&event);
		if(event.type == SDL_QUIT)
			quit = SDL_TRUE;
		else if( event.type == SDL_KEYDOWN)
		{
			if(event.key.keysym.sym == SDLK_BACKSPACE && len)
			{
				rep[len - 1] = 0;
				len--;
				has_type = SDL_TRUE;
			}
			if(event.key.keysym.sym == SDLK_v && (SDL_GetModState() & KMOD_CTRL) && SDL_HasClipboardText())
			{
				char *tmp = SDL_GetClipboardText();
				size_t l = strlen(tmp);
				size_t l_copy = len + l < LEN_MAX ? l : LEN_MAX - len;
				strncpy(rep + len, tmp, l_copy);
				len += l_copy;
				SDL_free(tmp);
				has_type = SDL_TRUE;
			}
			if(event.key.keysym.sym == SDLK_c && (SDL_GetModState() & KMOD_CTRL))
				SDL_SetClipboardText(rep);
		}
		else if(event.type == SDL_TEXTINPUT)
		{
			size_t l = strlen(event.text.text);
			size_t l_copy = len + l < LEN_MAX ? l : LEN_MAX - len;
			strncpy(rep + len, event.text.text, l_copy);
			len += l_copy;
			has_type = SDL_TRUE;
		}
		if(has_type)
			puts(rep);
	}
	return 1;
}

int main(void)
{
	int statut = EXIT_FAILURE;
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
		fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
	else
	{
		SDL_Window *window = SDL_CreateWindow("Text Input", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 500, 500, SDL_WINDOW_SHOWN);
		if(NULL == window)
			fprintf(stderr, "Erreur SDL_CreateWindow : %s", SDL_GetError());
		else
		{
			statut = EXIT_SUCCESS;
			SDL_StartTextInput();
			run();
			SDL_StopTextInput();
			SDL_DestroyWindow(window);
		}
		SDL_Quit();
	}
	return statut;
}
