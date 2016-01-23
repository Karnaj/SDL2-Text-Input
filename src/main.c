#include <SDL2/SDL.h>
#include <stdio.h>
#include <string.h>
#define LEN_MAX 10

SDL_Window *Init(void)
{
   SDL_Window *window;
   if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
		return NULL;
	}
	window = SDL_CreateWindow("Personnage 1.0", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 500, 500, SDL_WINDOW_SHOWN);
	if(NULL == window)
		fprintf(stderr, "Erreur SDL_CreateWindow : %s", SDL_GetError());
   return window;
}

int main(int argc, char* args[])
{
	SDL_Window *window = NULL;
	int quit = SDL_FALSE;
	char rep[LEN_MAX] = {0};
	size_t len = 0, l;

	SDL_Event event;
	if(window = Init() == NULL)
      goto Quit;
	SDL_StartTextInput();
	while(!quit)
	{
		SDL_WaitEvent(&event);
		if(event.type == SDL_QUIT)
			quit = SDL_TRUE;
		else if( event.type == SDL_KEYDOWN)
		{
			if(event.key.keysym.sym == SDLK_ESCAPE)
				quit = SDL_TRUE;
			if(event.key.keysym.sym == SDLK_BACKSPACE && len > 0)
			{
				rep[len - 1] = 0;
				len--;
			}
			if(event.key.keysym.sym == SDLK_v && (SDL_GetModState() & KMOD_CTRL) && SDL_HasClipboardText())
			{
				char *tmp = SDL_GetClipboardText();
				l = strlen(tmp);
				strncpy(rep + len, tmp, LEN_MAX - 1 - len);
            len += l;
            if(len > len > LEN_MAX - 1)
               len = LEN_MAX - 1;
				SDL_free(tmp);
			}
			if(event.key.keysym.sym == SDLK_c && (SDL_GetModState() & KMOD_CTRL))
				SDL_SetClipboardText(rep);
		}
		else if(event.type == SDL_TEXTINPUT)
		{
			l = strlen(event.text.text);
			strncpy(rep + len, event.text.text, LEN_MAX - 1 - len);
         len += l;
			if(len > LEN_MAX - 1)
            len = LEN_MAX - 1;
		}
      puts(rep);
	}
	SDL_StopTextInput();
Quit:
	if(window)
		SDL_DestroyWindow(window);
Fin:
	SDL_Quit();
	return 0;
}
