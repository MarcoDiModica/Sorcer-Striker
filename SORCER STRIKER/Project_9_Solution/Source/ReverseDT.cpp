#include "ReverseDT.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include <cstdlib>

ReverseDT::ReverseDT(int x, int y) : Enemy(x, y)
{
	cnt = 6;
	tipo = Enemy_Type::REVERSEDT;

	Anim1.PushBack({ 84,160,72,44 });
	Anim1.PushBack({ 164,160,72,44 });


	Anim1.speed = 0.015f;
	Anim1.loop = true;

	Mark.PushBack({ 327,167,67,36 });
	Mark.loop = true;

	currentAnim = &Anim1;

	Anim2.PushBack({ 244,158,72,42 }); 
	//falta la marca del suelo//

	App->particles->man = -1;

	current = SDL_GetTicks();

	collider = App->collisions->AddCollider({ position.x,position.y,72,42 }, Collider::Type::ITEM, (Module*)App->enemies);
}

void ReverseDT::Update()
{

	if (cnt == 0)
	{
		currentAnim = &Mark;
		if (collider != nullptr)
		{
			collider->type = Collider::Type::NONE;
		}
	}

	if (cnt == 2 || cnt == 1)
	{
		currentAnim = &Anim2;

	}

	if (position.y == App->render->camera.y)
	{
		next = current + interval;
	}

	current = SDL_GetTicks();

	if (current > next && cnt > 2)
	{
		App->particles->AddParticle(App->particles->enemieShotTANK2, position.x + 25, position.y + 12);
		App->particles->AddParticle(App->particles->enemieShotTANK2, position.x + 55, position.y + 12);

		interval = rand() % 1501 + 1500;
		next = current + interval;
	}

	Enemy::Update();
}

