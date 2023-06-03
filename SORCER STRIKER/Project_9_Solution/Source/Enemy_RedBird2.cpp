#include "Enemy_RedBird2.h"
#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"

Enemy_RedBird2::Enemy_RedBird2(int x, int y) : Enemy(x, y)
{
	cnt = 2;
	tipo = Enemy_Type::REDBIRD2;
	enemieH = 27;

	flyAnim.PushBack({ 0,0,21,27 });
	flyAnim.PushBack({ 0, 95, 42, 52 });
	flyAnim.speed = 0.2f;

	currentAnim = &flyAnim;

	collider = App->collisions->AddCollider({ 0, 0, 21, 27 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_RedBird2::Update()
{
	position.x += 1.5f;
	position.y += 1;

	if (position.y > (App->render->camera.y + SCREEN_HEIGHT + 50)) {
		SetToDelete();
	}

	Enemy::Update();
}
