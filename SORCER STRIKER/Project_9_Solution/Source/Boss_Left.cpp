#include "Boss_Left.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"

BossLeft::BossLeft(int x, int y) :Enemy(x, y) {

	cnt = 10;
	tipo = Enemy_Type::BOSSLEFT;

	flyAnim.PushBack({ 12,418,83,123 });
	flyAnim.PushBack({ 293, 418, 83,123 });
	flyAnim.speed = 0.01f;
	currentAnim = &flyAnim;

	collider = App->collisions->AddCollider({ position.x,position.y,83,123 }, Collider::Type::ENEMY, (Module*)App->enemies);

	//////////////////OEE WATON SI LE DAI A LA TECLA ENE VAI A LA ZONA DEL BO
}

void BossLeft::Update() {
	position.y -= 1;

	waveRatio += waveRatioSpeed;


	/*position.x = spawnPos.x + (waveHeight * sinf(waveRatio));

	if (position.y > (App->render->camera.y + SCREEN_HEIGHT + 50)) {
		SetToDelete();
	}*/

	


	Enemy::Update();
}