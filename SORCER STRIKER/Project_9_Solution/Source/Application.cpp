#include "Application.h"

#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "SceneIntro.h"
#include "SceneIntro2.h"
#include "SceneIntro3.h"
#include "SelectScreen.h"
#include "SceneGameOver.h"
#include "SceneStageclear.h"
#include "SceneLevel1.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "ModuleRender.h"
#include "ModuleItems.h"

Application::Application()
{
	// The order in which the modules are added is very important.
	// It will define the order in which Pre/Update/Post will be called
	// Render should always be last, as our last action should be updating the screen

	modules[0] =	window =		new ModuleWindow(true);
	modules[1] =	input =			new ModuleInput(true);
	modules[2] =	textures =		new ModuleTextures(true);
	modules[3] =	audio =			new ModuleAudio(true);

	modules[4] =	sceneIntro =	new SceneIntro(true);
	modules[5] =	sceneIntro2 =	new SceneIntro2(false);	
	modules[6] = sceneIntro3 = new SceneIntro3(false);
	modules[7] = sceneGameOver = new SceneGameOver(false);
	modules[8] = sceneStageclear = new SceneStageclear(false);
	modules[9] = selectscreen = new SelectScreen(false);
	modules[10] =	sceneLevel_1 =	new SceneLevel1(false);		//Gameplay scene starts disabled
	modules[11] =	player =		new ModulePlayer(false);	//Player starts disabled
	modules[12] =	particles =		new ModuleParticles(true);
	modules[13] =	enemies =		new ModuleEnemies(false);	//Enemies start disabled

	modules[14] =	collisions =	new ModuleCollisions(true);
	modules[15] =	fade =			new ModuleFadeToBlack(true);
	modules[16] =	fonts =			new ModuleFonts(true);
	modules[17] =	render =		new ModuleRender(true);
	modules[18] = items = new ModuleItems(false); 
}

Application::~Application()
{
	for (int i = 0; i < NUM_MODULES; ++i)
	{
		//Important: when deleting a pointer, set it to nullptr afterwards
		//It allows us for null check in other parts of the code
		delete modules[i];
		modules[i] = nullptr;
	}
}

bool Application::Init()
{
	bool ret = true;

	// All modules (active and disabled) will be initialized
	for (int i = 0; i < NUM_MODULES && ret; ++i)
		ret = modules[i]->Init();

	// Only active modules will be 'started'
	for (int i = 0; i < NUM_MODULES && ret; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	return ret;
}

Update_Status Application::Update()
{
	Update_Status ret = Update_Status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == Update_Status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : Update_Status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == Update_Status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : Update_Status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == Update_Status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : Update_Status::UPDATE_CONTINUE;

	if (App->input->keys[SDL_SCANCODE_ESCAPE] == Key_State::KEY_DOWN)
	{
		/*App->window->quit = true;*/
		App->CleanUp();
	}

	SDL_Delay(16.6);

	return ret;
}
 
bool Application::CleanUp()
{
	bool ret = true;

	for (int i = NUM_MODULES - 1; i >= 0 && ret; --i)
		ret = modules[i]->IsEnabled() ? modules[i]->CleanUp() : true;

	return ret;
}
