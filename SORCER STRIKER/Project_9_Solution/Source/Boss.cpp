#include "Boss.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"

Boss::Boss(int x, int y) :Enemy(x, y) {

	cnt = 20;
	tipo = Enemy_Type::BOSS;

	flyAnim.PushBack({ 95,418,101,128 });
	flyAnim.PushBack({ 377, 418, 101,128 });
	flyAnim.speed = 0.01f;
	currentAnim = &flyAnim;
	
	collider = App->collisions->AddCollider({ position.x,position.y,101,128 }, Collider::Type::ENEMY, (Module*)App->enemies);

	//////////////////OEE WATON SI LE DAI A LA TECLA ENE VAI A LA ZONA DEL BO
}

void Boss::Update() {
	position.y -= 1;

	waveRatio += waveRatioSpeed;


	/*position.x = spawnPos.x + (waveHeight * sinf(waveRatio));

	if (position.y > (App->render->camera.y + SCREEN_HEIGHT + 50)) {
		SetToDelete();
	}

	if (position.x <= 10)
	{
		position.x = 10;
	}

	if (position.x >= SCREEN_WIDTH - 10)
	{
		position.x = SCREEN_WIDTH - 10;
	}
	*/


	Enemy::Update();
}
 

