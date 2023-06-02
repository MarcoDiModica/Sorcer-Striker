#include "Boss_Right.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include <cstdlib>

BossRight::BossRight(int x, int y) :Enemy(x, y) {

	cnt = 10;
	tipo = Enemy_Type::BOSSRIGHT;
	enemieH = 120;

	flyAnim.PushBack({ 1305,426,90,124 });
	flyAnim.PushBack({ 1305,563,90,124 });
	flyAnim.loop = true;
	flyAnim.speed = 0.01f;
	currentAnim = &flyAnim;

	dedge.PushBack({1305,281,90,124});

	collider = App->collisions->AddCollider({ position.x,position.y,90,124 }, Collider::Type::ENEMY, (Module*)App->enemies);

	
	App->particles->cocaina5 = static_cast<float>(rand()) / RAND_MAX * -2 - 1;
	App->particles->cocaina6 = static_cast<float>(rand()) / RAND_MAX * -2 - 1;
	App->particles->cocaina7 = static_cast<float>(rand()) / RAND_MAX * -2 - 1;
	App->particles->cocaina8 = static_cast<float>(rand()) / RAND_MAX * -2 - 1;

	//////////////////OEE WATON SI LE DAI A LA TECLA ENE VAI A LA ZONA DEL BO
}

void BossRight::Update() {
	position.y -= 0;

	if (App->render->camera.y <= (-8525 - SCREEN_HEIGHT / 2))
	{
		position.y -= 1;
	}

	waveRatio += waveRatioSpeed;

	if (cnt == 0 || cnt == -1 || cnt == -2) {

		currentAnim = &dedge;

	}


	if (cnt == 0) {


		App->particles->AddParticle(App->particles->enemieShot6, position.x + (rand() % 51 + 30), position.y + 80, Collider::Type::ENEMY_SHOT);
		App->particles->cocaina6 = static_cast<float>(std::rand()) / RAND_MAX * 2 + 1;
		App->particles->AddParticle(App->particles->enemieShot7, position.x + (rand() % 51 + 30), position.y + 95, Collider::Type::ENEMY_SHOT);
		App->particles->cocaina7 = static_cast<float>(std::rand()) / RAND_MAX * 2 + 1;
		App->particles->AddParticle(App->particles->enemieShot8, position.x + (rand() % 51 + 30), position.y + 160, Collider::Type::ENEMY_SHOT);
		App->particles->cocaina8 = static_cast<float>(std::rand()) / RAND_MAX * 2 + 1;
		App->particles->AddParticle(App->particles->enemieShot5, position.x + (rand() % 51 + 30), position.y + 70, Collider::Type::ENEMY_SHOT);
		App->particles->cocaina5 = static_cast<float>(std::rand()) / RAND_MAX * 2 + 1;
		App->particles->AddParticle(App->particles->enemieShot6, position.x + (rand() % 51 + 30), position.y + 100, Collider::Type::ENEMY_SHOT);
		App->particles->cocaina6 = static_cast<float>(std::rand()) / RAND_MAX * 2 + 1;
		App->particles->AddParticle(App->particles->enemieShot7, position.x + (rand() % 51 + 30), position.y + 90, Collider::Type::ENEMY_SHOT);
		App->particles->cocaina7 = static_cast<float>(std::rand()) / RAND_MAX * 2 + 1;
		App->particles->AddParticle(App->particles->enemieShot8, position.x + (rand() % 51 + 30), position.y + 110, Collider::Type::ENEMY_SHOT);
		App->particles->cocaina8 = static_cast<float>(std::rand()) / RAND_MAX * 2 + 1;
		App->particles->AddParticle(App->particles->enemieShot5, position.x + (rand() % 51 + 30), position.y + 120, Collider::Type::ENEMY_SHOT);
		App->particles->cocaina5 = static_cast<float>(std::rand()) / RAND_MAX * 2 + 1;
		

		cnt = -1;

	}

	position.x = spawnPos.x + (waveHeight * sinf(waveRatio));

	Enemy::Update();
}