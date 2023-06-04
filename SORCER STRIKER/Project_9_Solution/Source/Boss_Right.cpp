#include "Boss_Right.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include <cstdlib>
#include "SceneLevel1.h"


BossRight::BossRight(int x, int y) :Enemy(x, y) {

	cnt = 33;
	tipo = Enemy_Type::BOSSRIGHT;
	enemieH = 120;

	flyAnim.PushBack({ 1305,426,90,123 });
	flyAnim.PushBack({ 1305,563,90,123 });
	flyAnim.loop = true;
	flyAnim.speed = 0.01f;
	currentAnim = &flyAnim;

	dedge.PushBack({1305,281,90,124});

	collider = App->collisions->AddCollider({ position.x,position.y,90,124 }, Collider::Type::ENEMY, (Module*)App->enemies);


	//////////////////OEE WATON SI LE DAI A LA TECLA ENE VAI A LA ZONA DEL BO
}

void BossRight::Update() {
	position.y += 0;

	if (position.y > App->render->camera.y + 30) {
		position.y -= 1;
	}
	
	tracker += 1;

	if ((tracker == 500 || tracker == 1500 || tracker == 3000) && cnt > 0) {
		App->particles->AddParticle(App->particles->flamethrower, position.x + 7, position.y, Collider::Type::ENEMY_SHOT, 80);
		App->particles->AddParticle(App->particles->flamethrower, position.x + 7, position.y, Collider::Type::ENEMY_SHOT, 90);
		App->particles->AddParticle(App->particles->flamethrower, position.x + 7, position.y, Collider::Type::ENEMY_SHOT, 110);
		App->particles->AddParticle(App->particles->flamethrower, position.x + 7, position.y, Collider::Type::ENEMY_SHOT, 120);
		App->particles->AddParticle(App->particles->flamethrower, position.x + 7, position.y, Collider::Type::ENEMY_SHOT, 130);
	}

	waveRatio += waveRatioSpeed;

	if (cnt == 0 || cnt == -1 || cnt == -2) {

		currentAnim = &dedge;

	}


	if (cnt == 0) {

		int a = App->sceneLevel_1->aprendeaprogramar;
		speedXshot = (App->player->position.x + 1 - (position.x + 35)) / 60.0f;
		speedYshot = 2;

		App->particles->directionshot.speed.x = speedXshot;
		App->particles->directionshot.speed.y = speedYshot;


		App->particles->AddParticle(App->particles->directionshot, position.x + (rand() % 51 + 30), position.y + 80, Collider::Type::ENEMY_SHOT);
		App->particles->AddParticle(App->particles->directionshot, position.x + (rand() % 51 + 30), position.y + 95, Collider::Type::ENEMY_SHOT);
		App->particles->AddParticle(App->particles->directionshot, position.x + (rand() % 51 + 30), position.y + 160, Collider::Type::ENEMY_SHOT);
		App->particles->AddParticle(App->particles->directionshot, position.x + (rand() % 51 + 30), position.y + 70, Collider::Type::ENEMY_SHOT);
		App->particles->AddParticle(App->particles->directionshot, position.x + (rand() % 51 + 30), position.y + 100, Collider::Type::ENEMY_SHOT);
		App->particles->AddParticle(App->particles->directionshot, position.x + (rand() % 51 + 30), position.y + 90, Collider::Type::ENEMY_SHOT);
		App->particles->AddParticle(App->particles->directionshot, position.x + (rand() % 51 + 30), position.y + 110, Collider::Type::ENEMY_SHOT);
		App->particles->AddParticle(App->particles->directionshot, position.x + (rand() % 51 + 30), position.y + 120, Collider::Type::ENEMY_SHOT);
		
		

		cnt = -1;

	}

	if (App->render->camera.y <= -12000) {
		position.y += 2;


	}

	position.x = spawnPos.x + (waveHeight * sinf(waveRatio));

	Enemy::Update();
}