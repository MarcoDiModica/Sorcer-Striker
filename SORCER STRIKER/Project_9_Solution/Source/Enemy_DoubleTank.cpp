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


	
	Anim1Rev.PushBack({ 1089,62,72,44 });
	Anim1Rev.PushBack({ 1010,61,72,44 });
	

	Anim1Rev.speed = 0.015f;
	Anim1Rev.loop = true;

	currentAnim = &Anim1Rev;

	Anim2.PushBack({ 930,62,72,42 });

	Mark.PushBack({327,167,67,36});
	Mark.loop = true;

	collider = App->collisions->AddCollider({ position.x,position.y,72,42 }, Collider::Type::ITEM, (Module*)App->enemies);
}

void Enemy_DoubleTank::Update()
{
	if (cnt == 0)
	{
		currentAnim = &Mark;
		collider->type == Collider::Type::NONE;
	}
	
	if (cnt == 2 || cnt == 1)
	{
		currentAnim = &Anim2;
	}

	Enemy::Update();
}

