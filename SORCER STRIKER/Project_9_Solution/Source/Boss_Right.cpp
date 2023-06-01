#include "Boss_Right.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"

BossRight::BossRight(int x, int y) :Enemy(x, y) {

	cnt = 10;
	tipo = Enemy_Type::BOSSRIGHT;

	flyAnim.PushBack({ 196,418,80,120 });
	flyAnim.PushBack({ 478, 418, 80,120 });
	flyAnim.PushBack({ 755,418,80,120 });
	flyAnim.speed = 0.01f;
	currentAnim = &flyAnim;

	dedge.PushBack({749,556,29,120});

	collider = App->collisions->AddCollider({ position.x-4,position.y,80,120 }, Collider::Type::ENEMY, (Module*)App->enemies);

	

	//////////////////OEE WATON SI LE DAI A LA TECLA ENE VAI A LA ZONA DEL BO
}

void BossRight::Update() {
	position.y -= 1;

	waveRatio += waveRatioSpeed;

	if (cnt == 0) {

		
		currentAnim = &dedge;
	}

	


	position.x = spawnPos.x + (waveHeight * sinf(waveRatio));

	

	


	Enemy::Update();
}