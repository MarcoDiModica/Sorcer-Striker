#include "Enemy_BlueDragon2.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "SceneLevel1.h"
#include <cstdlib>
#include <ctime>

Enemy_BlueDragon2::Enemy_BlueDragon2(int x, int y) : Enemy(x, y)
{
	cnt = 6;
	tipo = Enemy_Type::BlUEDRAGON2;

	DrakeAnim1.PushBack({ 428,278,116,130 });
	DrakeAnim1.PushBack({ 704,280,116,130 });
	DrakeAnim1.PushBack({ 564,278,116,130 });
	DrakeAnim1.PushBack({ 704,280,116,130 });

	DrakeAnim2.PushBack({ 433,128,122,140 });
	DrakeAnim2.PushBack({ 568,134,122,140 });
	DrakeAnim2.PushBack({ 634,266,122,140 });

	DrakeAnim1.speed = 0.05f;
	DrakeAnim1.loop = true;

	currentAnim = &DrakeAnim1;

	current = SDL_GetTicks();

	App->particles->cocaina5 = static_cast<float>(rand()) / RAND_MAX * -2 - 1;
	App->particles->cocaina6 = static_cast<float>(rand()) / RAND_MAX * -2 - 1;
	App->particles->cocaina7 = static_cast<float>(rand()) / RAND_MAX * -2 - 1;
	App->particles->cocaina8 = static_cast<float>(rand()) / RAND_MAX * -2 - 1;
	collider = App->collisions->AddCollider({ position.x,position.y,122,140 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_BlueDragon2::Update()
{
	if (position.y > (App->render->camera.y + 40)) {
		position.y -= App->sceneLevel_1->aprendeaprogramar;
	}

	if (position.y == App->render->camera.y)
	{
		next = current + interval;
	}

	current = SDL_GetTicks();

	if (current > next)
	{
		App->particles->cocaina5 = static_cast<float>(rand()) / RAND_MAX * -2 - 1;
		App->particles->AddParticle(App->particles->enemieShot5, position.x + (rand() % 51 + 30), position.y + 100, Collider::Type::ENEMY_SHOT);
		App->particles->cocaina6 = static_cast<float>(rand()) / RAND_MAX * -2 - 1;
		App->particles->AddParticle(App->particles->enemieShot6, position.x + (rand() % 51 + 30), position.y + 90, Collider::Type::ENEMY_SHOT);
		App->particles->cocaina7 = static_cast<float>(rand()) / RAND_MAX * -2 - 1;
		App->particles->AddParticle(App->particles->enemieShot7, position.x + (rand() % 51 + 30), position.y + 110, Collider::Type::ENEMY_SHOT);
		App->particles->cocaina8 = static_cast<float>(rand()) / RAND_MAX * -2 - 1;
		App->particles->AddParticle(App->particles->enemieShot8, position.x + (rand() % 51 + 30), position.y + 120, Collider::Type::ENEMY_SHOT);
		

		interval = rand() % 1501 + 1500;
		next = current + interval;
	}

	Enemy::Update();
}