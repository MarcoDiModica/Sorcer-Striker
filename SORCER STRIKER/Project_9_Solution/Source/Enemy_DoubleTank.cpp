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

	Anim1.PushBack({ 3,157,71,42 });
	Anim1.PushBack({ 170,162,72,42 });
	Anim1.speed = 0.01f;

	currentAnim = &Anim1;

	Anim2.PushBack({ 380,158,72,42 });

	collider = App->collisions->AddCollider({ position.x,position.y,72,42 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_DoubleTank::Update()
{
	position.y -= 1;
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

