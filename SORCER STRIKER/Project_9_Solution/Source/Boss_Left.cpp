#include "Boss_Left.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "Boss.h"
#include <cstdlib>

BossLeft::BossLeft(int x, int y) :Enemy(x, y) {

	cnt = 10;
	tipo = Enemy_Type::BOSSLEFT;
	enemieH = 123;

	flyAnim.PushBack({ 1096,426,90,123 });
	flyAnim.PushBack({ 1096,563,90,123 });
	flyAnim.speed = 0.01f;
	flyAnim.loop = true;
	currentAnim = &flyAnim;

	dedge.PushBack({1096,281,90,124});

	collider = App->collisions->AddCollider({ position.x,position.y,90,124 }, Collider::Type::ENEMY, (Module*)App->enemies);

	//////////////////OEE WATON SI LE DAI A LA TECLA ENE VAI A LA ZONA DEL BO
}

void BossLeft::Update() {
	position.y -= 0;

	position.x = spawnPos.x + (waveHeight * sinf(waveRatio));

	if (App->render->camera.y <= (-8525 - SCREEN_HEIGHT / 2))
	{
		position.y -= 1;
	}

	waveRatio += waveRatioSpeed;

	if (cnt == 0 || cnt == -1) {

		currentAnim = &dedge;

	}

	if (cnt == 0) {
		
		App->particles->AddParticle(App->particles->enemieShot, position.x + (rand() % 51 + 30), position.y + 100, Collider::Type::ENEMY_SHOT);
		App->particles->cocaina = static_cast<float>(std::rand()) / RAND_MAX * 2 + 1;
		App->particles->AddParticle(App->particles->enemieShot2, position.x + (rand() % 51 + 30), position.y + 90, Collider::Type::ENEMY_SHOT);
		App->particles->cocaina2 = static_cast<float>(std::rand()) / RAND_MAX * 2 + 1;
		App->particles->AddParticle(App->particles->enemieShot3, position.x + (rand() % 51 + 30), position.y + 110, Collider::Type::ENEMY_SHOT);
		App->particles->cocaina3 = static_cast<float>(std::rand()) / RAND_MAX * 2 + 1;
		App->particles->AddParticle(App->particles->enemieShot4, position.x + (rand() % 51 + 30), position.y + 120, Collider::Type::ENEMY_SHOT);
		App->particles->cocaina4 = static_cast<float>(std::rand()) / RAND_MAX * 2 + 1;
		App->particles->AddParticle(App->particles->enemieShot, position.x + (rand() % 51 + 30), position.y + 130, Collider::Type::ENEMY_SHOT);
		App->particles->cocaina5 = static_cast<float>(std::rand()) / RAND_MAX * 2 + 1;
		App->particles->AddParticle(App->particles->enemieShot2, position.x + (rand() % 51 + 30), position.y + 150, Collider::Type::ENEMY_SHOT);
		App->particles->cocaina6 = static_cast<float>(std::rand()) / RAND_MAX * 2 + 1;
		App->particles->AddParticle(App->particles->enemieShot3, position.x + (rand() % 51 + 30), position.y + 150, Collider::Type::ENEMY_SHOT);
		App->particles->cocaina7 = static_cast<float>(std::rand()) / RAND_MAX * 2 + 1;
		App->particles->AddParticle(App->particles->enemieShot4, position.x + (rand() % 51 + 30), position.y + 160, Collider::Type::ENEMY_SHOT);
		App->particles->cocaina8 = static_cast<float>(std::rand()) / RAND_MAX * 2 + 1;

		cnt = -1;

	}
	

	Enemy::Update();
}