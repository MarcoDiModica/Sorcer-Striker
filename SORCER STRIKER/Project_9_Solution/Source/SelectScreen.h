#ifndef __SELECT_SCREEN_H__
#define __SELECT_SCREEN_H__

#include "Module.h"
#include "Animation.h"
#include <SDL/include/SDL.h>

struct SDL_Texture;

class SelectScreen : public Module
{
public:
	//Constructor
	SelectScreen(bool startEnabled);

	//Destructor
	~SelectScreen();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	Update_Status Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	Update_Status PostUpdate() override;

	uint coinFx = 0;
public:
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* character1 = nullptr;
	SDL_Texture* character2 = nullptr;
	SDL_Texture* character3 = nullptr;
	SDL_Texture* character4 = nullptr;
	SDL_Texture* cuadrado = nullptr;

	uint selectFx = 0;

	int contador_segundos = 0;
int currentCharacterIndex = 1;
};

#endif
