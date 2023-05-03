#include "SceneIntro2.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "SceneIntro.h"

SceneIntro2::SceneIntro2(bool startEnabled) : Module(startEnabled)
{

}

SceneIntro2::~SceneIntro2()
{

}

// Load assets
bool SceneIntro2::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/cockcumbeer2.png");

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status SceneIntro2::Update()
{
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro3, 70);
	}

	PabloArquitecto = SDL_GetTicks();

	if (PabloArquitecto >= 7500)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro3, 70);
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneIntro2::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}