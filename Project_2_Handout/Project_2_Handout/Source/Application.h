#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"
#include "Module.h"

//TODO 1: Change the 'NUM_MODULES' value
#define NUM_MODULES 2

class ModuleDummy;
class ModuleWindow;

class Application
{

public:

	//Constructor. Creates all necessary modules for the application
	Application();

	//Destructor. Removes all module objects
	~Application();

	//Initializes all modules
	bool Init();

	//Updates all modules (PreUpdate, Update and PostUpdate)
	update_status Update();

	//Releases all the application data
	bool CleanUp();

public:

	Module* modules[NUM_MODULES];

	ModuleDummy* dummy = nullptr;
	ModuleWindow* window = nullptr;

};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__