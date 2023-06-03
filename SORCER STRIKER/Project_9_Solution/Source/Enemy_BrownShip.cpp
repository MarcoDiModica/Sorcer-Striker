#include "Enemy_BrownShip.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "SceneLevel1.h"

Enemy_BrownShip::Enemy_BrownShip(int x, int y) : Enemy(x, y)
{
	cnt = 5;
	tipo = Enemy_Type::BROWNSHIP;
	enemieH = 30;

	Anim1.PushBack({ 44, 5, 36, 34 });
	
	Anim2.PushBack({ 231, 3, 36, 34});
	Anim2.PushBack({ 231, 3, 36, 34 });
	Anim2.speed = 0.2f;
	Anim2.loop = false;

	Anim3.PushBack({ 231, 3, 36, 34 });
	Anim3.PushBack({ 231, 3, 36, 34 });
	Anim3.speed = 0.2f;
	Anim3.loop = false;

	currentAnim = &Anim1;

	collider = App->collisions->AddCollider({ position.x, position.y, 36, 34}, Collider::Type::ENEMY, (Module*)App->enemies);
}


void Enemy_BrownShip::Update()
{
	if (Anim2.HasFinished())
	{
		currentAnim = &Anim1;
	}
	
	position.x += mondongo;

	if (position.x < 10 + 250 || position.x > 190 + 250)
	{
		mondongo *= -1;
	}

	if (position.y > (App->render->camera.y + 30)) {
		 position.y -= App->sceneLevel_1->aprendeaprogramar;
	} 
	
	if (position.y == App->render->camera.y)
	{
		next = current + interval;
	}

	if (position.y > App->render->camera.y)
	{
		current = SDL_GetTicks();

		if (current > next && position.y < App->render->camera.y + 200 && position.y + enemieH> App->render->camera.y)
		{
			int a = App->sceneLevel_1->aprendeaprogramar;
			speedXshot = (App->player->position.x + 1 - (position.x + 35)) / 60.0f;
			speedYshot = (App->player->position.y + a - position.y) / 60.0f;
			if (a == 1)
			{

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

			App->particles->EnemyL.speed.x = speedXshot;
			App->particles->EnemyL.speed.y = speedYshot;
			
			App->particles->AddParticle(App->particles->EnemyL, position.x + 8, position.y + 10, Collider::Type::ENEMY_SHOT);
			interval = rand() % 2001 + 2000;
			next = current + interval;
		}
	}
	

	Enemy::Update();
}

