#ifndef __ITEM_H__
#define __ITEM_H__

#include "p2Point.h"
#include "Animation.h"

struct SDL_Texture;
struct Collider;

class Item
{
public:
	// Constructor
	// Saves the spawn position for later movement calculations
	Item(int x, int y);

	// Destructor
	virtual ~Item();

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

	// The enemy's texture
	SDL_Texture* texture2 = nullptr;

	// Sound fx when destroyed
	int collectedFx = 0;

	// A flag for the enemy removal. Important! We do not delete objects instantly
	bool pendingToDelete = false;

protected:
	// A ptr to the current animation
	Animation* currentAnim2 = nullptr;

	// The enemy's collider
	Collider* collider = nullptr;

	// Original spawn position. Stored for movement calculations
	iPoint spawnPos;
};

#endif // __ITEM_H__