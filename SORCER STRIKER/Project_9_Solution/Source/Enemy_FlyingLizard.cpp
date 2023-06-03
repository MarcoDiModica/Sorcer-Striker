#include "Enemy_FlyingLizard.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"

Enemy_FlyingLizard::Enemy_FlyingLizard(int x, int y) : Enemy(x, y) 
{
	cnt = 1;
	tipo = Enemy_Type::FLYINGLIZARD;
	enemieH = 34;

	FlyAnim1.PushBack({ 18,229,26,24 });
	/*FlyAnim1.PushBack({ 44,225,26,18 });
	FlyAnim1.PushBack({ 71,230,26,14 });
	FlyAnim1.PushBack({ 97,225,26,18 });
	FlyAnim1.PushBack({ 123,220,26,24 });
	
	FlyAnim1.loop = true;


	FlyAnim1.speed = 0.01f;*/
	
	currentAnim = &FlyAnim1;

	collider = App->collisions->AddCollider({ position.x,position.y,24,14 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_FlyingLizard::Update()
{
	position.y += 4;

	if (position.y > (App->render->camera.y + SCREEN_HEIGHT + 50)) {
		SetToDelete();
	}
	
	Enemy::Update();
}
