#include "ReverseDT.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"

ReverseDT::ReverseDT(int x, int y) : Enemy(x, y)
{
	cnt = 6;
	tipo = Enemy_Type::REVERSEDT;

	Anim1.PushBack({ 84,160,72,44 });
	Anim1.PushBack({ 164,160,72,44 });
	Anim1.PushBack({ 243,160,72,44 });
	Anim1.PushBack({ 164,160,72,44 });

	Anim1.speed = 0.015f;
	Anim1.loop = true;

	currentAnim = &Anim1;

	Anim2.PushBack({ 380,158,72,42 }); //////////////pablo cambialo

	collider = App->collisions->AddCollider({ position.x,position.y,72,42 }, Collider::Type::ITEM, (Module*)App->enemies);
}

void ReverseDT::Update()
{
	if (cnt < 3)
	{
		currentAnim = &Anim2;
	}

	Enemy::Update();
}

