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
	character1 = App->textures->Load("Assets/Sprites/finalselect.png");
	character2 = App->textures->Load("Assets/Sprites/finalwitch.png");
	character3 = App->textures->Load("Assets/Sprites/finalsamurai.png");
	character4 = App->textures->Load("Assets/Sprites/finalnecromancer.png");
	cuadrado = App->textures->Load("Assets/Sprites/cuadrado2.png");


	SDL_Texture* characterTexture = nullptr;
	int currentCharacterIndex = 0;
	App->audio->PlayMusic("Assets/Music/select.ogg", 1.0f);
	selectFx = App->audio->LoadFx("Assets/Fx/8bit.wav");
	App->render->camera.x = 0;
	App->render->camera.y = 0;
	
	int arr[4];
	App->collisions->CleanUp();

	characterTexture = App->textures->Load("Assets/Sprites/finalselect.png");

	return ret;
}

Update_Status SelectScreen::Update()
{
	GamePad& pad = App->input->pads[0];

	
	
	if (App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_DOWN || App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_DOWN|| pad.left == true)
	{
		App->audio->PlayFx(selectFx);
		currentCharacterIndex--;
		if (currentCharacterIndex <= 0)
			currentCharacterIndex = 4; 
		
		
	}
	if (App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_DOWN || App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_DOWN||pad.right == true)
	{
		App->audio->PlayFx(selectFx);
		currentCharacterIndex++;
		if (currentCharacterIndex > 4) 
			currentCharacterIndex = 1;
		
		
		
	}
	
	

	
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN && currentCharacterIndex == 3 || pad.a && currentCharacterIndex == 3 )

	{
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 40);
	}
	

	

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SelectScreen::PostUpdate()
{
	// Draw everything --------------------------------------

	contador_segundos++;
	if (contador_segundos % 5 == 0) {
		if (contador_segundos <= 5) {
			cuadrado = App->textures->Load("Assets/Sprites/cuadrado2.png");
		}
		else if (contador_segundos <= 10) {
			cuadrado = App->textures->Load("Assets/Sprites/cuadrado2azul.png");
		}
		else if (contador_segundos <= 15) {
			cuadrado = App->textures->Load("Assets/Sprites/cuadrado2verde.png");
		}
		else if (contador_segundos >= 20) {
			cuadrado = App->textures->Load("Assets/Sprites/cuadrado2rosa.png");
			contador_segundos = 0;
		}
	}
	
	

	if (currentCharacterIndex == 1) {
		

		App->render->Blit(character1, 0, 0, NULL);

		App->render->Blit(cuadrado, 30, 73, NULL);

	}
	if (currentCharacterIndex == 2) {
		
		App->render->Blit(character2, 0, 0, NULL);


		App->render->Blit(cuadrado, 81, 73, NULL);

	}
	if (currentCharacterIndex == 3) {
		

		App->render->Blit(character3, 0, 0, NULL);

		App->render->Blit(cuadrado, 132, 73, NULL);

	}
	if (currentCharacterIndex == 4) {
		

		App->render->Blit(character4, 0, 0, NULL);


		App->render->Blit(cuadrado, 183, 73, NULL);

	}

	


	return Update_Status::UPDATE_CONTINUE;
}
