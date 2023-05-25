#include "Enemy_Bag.h"
#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"

Enemy_Bag::Enemy_Bag(int x, int y) : Enemy(x, y) 
{
	cnt = 1;
	tipo = Enemy_Type::BAG;
	
	hoverAnim.PushBack({ 254,7,36,27 });
	hoverAnim.PushBack({ 295, 7, 34, 27 });
	hoverAnim.PushBack({ 336, 4, 21, 30 });
	hoverAnim.PushBack({ 365, 6, 36, 28 });
	hoverAnim.speed = 0.2f;

	currentAnim = &hoverAnim;

	collider = App->collisions->AddCollider({ 0, 0, 35, 30 }, Collider::Type::ENEMY, (Module*)App->enemies);

}

void Enemy_Bag::Update()
{
	waveRatio += waveRatioSpeed;

	position.x = spawnPos.x + (waveHeight * sinf(waveRatio));

	if (position.y > (App->player->OPTMIZENELJUEGUITO + 70)) {
		position.y -= 3;
	}

	Enemy::Update();
}