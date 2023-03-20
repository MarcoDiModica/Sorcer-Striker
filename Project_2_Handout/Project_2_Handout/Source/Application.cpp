#include "Application.h"

#include "Module.h"
#include "ModuleDummy.h"
#include "ModuleWindow.h"

Application::Application()
{
	modules[0] = dummy = new ModuleDummy();

	//TODO 1: Create the window module in application

	modules[1] = window = new ModuleWindow();
}

Application::~Application()
{
	for (int i = 0; i < NUM_MODULES; ++i)
	{
		//Important! When deleting a pointer, set it to nullptr afterwards
		//It allows us for null check in other parts of the code
		delete modules[i];
		modules[i] = nullptr;
	}
}

bool Application::Init()
{
	for (int i = 0; i < NUM_MODULES; ++i)
	{
		modules[i]->Init();
	}

	return true;
}

update_status Application::Update()
{
	update_status ret = update_status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == update_status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->PreUpdate();

	for (int i = 0; i < NUM_MODULES && ret == update_status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->Update();

	for (int i = 0; i < NUM_MODULES && ret == update_status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->PostUpdate();

	return ret;
}
 
bool Application::CleanUp()
{
	bool ret = true;

	for (int i = NUM_MODULES - 1; i >= 0 && ret; --i)
	{
		ret = modules[i]->CleanUp();
	}

	return ret;
}
