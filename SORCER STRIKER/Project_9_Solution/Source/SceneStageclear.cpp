#include "SceneStageclear.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFonts.h"
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
	
	bgTexture = App->textures->Load("Assets/Sprites/raizing.png");
	/*App->audio->PlayMusic("Assets/Music/introTitle.ogg", 1.0f);*/
	char lookupTable[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };
	insertFont = App->fonts->Load("Assets/Fonts/textocosa.png", lookupTable, 2);
	
	App->render->camera.x = 0;
	App->render->camera.y = 0;

	App->collisions->CleanUp();

	return ret;
}

Update_Status SceneStageclear::Update()
{
	//put this before use controller
	GamePad& pad = App->input->pads[0];

	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->selectscreen, 30);
	}

	if (App->input->keys[SDL_SCANCODE_K] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 30);
	}

	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN || pad.a == true)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro3, 30);
	}

	kol = SDL_GetTicks();

	if (kol >= 23000)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro3, 50);
	}


	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneStageclear::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 85, 247, NULL);
	App->fonts->BlitText(100, 40, insertFont, "notice");
	App->fonts->BlitText(20, 80, insertFont, "this game is for use in");

	App->fonts->BlitText(20, 100, insertFont, "europe only.");
	App->fonts->BlitText(20, 120, insertFont, "sales, export, or operation");
	App->fonts->BlitText(20, 140, insertFont, "outside this territory");
	App->fonts->BlitText(20, 160, insertFont, "may violate international");	
	App->fonts->BlitText(20, 180, insertFont, "copyright and trademark");
	App->fonts->BlitText(20, 200, insertFont, "laws and the violator");
	App->fonts->BlitText(20, 220, insertFont, "subject to severe penalties.");
	App->fonts->BlitText(52, 290, insertFont, "raizing co.,ltd. 1993");






	return Update_Status::UPDATE_CONTINUE;
}