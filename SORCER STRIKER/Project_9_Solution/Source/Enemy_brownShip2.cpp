#include "Enemy_BrownShip2.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "SceneLevel1.h"

Enemy_BrownShip2::Enemy_BrownShip2(int x, int y) : Enemy(x, y)
{
	cnt = 3;
	tipo = Enemy_Type::BROWNSHIP2;
	enemieH = 30;

	Anim1.PushBack({ 44, 5, 36, 34 });

	Anim2.PushBack({ 231, 3, 36, 34 });
	Anim2.PushBack({ 231, 3, 36, 34 });
	Anim2.speed = 0.2f;
	Anim2.loop = false;

	Anim3.PushBack({ 231, 3, 36, 34 });
	Anim3.PushBack({ 231, 3, 36, 34 });
	Anim3.speed = 0.2f;
	Anim3.loop = false;

	currentAnim = &Anim1;


	collider = App->collisions->AddCollider({ position.y + 5, position.y, 34, 30 }, Collider::Type::ENEMY, (Module*)App->enemies);
}


void Enemy_BrownShip2::Update()
{
	if (Anim2.HasFinished())
	{
		currentAnim = &Anim1;
	}

	if (position.y > (App->render->camera.y + 60)) {
		position.y -= App->sceneLevel_1->aprendeaprogramar;
	}

	if (position.y == App->render->camera.y)
	{
		next = current + interval;
	}

	if (position.y > App->render->camera.y)
	{
		current = SDL_GetTicks();

		if (current > next)
		{
			App->particles->AddParticle(App->particles->EnemyL, position.x, position.y, Collider::Type::ENEMY_SHOT);
			interval = rand() % 2001 + 2000;
			next = current + interval;
		}
	}


	Enemy::Update();
}

