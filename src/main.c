#include <SDL2/SDL.h>
#include <stdio.h>
#include <string.h>
#define LEN_MAX 80

void copier(char *src, char *dst, int len)
{
	while(len-- && (*dst++ = *src++));
}

int main(int argc, char* args[])
{
	SDL_Window *window = NULL;
	int quit = SDL_FALSE;
	char rep[LEN_MAX] = {0};
	int len = 0, l;
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
		goto Fin;
	}
	window = SDL_CreateWindow("Personnage 1.0", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 500, 500, SDL_WINDOW_SHOWN);
	if(NULL == window)
	{
		fprintf(stderr, "Erreur SDL_CreateWindow : %s", SDL_GetError());
		goto Quit;
	}
	SDL_Event event;
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
				if(LEN_MAX - 1 - len - l > 0)
				{
					copier(tmp, (rep + len), l);
					len += l;
				}
				else
				{
					copier(tmp, (rep + len), LEN_MAX - 1 - len);
					len = LEN_MAX - 1;
				}
			}
			if(event.key.keysym.sym == SDLK_c && (SDL_GetModState() & KMOD_CTRL))
				SDL_SetClipboardText(rep);
		}
		else if(event.type == SDL_TEXTINPUT)
		{
			l = strlen(event.text.text);
			if(LEN_MAX - 1 - len - l > 0)
			{
				copier(event.text.text, (rep + len), l);
				len += l;
			}
			else
			{
				copier(event.text.text, (rep + len), LEN_MAX - 1 - len);
				len = LEN_MAX - 1;
			}
		}
		printf("%s\n", rep);
	}
	SDL_StopTextInput();
Quit:
	if(window)
		SDL_DestroyWindow(window);
Fin:
	SDL_Quit();
	return 0;
}
