#include "ReverseST.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include <cstdlib>
#include "SceneLevel1.h"

ReverseST::ReverseST(int x, int y) : Enemy(x, y)
{

	cnt = 4;
	tipo = Enemy_Type::REVERSEST;
	enemieH = 34;

	Anim1Rev.PushBack({ 1100,21,36,34 });
	Anim1Rev.PushBack({ 1018,20 ,36,34 });
	Anim1Rev.PushBack({ 977,20 ,36,34 });
	Anim1Rev.PushBack({ 1018,20 ,36,34 });
	Anim1Rev.speed = 0.02f;
	Anim1Rev.loop = true;

	currentAnim = &Anim1Rev;

	Anim2.PushBack({ 935,20,36,34 });

	Mark.PushBack({ 213,257,38,40 });

	App->particles->man = -1;

	current = SDL_GetTicks();

	collider = App->collisions->AddCollider({ position.x,position.y,36,34 }, Collider::Type::ITEM, (Module*)App->enemies);
	
}

void ReverseST::Update()
{
	position.x += 1;

	if (cnt == 1)
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

	if (current > next && cnt > 1 && position.y < App->render->camera.y + 200 && position.y > App->render->camera.y)
	{
		int a = App->sceneLevel_1->aprendeaprogramar;
		speedXshot = (App->player->position.x + 1 - (position.x + 35)) / 60.0f;
		speedYshot = (App->player->position.y + a - position.y) / 60.0f;

		App->particles->directionshot.speed.x = speedXshot;
		App->particles->directionshot.speed.y = speedYshot;

		App->particles->AddParticle(App->particles->directionshot, position.x + 13, position.y + 12);

		interval = rand() % 1201 + 1200;
		next = current + interval;
	}

	Enemy::Update();
}
