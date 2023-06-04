#include "SceneGameOver.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleFadeToBlack.h"
#include "ModuleCollisions.h"
#include <SDL_mixer/include/SDL_mixer.h>

SceneGameOver::SceneGameOver(bool startEnabled) : Module(startEnabled)
{

}

SceneGameOver::~SceneGameOver()
{

}

// Load assets
bool SceneGameOver::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/gameover test.png");
	Mix_PauseMusic();

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	
	/*App->collisions->CleanUp();
	App->particles->CleanUp();
	App->enemies->CleanUp();
	App->player->CleanUp();

	App->collisions->Disable();
	App->enemies->Disable();
	App->player->Disable();*/
	
	

	return ret;
}

Update_Status SceneGameOver::Update()
{
	GamePad& pad = App->input->pads[0];
	
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN || pad.a == true)
	{
		App->fade->FadeToBlack((Module*)App->sceneGameOver, (Module*)App->sceneIntro3, 30);
	}

	erm = SDL_GetTicks();

	
	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneGameOver::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}