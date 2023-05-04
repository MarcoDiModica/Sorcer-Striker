#include "Enemy_RedBird.h"
#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"

Enemy_RedBird::Enemy_RedBird(int x, int y) : Enemy(x, y)
{
	cnt = 1;
	
	flyAnim.PushBack({ 0,0,21,27 });
	flyAnim.PushBack({ 0, 95, 42, 52 });
	flyAnim.speed = 0.2f;

	currentAnim = &flyAnim;

	collider = App->collisions->AddCollider({0, 0, 21, 27}, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_RedBird::Update()
{
	position.y -= 1;
	
	waveRatio += waveRatioSpeed;

	position.x = spawnPos.x + (waveHeight * sinf(waveRatio));

	if (position.y > (App->player->OPTMIZENELJUEGUITO + SCREEN_HEIGHT + 30)) {
		SetToDelete();
	}
	
	Enemy::Update();
}
