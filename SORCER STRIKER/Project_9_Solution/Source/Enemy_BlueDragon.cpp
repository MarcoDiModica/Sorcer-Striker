#include "Enemy_BlueDragon.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"

Enemy_BlueDragon::Enemy_BlueDragon(int x, int y) : Enemy(x, y)
{
	cnt = 6;
	tipo = Enemy_Type::BlUEDRAGON;

	DrakeAnim1.PushBack({ 372,266,114,120 });
	DrakeAnim1.PushBack({ 507,273,114,120 });
	DrakeAnim1.PushBack({ 634,266,114,120 });
	DrakeAnim1.PushBack({ 760,270,114,120 });

	DrakeAnim1.speed = 0.01f;

	currentAnim = &DrakeAnim1;

	collider = App->collisions->AddCollider({ position.x,position.y,114,124 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_BlueDragon::Update()
{
	Enemy::Update();
}
