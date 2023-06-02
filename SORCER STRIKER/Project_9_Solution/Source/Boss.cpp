#include "Boss.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "Boss_Right.h"
#include "Boss_Left.h"
#include "Enemy_Minion.h"
#include "SceneLevel1.h"
#include <cstdlib>
#include <ctime>


Boss::Boss(int x, int y) :Enemy(x, y) {

	cnt = 15;
	tipo = Enemy_Type::BOSS;
	enemieH = 128;

	flyAnim.PushBack({ 1199,426,90,124 });
	flyAnim.PushBack({ 1199,563, 90,124 });
	flyAnim.speed = 0.01f;
	flyAnim.loop = true;
	currentAnim = &flyAnim;

	dedge.PushBack({ 1199,281,90,124 });

	current = SDL_GetTicks();

	collider = App->collisions->AddCollider({ position.x,position.y,90,124 }, Collider::Type::ENEMY, (Module*)App->enemies);

	spawnInterval = 500;
	//////////////////OEE WATON SI LE DAI A LA TECLA ENE VAI A LA ZONA DEL BO
}

void Boss::Update() {

	position.y -= 0;

	if (position.y == App->render->camera.y) {
		next = current + spawnInterval;
	}

	if (spawnInterval <= 0) {


		spawnInterval = 500;
	}

	if (App->render->camera.y <= (-8525 - SCREEN_HEIGHT / 2))
	{
		position.y -= 1;
	}

	waveRatio += waveRatioSpeed;

	current = SDL_GetTicks();

	if (current > next) {
		App->enemies->AddEnemy(Enemy_Type::MINION, position.x + (rand() % 25 + 20), position.y);
		App->enemies->AddEnemy(Enemy_Type::MINION, position.x + (rand() % 12 + 5), position.y - (rand() % 5));
		
		spawnInterval = 500;
		next = current + spawnInterval;
	}

	if (cnt == 0) {

		currentAnim = &dedge;

	}

	position.x = spawnPos.x + (waveHeight * sinf(waveRatio));





	Enemy::Update();
}

 

