#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "p2Point.h"
#include "Animation.h"
#include "ModuleEnemies.h"

struct SDL_Texture;
struct Collider;

class Enemy
{
public:
	// Constructor
	// Saves the spawn position for later movement calculations
	Enemy(int x, int y);

	int cnt;
	bool text = false;
	bool miya = false;
	bool win = false;
	// Destructor
	virtual ~Enemy();

	// Returns the enemy's collider
	const Collider* GetCollider() const;

	// Called from inhering enemies' Udpate
	// Updates animation and collider position
	virtual void Update();

	// Called from ModuleEnemies' Update
	virtual void Draw();

	// Collision response
	virtual void OnCollision(Collider* collider);

	// Sets flag for deletion and for the collider aswell
	virtual void SetToDelete();

public:
	// The current position in the world
	iPoint position;

	float speedXshot;
	float speedYshot;

	// The enemy's texture
	SDL_Texture* texture = nullptr;

	// Sound fx when destroyed
	uint destroyedFx = 0;

	int bossdelete;

	int enemieH;

	uint tracker;

	// A flag for the enemy removal. Important! We do not delete objects instantly
	bool pendingToDelete = false;

protected:
	// A ptr to the current animation
	Animation* currentAnim = nullptr;
	Animation Anim1;
	Animation Anim2;
	Animation Anim3;

	// The enemy's collider
	Collider* collider = nullptr;

	Enemy_Type tipo = Enemy_Type::NO_TYPE;

	// Original spawn position. Stored for movement calculations
	iPoint spawnPos;
};

#endif // __ENEMY_H__