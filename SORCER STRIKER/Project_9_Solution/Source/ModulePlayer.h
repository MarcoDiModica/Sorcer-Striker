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

public:
	// Position of the player in the map
	iPoint position;

	// The speed in which we move the player (pixels per frame)
	int speed = 2;

	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* texture = nullptr;

	SDL_Texture* win = nullptr;
	
	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentAnimation = nullptr;

	// A set of animations
	Animation idleAnim;
	Animation leftAnim;
	Animation rightAnim;

	// The player's collider
	Collider* collider = nullptr;

	// A flag to detect when the player has been destroyed
	bool destroyed = false;
	bool god_mode = false;
	float OPTMIZENELJUEGUITO;

	// Sound effects indices
	uint laserFx = 0;
	uint explosionFx = 0;
	uint winFx = 0;
	uint loseFx = 0;
	uint coinFx = 0;
	// uint damageFx = 0; 
	// uint lasthitFX = 0;

	// Font score index
	uint score = 000;
	uint highscore = 000;
	uint lives = 3;
	int scoreFont = -1;
	char livesText[10] = { "\0" };
	char scoreText[10] = { "\0" };
	char highscoreText[10] = { "\0" };

};

#endif //!__MODULE_PLAYER_H__