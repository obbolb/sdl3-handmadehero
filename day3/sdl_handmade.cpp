#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define WINDOW_TITLE "Handmade Hero"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL; 
static SDL_Texture *texture = NULL;
static void *pixels = NULL;
//static SDL_Rect *rect=NULL;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv){
	if(!SDL_Init(SDL_INIT_VIDEO)){
		SDL_Log("Couldn't initialize game: %s",SDL_GetError());
		return SDL_APP_FAILURE;
	}
	if(!SDL_CreateWindowAndRenderer(WINDOW_TITLE,WINDOW_WIDTH,WINDOW_HEIGHT,SDL_WINDOW_RESIZABLE,&window,&renderer)){
		SDL_Log("Couldn't create game window/renderer: %s",SDL_GetError());
		return SDL_APP_FAILURE;
        }

	texture = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_ARGB8888,SDL_TEXTUREACCESS_STREAMING,WINDOW_WIDTH,WINDOW_HEIGHT);
	if(!texture){
		SDL_Log("Couldn't create a texture: %s",SDL_GetError());
		return SDL_APP_FAILURE;
	}

        pixels= calloc(WINDOW_HEIGHT * WINDOW_WIDTH * 4,1);
	if(!pixels){
		fprintf(stderr,"can't allocate pixel memory");
		return SDL_APP_FAILURE;
	}
	
	return SDL_APP_CONTINUE;	
}
//function gets called whenever a new event comes in (dont need to be calling pollevent()
//
//TODO:there is a pixel the pixel go into texture texture go into windows 
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event){
	switch(event->type){
		case SDL_EVENT_QUIT:
			return SDL_APP_SUCCESS;
			break;
		
		//this was changed in sdl3 window events are now top level
		//instead of the specific event being inside the sdl_windowevent struct	
		case SDL_EVENT_WINDOW_RESIZED:
			SDL_Log("window is resized to %d * %d",event->window.data1,event->window.data2);
			return SDL_APP_CONTINUE;
			break;
		
		case SDL_EVENT_WINDOW_FOCUS_GAINED:
			SDL_Log("focus gained");
			return SDL_APP_CONTINUE;
			break;

	}
	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate){
	int pitch = WINDOW_WIDTH * 4;
	if(SDL_LockTexture(texture,NULL,&pixels,&pitch)){
		SDL_UnlockTexture(texture);		
	}
	SDL_RenderTexture(renderer,texture,NULL,NULL);
	SDL_RenderPresent(renderer);
	return SDL_APP_CONTINUE;

}


void SDL_AppQuit(void *appstate, SDL_AppResult result){
	//sdl will cal sdl_quit which will free everything
	if(pixels){
		free(pixels);
	}
}




		
				
			
			
		
			
				




