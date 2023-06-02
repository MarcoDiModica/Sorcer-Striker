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

	flyAnim.PushBack({ 124,219,26,24 });
	flyAnim.PushBack({ 98,219,26,24 });
	flyAnim.PushBack({ 72,219,26,24 });
	flyAnim.PushBack({ 46,219,26,24 });
	flyAnim.PushBack({ 18,219,26,24 });
	flyAnim.speed = 0.1f;
	flyAnim.loop = false;
	currentAnim = &flyAnim;

	initialY = position.y;
	distanceUp = 50;

	collider = App->collisions->AddCollider({ position.x,position.y,26,24 }, Collider::Type::ENEMY, (Module*)App->enemies);

	randomNumber = rand() % 2;


	//////////////////OEE WATON SI LE DAI A LA TECLA ENE VAI A LA ZONA DEL BO
}

void Enemy_Minion::Update() {


	if( randomNumber == 0) {


	if (state == State::MovingUp) {
			
			position.x -= 1;
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
			
			position.x += 1;
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