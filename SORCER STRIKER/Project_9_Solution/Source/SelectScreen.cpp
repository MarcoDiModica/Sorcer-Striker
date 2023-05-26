#include "SelectScreen.h"
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


SelectScreen::SelectScreen(bool startEnabled) : Module(startEnabled)
{

}

SelectScreen::~SelectScreen()
{

}

// Load assets
bool SelectScreen::Start()
{
	LOG("Loading background assets");
	Mix_ResumeMusic();
	bool ret = true;
	int contador_segundos = 0;
	bgTexture = App->textures->Load("Assets/Sprites/selectdefinitive2.png");
	bgTexture2 = App->textures->Load("Assets/Sprites/cuadrado2.png");
	SDL_Texture* characterTexture = nullptr;
	int currentCharacterIndex = 0;
	char lookupTable[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };
	insertFont = App->fonts->Load("Assets/Fonts/textocosa.png", lookupTable, 2);
	App->audio->PlayMusic("Assets/Music/introTitle.ogg", 1.0f);
	coinFx = App->audio->LoadFx("Assets/Fx/coin.wav");
	App->render->camera.x = 0;
	App->render->camera.y = 0;
	
	int arr[4];
	App->collisions->CleanUp();

	characterTexture = App->textures->Load("Assets/Sprites/selectdefinitive2.png");

	return ret;
}

Update_Status SelectScreen::Update()
{
	
	
	if (App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_DOWN)
	{
		currentCharacterIndex--;
		if (currentCharacterIndex <= 0)
			currentCharacterIndex = 4; // Cambia el n�mero al �ndice m�ximo de personajes disponibles
		// Carga la imagen correspondiente al nuevo �ndice
		// Por ejemplo:
		// characterTexture = App->textures->Load("Assets/Sprites/witch.png");
	}
	if (App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_DOWN)
	{
		currentCharacterIndex++;
		if (currentCharacterIndex > 4) // Cambia el n�mero al �ndice m�ximo de personajes disponibles
			currentCharacterIndex = 1;
		// Carga la imagen correspondiente al nuevo �ndice
		// Por ejemplo:
		
	}
	if (currentCharacterIndex == 1) {

		bgTexture = App->textures->Load("Assets/Sprites/selectdefinitive2.png");

	}
	if (currentCharacterIndex == 2) {

		bgTexture = App->textures->Load("Assets/Sprites/witch.png");

	}
	if (currentCharacterIndex == 3) {

		bgTexture = App->textures->Load("Assets/Sprites/samurai.png");

	}
	if (currentCharacterIndex == 4) {

		bgTexture = App->textures->Load("Assets/Sprites/necromancer.png");

	}
	
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN && currentCharacterIndex == 3)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 70);
		App->audio->PlayFx(coinFx);
	}
	

	

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SelectScreen::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);
	if (currentCharacterIndex == 1) {

		App->render->Blit(bgTexture2, 31, 73, NULL);

	}
	if (currentCharacterIndex == 2) {

		App->render->Blit(bgTexture2, 83, 73, NULL);

	}
	if (currentCharacterIndex == 3) {

		App->render->Blit(bgTexture2, 135, 73, NULL);

	}
	if (currentCharacterIndex == 4) {

		App->render->Blit(bgTexture2, 186, 73, NULL);

	}

	


	



	return Update_Status::UPDATE_CONTINUE;
}
//if (App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_DOWN) {
//	cnt++;
//}
//if (App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_DOWN)
//{
//	cnt--;
//}
//if (cnt < 4) {
//	cnt = 4;
//}
//if (cnt < 0) {
//	cnt = 0;
//}
//if (cnt == 0)
//{
//	bgTexture = App->textures->Load("Assets/Sprites/selectdefinitive2.png");
//}
//if (cnt == 1)
//{
//	bgTexture = App->textures->Load("Assets/Sprites/witch.png");
//}
//if (cnt == 2)
//{
//	bgTexture = App->textures->Load("Assets/Sprites/samurai.png");
//}
//if (cnt == 3)
//{
//	bgTexture = App->textures->Load("Assets/Sprites/necromancer.png");
//}