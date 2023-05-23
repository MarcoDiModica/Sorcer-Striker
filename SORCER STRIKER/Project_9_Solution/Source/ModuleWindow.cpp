#include "ModuleWindow.h"

#include "Application.h"
#include "Globals.h"
#include "ModuleInput.h"

#include "SDL/include/SDL.h"


ModuleWindow::ModuleWindow(bool startEnabled) : Module(startEnabled)
{}

ModuleWindow::~ModuleWindow()
{}

bool ModuleWindow::Init()
{
	LOG("Init SDL window & surface");
	bool ret = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		LOG("SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		//Create window
		Uint32 flags = SDL_WINDOW_SHOWN;

		if (WIN_FULLSCREEN == true)
			flags |= SDL_WINDOW_FULLSCREEN;

		if (WIN_BORDERLESS == true)
			flags |= SDL_WINDOW_BORDERLESS;

		if (WIN_RESIZABLE == true)
			flags |= SDL_WINDOW_RESIZABLE;

		if (WIN_FULLSCREEN_DESKTOP == true)
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;

		window = SDL_CreateWindow("SORCER STRIKER : F1 DEBUG MODE : F2 GOD MODE : F3 AUTO WIN : F4 AUTO LOSE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH * SCREEN_SIZE, SCREEN_HEIGHT * SCREEN_SIZE, flags);
		
		if (window == nullptr)
		{
			LOG("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}
		else
		{
			screenSurface = SDL_GetWindowSurface(window);
		}
	}

	return ret;
}

Update_Status ModuleWindow::Update() {
	if (quit && !isFullscreen)
	{
		SDL_DestroyWindow(window);
	}
	if (App->input->keys[SDL_SCANCODE_F11] == Key_State::KEY_DOWN && isFullscreen == false)
	{
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
		isFullscreen = !isFullscreen;
	}
	else if (App->input->keys[SDL_SCANCODE_F11] == Key_State::KEY_DOWN && isFullscreen == true)
	{ 
		SDL_SetWindowFullscreen(window, SDL_WINDOW_SHOWN);
		isFullscreen = !isFullscreen;
	}
	return Update_Status::UPDATE_CONTINUE;
}

bool ModuleWindow::CleanUp()
{
	LOG("Destroying SDL window and quitting all SDL systems");

	//Destroy window
	if (window != nullptr && quit != true)
		SDL_DestroyWindow(window);

	//Quit SDL subsystems
	SDL_Quit();

	return true;
}




