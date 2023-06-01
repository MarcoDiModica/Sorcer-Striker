#include "Enemy_RedBird3.h"
#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"

Enemy_RedBird3::Enemy_RedBird3(int x, int y) : Enemy(x, y)
{
	cnt = 1;
	tipo = Enemy_Type::REDBIRD3;

	flyAnim.PushBack({ 0,0,21,27 });
	flyAnim.PushBack({ 0, 95, 42, 52 });
	flyAnim.speed = 0.2f;

	currentAnim = &flyAnim;

	collider = App->collisions->AddCollider({ 0, 0, 21, 27 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_RedBird3::Update()
{
	waveRatio += waveRatioSpeed;

	position.x = spawnPos.x + (waveHeight * sinf(waveRatio));

	if (position.y > (App->render->camera.y + SCREEN_HEIGHT + 50)) {
		SetToDelete();
	}

	Enemy::Update();
}
