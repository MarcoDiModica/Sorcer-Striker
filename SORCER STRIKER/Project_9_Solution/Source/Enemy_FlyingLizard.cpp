#include "Enemy_FlyingLizard.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"

Enemy_FlyingLizard::Enemy_FlyingLizard(int x, int y) : Enemy(x, y) 
{
	cnt = 6;
	tipo = Enemy_Type::FLYINGLIZARD;

	FlyAnim1.PushBack({ 144,221,26,24 });
	FlyAnim1.PushBack({ 106,226,26,20 });
	FlyAnim1.PushBack({ 74,230,26,14 });
	FlyAnim1.PushBack({ 45,225,26,20 });
	FlyAnim1.PushBack({ 18,220,26,24 });
	FlyAnim1.PushBack({ 45,225,26,20 });
	FlyAnim1.PushBack({ 74,230,26,14 });
	FlyAnim1.PushBack({ 106,226,26,20 });
	FlyAnim1.PushBack({ 144,221,26,24 });


	FlyAnim1.speed = 0.01f;
	
	currentAnim = &FlyAnim1;

	

	collider = App->collisions->AddCollider({ position.x,position.y,36,34 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_FlyingLizard::Update()
{
	Enemy::Update();
}
