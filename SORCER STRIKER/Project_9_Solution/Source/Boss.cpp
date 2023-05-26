#include "Boss.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"

Boss::Boss(int x, int y) :Enemy(x, y) {
	flyAnim.PushBack({ 831, 1, 264,123 });
	currentAnim = &flyAnim;
	collider = App->collisions->AddCollider({ 0,0,256,123 }, Collider::Type::ENEMY, (Module*)App->enemies);

}

void Boss::Update() {
	position.y -= 1;

	waveRatio += waveRatioSpeed;

	


	Enemy::Update();
}
 

