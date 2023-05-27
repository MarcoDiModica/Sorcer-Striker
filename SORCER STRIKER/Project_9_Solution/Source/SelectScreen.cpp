#include "SelectScreen.h"
#include "SceneIntro2.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFonts.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
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
	App->audio->PlayMusic("Assets/Music/introTitle.ogg", 1.0f);
	/*coinFx = App->audio->LoadFx("Assets/Fx/coin.wav");*/
	App->render->camera.x = 0;
	App->render->camera.y = 0;
	
	int arr[4];
	App->collisions->CleanUp();

	characterTexture = App->textures->Load("Assets/Sprites/selectdefinitive2.png");

	return ret;
}

Update_Status SelectScreen::Update()
{
	GamePad& pad = App->input->pads[0];

	
	
	if (App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_DOWN || App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_DOWN|| pad.left == true)
	{
		currentCharacterIndex--;
		if (currentCharacterIndex <= 0)
			currentCharacterIndex = 4; 
		
		
	}
	if (App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_DOWN || App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_DOWN||pad.right == true)
	{
		currentCharacterIndex++;
		if (currentCharacterIndex > 4) 
			currentCharacterIndex = 1;
		
		
		
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
	
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN && currentCharacterIndex == 3 || pad.a)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 40);
		App->audio->PlayFx(coinFx);
	}
	

	

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SelectScreen::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	contador_segundos++;
	if (contador_segundos % 5 == 0) {
		if (contador_segundos <= 5) {
			bgTexture2 = App->textures->Load("Assets/Sprites/cuadrado2.png");
		}
		else if (contador_segundos <= 10) {
			bgTexture2 = App->textures->Load("Assets/Sprites/cuadrado2azul.png");
		}
		else if (contador_segundos <= 15) {
			bgTexture2 = App->textures->Load("Assets/Sprites/cuadrado2verde.png");
		}
		else if (contador_segundos >= 20) {
			bgTexture2 = App->textures->Load("Assets/Sprites/cuadrado2rosa.png");
			contador_segundos = 0;
		}
	}
	
	

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