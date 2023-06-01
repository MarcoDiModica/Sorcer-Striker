#include "Boss.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "Boss_Right.h"
#include "Boss_Left.h"

Boss::Boss(int x, int y) :Enemy(x, y) {

	cnt = 10;
	tipo = Enemy_Type::BOSS;

	flyAnim.PushBack({ 95,418,101,128 });
	flyAnim.PushBack({ 377, 418, 101,128 });
	flyAnim.PushBack({ 654,418,101,128 });
	flyAnim.speed = 0.01f;
	currentAnim = &flyAnim;

	dedge.PushBack({653,556,98,128});
	
	collider = App->collisions->AddCollider({ position.x,position.y,98,128 }, Collider::Type::ENEMY, (Module*)App->enemies);

	//////////////////OEE WATON SI LE DAI A LA TECLA ENE VAI A LA ZONA DEL BO
}

void Boss::Update() {
	position.y -= 1;

	waveRatio += waveRatioSpeed;

	if (cnt == 0) {
		currentAnim = &dedge;
		
	}



	position.x = spawnPos.x + (waveHeight * sinf(waveRatio));


	


	Enemy::Update();
}
 

