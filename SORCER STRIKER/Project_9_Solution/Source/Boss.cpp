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

	cnt = 10;
	tipo = Enemy_Type::BOSS;
	enemieH = 128;

	flyAnim.PushBack({ 95,418,101,128 });
	flyAnim.PushBack({ 377, 418, 101,128 });
	flyAnim.PushBack({ 654,418,101,128 });
	flyAnim.speed = 0.01f;
	currentAnim = &flyAnim;

	dedge.PushBack({653,556,98,128});

	current = SDL_GetTicks();
	
	collider = App->collisions->AddCollider({ position.x,position.y,98,128 }, Collider::Type::ENEMY, (Module*)App->enemies);

	//////////////////OEE WATON SI LE DAI A LA TECLA ENE VAI A LA ZONA DEL BO
}

void Boss::Update() {
	
	position.y -= 0;

	if (App->render->camera.y <= (-8525 - SCREEN_HEIGHT / 2))
	{
		position.y -= 1;
	}

	waveRatio += waveRatioSpeed;

	current = SDL_GetTicks();

	if (cnt == 0) {
		
		currentAnim = &dedge;
		
	}

	if (position.y == App->render->camera.y)
	{
		next = current + interval;
	}

	/*if (current > next) {
		App->enemies->AddEnemy(Enemy_Type::MINION, position.x + rand() % 51 + 30, position.y);
		interval = rand() % 20 + 21;
		next = current + interval;
	}*/


	position.x = spawnPos.x + (waveHeight * sinf(waveRatio));


	


	Enemy::Update();
}
 

