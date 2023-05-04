#ifndef __SCENE_INTRO3_H__
#define __SCENE_INTRO3_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class SceneIntro3 : public Module
{
public:
	//Constructor
	SceneIntro3(bool startEnabled);

	//Destructor
	~SceneIntro3();

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
	SDL_Texture* bgTexture = nullptr;
	SDL_Texture* bgTexture2 = nullptr;
	int insertFont = -1;
	int contador_segundos = 0;
	//char insertText[10] = { "\0" };


};

#endif
