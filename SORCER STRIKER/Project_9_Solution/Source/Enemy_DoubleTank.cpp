#include "Enemy_DoubleTank.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "SceneLevel1.h"

Enemy_DoubleTank::Enemy_DoubleTank(int x, int y) : Enemy(x, y)
{
	cnt = 8;
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

	if (current > next && cnt > 2 && position.y < App->render->camera.y + 200 && position.y + enemieH > App->render->camera.y)
	{
		int a = App->sceneLevel_1->aprendeaprogramar;
		speedXshot = (App->player->position.x + 1 - (position.x + 35)) / 60.0f;
		speedYshot = (App->player->position.y + a - position.y) / 60.0f;
		if (a == 1)
		{
			if (speedYshot < -2.5f)
			{
				speedYshot = -2.5f;
			}
			if (speedYshot > 2.5f)
			{
				speedYshot = 2.5f;
			}
			if (speedYshot == 0)
			{
				speedYshot += 0.5f;
			}
		}
		if (a == 2)
		{
			if (speedYshot < -2.5f)
			{
				speedYshot = -2.5f;
			}
			if (speedYshot > 2.5f)
			{
				speedYshot = 2.5f;
			}
			if (speedYshot == 0)
			{
				speedYshot += 0.5f;
			}
			speedXshot++;
		}

		App->particles->directionshot.speed.x = speedXshot;
		App->particles->directionshot.speed.y = speedYshot;
		App->particles->AddParticle(App->particles->directionshot, position.x + 25, position.y + 12, Collider::Type::ENEMY_SHOT);
		App->particles->AddParticle(App->particles->directionshot, position.x + 55, position.y + 12, Collider::Type::ENEMY_SHOT);

		interval = rand() % 2001 + 2000;
		next = current + interval;
	}

	Enemy::Update();
}

