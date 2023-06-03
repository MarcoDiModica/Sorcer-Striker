#include "SceneIntro.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

SceneIntro::SceneIntro(bool startEnabled) : Module(startEnabled)
{

}

SceneIntro::~SceneIntro()
{

}

// Load assets
bool SceneIntro::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/Initialscreen.png");
	App->audio->PlayMusic("Assets/Music/pizzadeluxe.ogg", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status SceneIntro::Update()
{
	//put this before use controller
	GamePad& pad = App->input->pads[0];

	//Press "s" to skip to selection Screen
	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->selectscreen, 30);
	}
	//Press "k" to skip to level 1
	if (App->input->keys[SDL_SCANCODE_K] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 30);
	}

	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN || pad.a == true)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro2, 50);
	}
	
	
	tiempou = SDL_GetTicks();

	if (tiempou >= 7000)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro2, 50);
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneIntro::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}