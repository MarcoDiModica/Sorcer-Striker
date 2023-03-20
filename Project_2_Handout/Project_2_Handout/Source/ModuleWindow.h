#ifndef __MODULE_WINDOW_H__
#define __MODULE_WINDOW_H__

#include "Module.h"
#define WINDOWH	600
#define WINDOWW 600
// TODO 1:	Create the declaration of ModuleWindow class

//			It should inherit from module and override all necessary functions

struct SDL_Window;

class ModuleWindow : public Module {
public:
	virtual bool Init();
	virtual bool CleanUp();
private:
	SDL_Window* window;
};
#endif // !__MODULE_WINDOW_H__

