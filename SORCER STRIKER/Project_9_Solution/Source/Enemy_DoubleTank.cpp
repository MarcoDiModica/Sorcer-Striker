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
	enemieH = 42;

	
	Anim1Rev.PushBack({ 1089,62,72,44 });
	Anim1Rev.PushBack({ 1010,61,72,44 });
	

	Anim1Rev.speed = 0.015f;
	Anim1Rev.loop = true;

	currentAnim = &Anim1Rev;

	Anim2.PushBack({ 930,62,72,42 });

	Mark.PushBack({327,167,67,36});
	Mark.loop = true;

	current = SDL_GetTicks();

	collider = App->collisions->AddCollider({ position.x,position.y,72,42 }, Collider::Type::ITEM, (Module*)App->enemies);
}

void Enemy_DoubleTank::Update()
{
	
	if (cnt == 2 || cnt == 1)
	{
		currentAnim = &Anim2;
	}

	if (cnt == 0)
	{
		currentAnim = &Mark;
		if (collider != nullptr)
		{
			collider->type = Collider::Type::NONE;
		}
	}

	if (position.y == App->render->camera.y)
	{
		next = current + interval;
	}

	current = SDL_GetTicks();

	if (current > next && cnt > 2)
	{
		App->particles->AddParticle(App->particles->enemieShotTANK, position.x + 25, position.y + 12);
		App->particles->AddParticle(App->particles->enemieShotTANK, position.x + 55, position.y + 12);

		interval = rand() % 1501 + 1500;
		next = current + interval;
	}

	Enemy::Update();
}

