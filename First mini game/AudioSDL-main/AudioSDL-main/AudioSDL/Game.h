#pragma once

#include "SDL/include/SDL.h"
#include "SDL_image/include/SDL_image.h"
#pragma comment( lib, "SDL/libx86/SDL2.lib" )
#pragma comment( lib, "SDL/libx86/SDL2main.lib" )
#pragma comment( lib, "SDL_image/libx86/SDL2_image.lib" )


#include "SDL_Mixer/include/SDL_mixer.h"
#pragma comment( lib, "SDL_Mixer/lib_x86/SDL2_mixer.lib")

#include "Entity.h"

#define WINDOW_WIDTH	1024
#define WINDOW_HEIGHT	768
#define MAX_KEYS		256
#define MAX_SHOTS		32
#define MAX_TRACKS		8

class Game
{
public:
	Game();
	~Game();

	bool Init();
	bool LoadAudios();
	bool LoadImages();
	void Release();
	
	bool Input();
	bool Update();
	void Draw();

private:
	SDL_Window *Window;
	SDL_Renderer *Renderer;
	SDL_Texture *img_background, *img_player, *img_shot;

	Entity Player, Shots[MAX_SHOTS], Scene;
	int idx_shot;

	bool god_mode;

	enum KEY_STATE { KEY_IDLE, KEY_DOWN, KEY_REPEAT, KEY_UP	};
	KEY_STATE keys[MAX_KEYS]; 

	Mix_Music* tracks[MAX_TRACKS];
	int num_tracks;

	Mix_Chunk* sfxs[MAX_SHOTS];
	int num_sfxs;
	
};
