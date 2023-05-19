#include "SceneIntro3.h"
#include "SceneIntro2.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFonts.h"
#include "ModuleFadeToBlack.h"
#include <chrono>

#include <iostream>
#include <thread>
#include "ModuleCollisions.h"
#include <SDL_mixer/include/SDL_mixer.h>


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
	Mix_ResumeMusic();
	bool ret = true;
	int contador_segundos = 0;
	bgTexture = App->textures->Load("Assets/Sprites/menu.png");
	//bgTexture2 = App->textures->Load("Assets/Sprites/StageClear.png");
	char lookupTable[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };
	insertFont = App->fonts->Load("Assets/Fonts/textocosa.png", lookupTable, 2);
	App->audio->PlayMusic("Assets/Music/introTitle.ogg", 1.0f); 
	coinFx = App->audio->LoadFx("Assets/Fx/coin.wav");
	App->render->camera.x = 0;
	App->render->camera.y = 0;

	App->collisions->CleanUp();

	return ret;
}

Update_Status SceneIntro3::Update()
{
	

		//contador_segundos++;
		//if (contador_segundos % 70 == 0) {

		//	bgTexture2 = App->textures->Load("Assets/Sprites/.png");
		//	contador_segundos = 0;

		//}
		//else if(contador_segundos>=10){
		//	//bgTexture2 = App->textures->Load("Assets/Sprites/StageClear.png");
		//	App->fonts->BlitText(88, 70, scoreFont, "highscore");
		//}
	
	
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->selectscreen, 70);
		App->audio->PlayFx(coinFx);
	}
	if (App->input->pads[0].a == true)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 70);
		App->audio->PlayFx(coinFx);
	}
	
	if (App->input->keys[SDL_SCANCODE_K] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 70);
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneIntro3::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);
	App->render->Blit(bgTexture2, 0, 0, NULL);
	
	
	contador_segundos++;
	if (contador_segundos % 100 == 0) {

		//bgTexture2 = App->textures->Load("Assets/Sprites/.png");
		contador_segundos = 0;

	}
	else if (contador_segundos >= 50) {
		//bgTexture2 = App->textures->Load("Assets/Sprites/StageClear.png");

		App->fonts->BlitText(57, 179, insertFont, "please insert coin");

	}

	

	return Update_Status::UPDATE_CONTINUE;
}