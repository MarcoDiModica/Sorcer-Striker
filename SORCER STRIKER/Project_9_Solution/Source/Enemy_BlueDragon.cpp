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
	App->particles->cocaina = (rand() / static_cast<double>(RAND_MAX)) * 7.0 - 3.5;

	collider = App->collisions->AddCollider({ position.x,position.y,122,140 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_BlueDragon::Update()
{
	if (position.x <= 5 + 250)
	{
		position.x = 5;
	}

	if (position.x >= SCREEN_WIDTH / 2 - 120 + 250)
	{
		position.x = SCREEN_WIDTH / 2 - 120 + 250;
	}

	if (position.y > (App->render->camera.y + 60)) {
		position.y -= App->sceneLevel_1->aprendeaprogramar;
	}

	current = SDL_GetTicks();

	if (current > next)
	{
		App->particles->AddParticle(App->particles->enemieShot, position.x + (rand() % 51 + 30), position.y + 100, Collider::Type::ENEMY_SHOT);
		App->particles->AddParticle(App->particles->enemieShot, position.x + (rand() % 51 + 30), position.y + 100, Collider::Type::ENEMY_SHOT);
		App->particles->AddParticle(App->particles->enemieShot, position.x + (rand() % 51 + 30), position.y + 100, Collider::Type::ENEMY_SHOT);
		App->particles->AddParticle(App->particles->enemieShot, position.x + (rand() % 51 + 30), position.y + 100, Collider::Type::ENEMY_SHOT);
		App->particles->AddParticle(App->particles->enemieShot, position.x + (rand() % 51 + 30), position.y + 100, Collider::Type::ENEMY_SHOT);
		App->particles->AddParticle(App->particles->enemieShot, position.x + (rand() % 51 + 30), position.y + 100, Collider::Type::ENEMY_SHOT);
		App->particles->cocaina = (rand() / static_cast<double>(RAND_MAX)) * 7.0 - 3.5;
		
		interval = rand() % 1001 + 1000;
		next = current + interval;
	}
	
	Enemy::Update();
}
