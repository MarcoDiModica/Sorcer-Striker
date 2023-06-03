#include "Enemy_BrownShip2.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "SceneLevel1.h"

Enemy_BrownShip2::Enemy_BrownShip2(int x, int y) : Enemy(x, y)
{
	cnt = 5;
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

	turnAnim1.PushBack({ 90,48,36,34 });
	turnAnim1.loop = true;
	
	turnAnim2.PushBack({ 88,7,36,34 });
	turnAnim2.loop = true;

	currentAnim = &Anim1;

	collider = App->collisions->AddCollider({ position.x, position.y, 36, 34 }, Collider::Type::ENEMY, (Module*)App->enemies);
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

	if (position.y > 254)
	{
		if (position.y > (App->render->camera.y + 50))
		{
			position.x += 1;
			currentAnim = &turnAnim2;
		}
		
		if (position.y == (App->render->camera.y + 50))
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
				speedXshot++;
			}

			App->particles->EnemyL.speed.x = speedXshot;
			App->particles->EnemyL.speed.y = speedYshot;

			App->particles->AddParticle(App->particles->EnemyL, position.x + 8, position.y + 10, Collider::Type::ENEMY_SHOT);
		}
	}
	else
	{
		if (position.y > (App->render->camera.y + 50))
		{
			position.x -= 1;
			currentAnim = &turnAnim1;
			
		}

		if (position.y == (App->render->camera.y + 50))
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
		}
	}

	Enemy::Update();
}

