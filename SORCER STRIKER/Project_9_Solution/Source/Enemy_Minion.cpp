#include "Enemy_Minion.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "SceneLevel1.h"
#include <cstdlib>

Enemy_Minion::Enemy_Minion(int x, int y) :Enemy(x, y) {

	cnt = 1;
	tipo = Enemy_Type::MINION;
	enemieH = 24;

	flyAnim.PushBack({ 15,418,34,34 });
	flyAnim.PushBack({ 60,418,34,34 });
	flyAnim.PushBack({ 109,418,44,34 });
	flyAnim.PushBack({ 168,418,41,34 });
	flyAnim.speed = 0.1f;
	flyAnim.loop = false;
	currentAnim = &flyAnim;

	initialY = position.y;
	distanceUp = 50;

	collider = App->collisions->AddCollider({ position.x,position.y,44,34 }, Collider::Type::ENEMY, (Module*)App->enemies);

	randomNumber = rand() % 2;


	//////////////////OEE WATON SI LE DAI A LA TECLA ENE VAI A LA ZONA DEL BO
}

void Enemy_Minion::Update() {




	if( randomNumber == 0) {


	if (state == State::MovingUp) {
			
			position.x -= 2;
			position.y -= 2;

		if (position.y <= initialY - distanceUp) {
				
				state = State::MovingDown;
		}
	}
	else {
			
			position.y += 3;
	}
	}
	else {
		if (state == State::MovingUp) {
			
			position.x += 2;
			position.y -= 2;

			if (position.y <= initialY - distanceUp) {
				
				state = State::MovingDown;
			}
		}
		else {
			
			position.y += 3;
		}
	}



	

	Enemy::Update();
}