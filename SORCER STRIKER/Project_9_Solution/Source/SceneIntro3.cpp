#include "SceneIntro3.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

SceneIntro3::SceneIntro3(bool startEnabled) : Module(startEnabled)
{

}

SceneIntro3::~SceneIntro3()
{

}

// Load assets
bool SceneIntro3::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/menu.png");
	App->audio->PlayMusic("Assets/Music/introTitle.ogg", 1.0f); 
	coinFx = App->audio->LoadFx("Assets/Fx/coin.wav");
	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status SceneIntro3::Update()
{
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 70);
		App->audio->PlayFx(coinFx);
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneIntro3::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}