#include "Enemy_BlueDragon.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "SceneLevel1.h"
#include <cstdlib>

Enemy_BlueDragon::Enemy_BlueDragon(int x, int y) : Enemy(x, y)
{
	cnt = 6;
	tipo = Enemy_Type::BlUEDRAGON;

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
	next = current + interval;
	App->particles->cocaina = rand() % 5 - 4;

	collider = App->collisions->AddCollider({ position.x,position.y,122,140 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_BlueDragon::Update()
{
	if (position.x <= 5)
	{
		position.x = 5;
	}

	if (position.x >= SCREEN_WIDTH - 120)
	{
		position.x = SCREEN_WIDTH - 120;
	}

	if (position.y > (App->render->camera.y + 60)) {
		position.y -= App->sceneLevel_1->aprendeaprogramar;
	}

	current = SDL_GetTicks();

	if (current > next)
	{
		App->particles->AddParticle(App->particles->enemieShot, position.x + 52, position.y + 100, Collider::Type::ENEMY_SHOT);
		interval = rand() % 1201 + 600;
		App->particles->cocaina = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 3.5f));

		next = current + interval;
	}
	
	Enemy::Update();
}
