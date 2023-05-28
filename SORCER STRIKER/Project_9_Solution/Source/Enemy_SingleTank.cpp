#include "Enemy_SingleTank.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"

Enemy_SingleTank::Enemy_SingleTank(int x, int y) : Enemy(x, y) 
{

	cnt = 6;
	tipo = Enemy_Type::SINGLETANK;

	Anim1.PushBack({ 66,270,36,34 });
	Anim1.PushBack({ 190,270,36,34 });
	Anim1.PushBack({ 116,270,36,34 });
	Anim1.speed = 0.01f;

	currentAnim = &Anim1;

	Anim2.PushBack({ 24,270,36,34 });

	collider = App->collisions->AddCollider({ position.x,position.y,36,34 }, Collider::Type::ITEM, (Module*)App->enemies);

}

void Enemy_SingleTank::Update()
{
	position.y -= 1;
	if (cnt < 3)
	{
		currentAnim = &Anim2;
	}

	if (position.x <= 0)
	{
		position.x = 0;
	}

	if (position.x >= SCREEN_WIDTH - 36)
	{
		position.x = SCREEN_WIDTH - 36;
	}

	Enemy:: Update();
}
