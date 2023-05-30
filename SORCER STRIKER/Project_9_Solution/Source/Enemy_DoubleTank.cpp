#include "Enemy_DoubleTank.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"

Enemy_DoubleTank::Enemy_DoubleTank(int x, int y) : Enemy(x, y)
{
	cnt = 6;
	tipo = Enemy_Type::DOUBLETANK;

	
	//Anim1.PushBack({ 84,160,72,44 });
	//Anim1.PushBack({ 164,160,72,44 });
	//Anim1.PushBack({ 243,160,72,44 });
	//Anim1.PushBack({ 164,160,72,44 });

	//Anim1.speed = 0.015f;
	//Anim1.loop = true;

	//currentAnim = &Anim1;

	
	Anim1Rev.PushBack({ 1089,62,72,44 });
	Anim1Rev.PushBack({ 1010,61,72,44 });
	

	Anim1Rev.speed = 0.015f;
	Anim1Rev.loop = true;

	currentAnim = &Anim1Rev;

	Anim2.PushBack({ 243,158,72,42 });

	collider = App->collisions->AddCollider({ position.x,position.y,72,42 }, Collider::Type::ITEM, (Module*)App->enemies);
}

void Enemy_DoubleTank::Update()
{
	if (cnt < 3)
	{
		currentAnim = &Anim2;
	}

	if (position.x <= 0)
	{
		position.x = 0;
	}

	if (position.x >= SCREEN_WIDTH - 72)
	{
		position.x = SCREEN_WIDTH - 72;
	}

	Enemy::Update();
}

