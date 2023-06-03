#include "Enemy_BlueDragon.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "SceneLevel1.h"
#include <cstdlib>
#include <ctime>

Enemy_BlueDragon::Enemy_BlueDragon(int x, int y) : Enemy(x, y)
{
	cnt = 10;
	tipo = Enemy_Type::BlUEDRAGON;
	enemieH = 140;

	DrakeAnim1.PushBack({ 428,278,116,130 });
	DrakeAnim1.PushBack({ 704,280,116,130 });
	DrakeAnim1.PushBack({ 564,278,116,130 });
	DrakeAnim1.PushBack({ 704,280,116,130 });
	DrakeAnim1.speed = 0.05f;
	DrakeAnim1.loop = true;

	DrakeAnim2.PushBack({ 433,128,122,140 });
	DrakeAnim2.PushBack({ 433,128,122,140 });
	DrakeAnim1.speed = 0.05f;
	DrakeAnim1.loop = false;

	DrakeAnim3.PushBack({ 568,134,122,140 });
	DrakeAnim3.PushBack({ 568,134,122,140 });
	DrakeAnim1.speed = 0.05f;
	DrakeAnim1.loop = false;

	DrakeAnim4.PushBack({ 634,266,122,140 }); 
	DrakeAnim4.PushBack({ 634,266,122,140 });
	DrakeAnim1.speed = 0.03f;
	DrakeAnim1.loop = false;

	currentAnim = &DrakeAnim1;
	App->particles->man = -1;
	
	current = SDL_GetTicks();

	App->particles->cocaina = static_cast<float>(std::rand()) / RAND_MAX * 2 + 1;
	App->particles->cocaina2 = static_cast<float>(std::rand()) / RAND_MAX * 2 + 1;
	App->particles->cocaina3 = static_cast<float>(std::rand()) / RAND_MAX * 2 + 1;
	App->particles->cocaina4 = static_cast<float>(std::rand()) / RAND_MAX * 2 + 1;
	collider = App->collisions->AddCollider({ position.x,position.y,122,140 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_BlueDragon::Update()
{  
	if (position.y > (App->render->camera.y + 25)) {
		position.y -= App->sceneLevel_1->aprendeaprogramar;
	}

	if (position.y == App->render->camera.y - 50)
	{
		next = current + interval;
	}

	current = SDL_GetTicks();

	if (current > next && position.y < App->render->camera.y + 200 && position.y + enemieH> App->render->camera.y )
	{
		int a = App->sceneLevel_1->aprendeaprogramar;
		speedXshot = (App->player->position.x + 1 - (position.x + 35)) / 60.0f;
		speedYshot = (App->player->position.y - position.y) / 60.0f;
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
		}

		App->particles->directionshot.speed.x = speedXshot;
		App->particles->directionshot.speed.y = speedYshot;
		
		App->particles->AddParticle(App->particles->directionshot, position.x + (rand() % 51 + 30), position.y + 100, Collider::Type::ENEMY_SHOT);
		
		App->particles->AddParticle(App->particles->directionshot, position.x + (rand() % 51 + 30), position.y + 90, Collider::Type::ENEMY_SHOT);
		
		App->particles->AddParticle(App->particles->directionshot, position.x + (rand() % 51 + 30), position.y + 110, Collider::Type::ENEMY_SHOT);
		
		App->particles->AddParticle(App->particles->directionshot, position.x + (rand() % 51 + 30), position.y + 120, Collider::Type::ENEMY_SHOT);
		
		interval = rand() % 1001 + 1000;
		next = current + interval;
	}
	
	Enemy::Update();
}
