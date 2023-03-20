#include "ModuleWindow.h"

#include "Application.h"
#include "Globals.h"
#include "SDL/include/SDL.h"

bool ModuleWindow::Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	window = SDL_CreateWindow("ME ABURRO EN ESTA CLASE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOWH, WINDOWW, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		SDL_Log("Unable to create window: %s", SDL_GetError());
		return false;
	}

	return true;
	
}

bool ModuleWindow::CleanUp(){
	
	SDL_DestroyWindow(window);
	SDL_Quit;

	return true;
}
//	TODO 2:	Init the library and check for possible errors using SDL_GetError()
	
//	TODO 3:	Pick the width and height and experiment with different window flags.
//			Create the window and check for errors
//			Expose the SDL_window as a public variable to access it through the different application modules
		
//	TODO 4: Create a screen surface and keep it as a public variable
		
//	TODO 5:	Fill with code the CleanUp() method
//			Remove all the data and uninitialize SDL





