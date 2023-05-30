#include "Clear.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "SceneLevel1.h"

Clear::Clear(int x, int y) : Enemy(x, y)
{
	cnt = 1;
	tipo = Enemy_Type::CLEAR;

	FlyAnim1.PushBack({ 947,211,81,39 });
	/*FlyAnim1.PushBack({ 44,225,26,18 });
	FlyAnim1.PushBack({ 71,230,26,14 });
	FlyAnim1.PushBack({ 97,225,26,18 });
	FlyAnim1.PushBack({ 123,220,26,24 });




	FlyAnim1.speed = 0.01f;*/

	FlyAnim1.loop = true;
	currentAnim = &FlyAnim1;

	collider = App->collisions->AddCollider({ position.x,position.y,36,34 }, Collider::Type::NONE, (Module*)App->enemies);
}

void Clear::Update()
{

	
	position.x += mondongo;

	if (position.x >= 100) {
		mondongo = 0;
	}



	position.y -= App->sceneLevel_1->aprendeaprogramar;




	Enemy::Update();
}