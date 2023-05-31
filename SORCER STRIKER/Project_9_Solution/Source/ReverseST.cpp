#include "ReverseST.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"

ReverseST::ReverseST(int x, int y) : Enemy(x, y)
{

	cnt = 4;
	tipo = Enemy_Type::REVERSEST;

	Anim1Rev.PushBack({ 1100,21,36,34 });
	Anim1Rev.PushBack({ 1018,20 ,36,34 });
	Anim1Rev.PushBack({ 977,20 ,36,34 });
	Anim1Rev.PushBack({ 1018,20 ,36,34 });
	Anim1Rev.speed = 0.02f;
	Anim1Rev.loop = true;

	currentAnim = &Anim1Rev;

	Anim2.PushBack({ 935,20,36,34 });

	Mark.PushBack({ 213,257,38,40 });

	collider = App->collisions->AddCollider({ position.x,position.y,36,34 }, Collider::Type::ITEM, (Module*)App->enemies);
	
}

void ReverseST::Update()
{
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

	Enemy::Update();
}
