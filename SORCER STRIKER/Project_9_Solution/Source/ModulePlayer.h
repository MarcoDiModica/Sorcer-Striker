#ifndef __MODULE_PLAYER_H__
#define __MODULE_PLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"
#include <SDL_image/include/SDL_image.h>

struct SDL_Texture;
struct Collider;

class ModulePlayer : public Module
{
public:
	// Constructor
	ModulePlayer(bool startEnabled);

	// Destructor
	~ModulePlayer();

	// Called when the module is activated
	// Loads the necessary textures for the player
	bool Start() override;

	// Called at the middle of the application loop
	// Processes new input and handles player movement
	Update_Status Update() override;

	// Called at the end of the application loop
	// Performs the render call of the player sprite
	Update_Status PostUpdate() override;

	// Collision callback, called when the player intersects with another collider
	void OnCollision(Collider* c1, Collider* c2) override;

	// Draws gamepad debug info in the screen
	void DebugDrawGamepadInfo();

public:
	// Position of the player in the map
	iPoint position;

	// The speed in which we move the player (pixels per frame)
	int speed = 2;

	float laserspeed = -8;
	int stagespeed = 1;
	int playershots = 2;
	bool ahora = false;
	bool crack = false;
	bool farlopa = false;
	bool anfetaminas = false;
	bool stage;
	bool over;

	Uint32 intervalo = 1000;

	Uint32 startTime;
	Uint32 nextNotificationTime;
	Uint32 currentTime;

	Uint32 current;
	Uint32 next;
	Uint32 interval = 4000;
	Uint32 start;
	Uint32 current2;
	Uint32 next2;
	Uint32 interval2 = 4000;
	Uint32 start2;

	// Countdown to handle shot spacing
	int shotMaxCountdown = 7;
	int shotCountdown = 0;

	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* texture = nullptr;
	
	//SDL_Texture* win = nullptr;
	
	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentAnimation = nullptr;

	// A set of animations
	Animation idleAnim;
	Animation leftAnim;
	Animation rightAnim;
	Animation boost;

	Animation bright1;
	Animation bright2;
	Animation bright3;

	Animation flip;
	




	// The player's collider
	Collider* collider = nullptr;
	Collider* collider2 = nullptr;
	Collider* collider3 = nullptr;

	// A flag to detect when the player has been destroyed
	bool destroyed = false;
	bool god_mode = false;
	int OPTMIZENELJUEGUITO;

	// Sound effects indices
	uint laserFx = 0;
	uint explosionFx = 0;
	uint winFx = 0;
	uint loseFx = 0;
	uint coinFx = 0;
	uint damageFx = 0;
	uint bigexplioson = 0;
	uint muerteFx = 0;
	uint pkfire = 0;
	uint hit = 0;

	// uint lasthitFX = 0;

	// Font score index
	uint score = 000;
	uint highscore = 000;
	uint lives = 3;
	int scoreFont = -1;
	char livesText[10] = { "\0" };
	char scoreText[10] = { "\0" };
	char highscoreText[10] = { "\0" };

	// Debugdraw for gamepad data
	bool debugGamepadInfo = false;

};

#endif //!__MODULE_PLAYER_H__