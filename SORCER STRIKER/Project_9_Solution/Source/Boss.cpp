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

	cnt = 40;
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

	spawnInterval = 1000;
	//////////////////OEE WATON SI LE DAI A LA TECLA ENE VAI A LA ZONA DEL BO
}

void Boss::Update() {

	position.y -= 0;

	if (position.y > App->render->camera.y + 30) {
		position.y -= 1;
	}

	
     tracker += 1;

	 if ((tracker == 500||tracker == 1500 || tracker == 3000) && cnt>0) {
		 App->particles->AddParticle(App->particles->flamethrower, position.x + 42, position.y, Collider::Type::ENEMY_SHOT, 80);
		 App->particles->AddParticle(App->particles->flamethrower, position.x + 42, position.y, Collider::Type::ENEMY_SHOT, 90);
		 App->particles->AddParticle(App->particles->flamethrower, position.x + 42, position.y, Collider::Type::ENEMY_SHOT, 110);
		 App->particles->AddParticle(App->particles->flamethrower, position.x + 42, position.y, Collider::Type::ENEMY_SHOT, 120);
		 App->particles->AddParticle(App->particles->flamethrower, position.x + 42, position.y, Collider::Type::ENEMY_SHOT, 130);
	 }
	

	waveRatio += waveRatioSpeed;

	current = SDL_GetTicks();


	if (current > next && App->render->camera.y < -9200) {
		App->enemies->AddEnemy(Enemy_Type::MINION, position.x + (rand() % 25 + 20), position.y+rand()%10);
		App->enemies->AddEnemy(Enemy_Type::MINION, position.x + (rand() % 12 + 5), position.y - (rand() % 10));
		
		spawnInterval = 1000;
		next = current + spawnInterval;
	}

	if (cnt == 0) {

		currentAnim = &dedge;

	}

	position.x = spawnPos.x + (waveHeight * sinf(waveRatio));





	Enemy::Update();
}

 

