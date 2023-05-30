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

	Anim1.PushBack({ 48,260,36,34 });
	Anim1.PushBack({ 88,260,36,34 });
	Anim1.PushBack({ 129,260,36,34 });
	Anim1.PushBack({ 88,260,36,34 });
	Anim1.speed = 0.06f;
	Anim1.loop = true;

	Anim1Rev.PushBack({ 1100,21,36,34 });
	Anim1Rev.PushBack({ 1018,20 ,36,34 });
	Anim1Rev.PushBack({ 977,20 ,36,34 });
	Anim1Rev.PushBack({ 1018,20 ,36,34 });
	Anim1Rev.speed = 0.06f;
	Anim1Rev.loop = true;

	currentAnim = &Anim1;


	/*currentAnim = &Anim1Rev;*/
	

	Anim2.PushBack({ 171,260,36,34 });

	collider = App->collisions->AddCollider({ position.x,position.y,36,34 }, Collider::Type::ENEMY, (Module*)App->enemies);

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
