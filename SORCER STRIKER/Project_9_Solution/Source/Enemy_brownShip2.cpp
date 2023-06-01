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

	Anim1.PushBack({ 44, 5, 36, 34 });

	Anim2.PushBack({ 231, 3, 36, 34 });
	Anim2.PushBack({ 231, 3, 36, 34 });
	Anim2.speed = 0.4f;
	Anim2.loop = false;

	Anim3.PushBack({ 231, 3, 36, 34 });
	Anim3.PushBack({ 231, 3, 36, 34 });
	Anim3.speed = 0.4f;
	Anim3.loop = false;

	currentAnim = &Anim1;

	//turnAnim2.PushBack({ 144, 0, 34, 31 });
	//
	//turnAnim3.PushBack({ 179, 0, 34, 31 });
	//
	//turnAnim4.PushBack({ 215, 0, 34, 31 });
	// 
	//// Define the movement path
	//path.PushBack({ 0.0f, -0.3f }, 200, &flyAnim);
	//currentAnim = path.GetCurrentAnimation();
	//path.PushBack({ 0.2f, -0.5f }, 60, &turnAnim1);
	//currentAnim = path.GetCurrentAnimation();
	//path.PushBack({ 0.3f, -0.6f }, 60, &turnAnim2);
	//currentAnim = path.GetCurrentAnimation();
	//path.PushBack({ 0.4f, -2.0f }, 60, &turnAnim3);
	//currentAnim = path.GetCurrentAnimation();
	//path.PushBack({ 0.0f, -0.3f }, 1000, &turnAnim4);
	//currentAnim = path.GetCurrentAnimation();

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
