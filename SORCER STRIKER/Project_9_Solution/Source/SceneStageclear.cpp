#include "SceneStageclear.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleCollisions.h"
#include <SDL_mixer/include/SDL_mixer.h>
#include "ModulePlayer.h"

SceneStageclear::SceneStageclear(bool startEnabled) : Module(startEnabled)
{

}

SceneStageclear::~SceneStageclear()
{

}

// Load assets
bool SceneStageclear::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	Mix_PauseMusic();

	bgTexture = App->textures->Load("Assets/Sprites/goodending.png");
	/*App->audio->PlayMusic("Assets/Music/introTitle.ogg", 1.0f);*/
	App->audio->PlayFx(App->player->winFx);
	App->render->camera.x = 0;
	App->render->camera.y = 0;

	App->collisions->CleanUp();

	return ret;
}

Update_Status SceneStageclear::Update()
{
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro3, 30);
	}

	if (App->input->pads[0].a == true)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro3, 30);
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneStageclear::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}