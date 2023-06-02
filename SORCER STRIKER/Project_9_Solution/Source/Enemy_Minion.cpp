#include "Enemy_Minion.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"

Enemy_Minion::Enemy_Minion(int x, int y) :Enemy(x, y) {

	cnt = 1;
	tipo = Enemy_Type::MINION;
	enemieH = 24;

	flyAnim.PushBack({ 18,229,26,24 });
	currentAnim = &flyAnim;

	collider = App->collisions->AddCollider({ position.x,position.y,26,24 }, Collider::Type::ENEMY, (Module*)App->enemies);

	//////////////////OEE WATON SI LE DAI A LA TECLA ENE VAI A LA ZONA DEL BO
}

void Enemy_Minion::Update() {
	position.y -= 1;

	waveRatio += waveRatioSpeed;

	

	/*position.x = spawnPos.x + (waveHeight * sinf(waveRatio));*/






	Enemy::Update();
}