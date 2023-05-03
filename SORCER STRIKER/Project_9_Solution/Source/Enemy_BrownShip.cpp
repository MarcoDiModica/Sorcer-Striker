#include "Enemy_BrownShip.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"

Enemy_BrownShip::Enemy_BrownShip(int x, int y) : Enemy(x, y)
{
	cnt = 3;
	
	// Define the fly animation
	flyAnim.PushBack({68, 0, 34, 31});
	
	// Define the turning animation
	turnAnim1.PushBack({ 109, 0, 34, 31});

	turnAnim2.PushBack({ 144, 0, 34, 31 });
	
	turnAnim3.PushBack({ 179, 0, 34, 31 });
	
	turnAnim4.PushBack({ 215, 0, 34, 31 });
	 
	// Define the movement path
	path.PushBack({ 0.0f, -0.3f }, 200, &flyAnim);
	currentAnim = path.GetCurrentAnimation();
	path.PushBack({ 0.2f, -0.5f }, 60, &turnAnim1);
	currentAnim = path.GetCurrentAnimation();
	path.PushBack({ 0.3f, -0.6f }, 60, &turnAnim2);
	currentAnim = path.GetCurrentAnimation();
	path.PushBack({ 0.4f, -2.0f }, 60, &turnAnim3);
	currentAnim = path.GetCurrentAnimation();
	path.PushBack({ 0.0f, -0.3f }, 1000, &turnAnim4);
	currentAnim = path.GetCurrentAnimation();

	collider = App->collisions->AddCollider({ position.y + 5, position.y, 34, 30}, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_BrownShip::Update()
{
	path.Update();

	position = spawnPos + path.GetRelativePosition();

	if (position.y > (App->player->OPTMIZENELJUEGUITO + 120)) {
		position.y -= 3;
	}

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
