#include "Stage.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "SceneLevel1.h"

Stage::Stage(int x, int y) : Enemy(x, y)
{
	cnt = 1;
	tipo = Enemy_Type::STAGE;
	
	Cristal.PushBack({848,211,97,47});
	Cristal.loop = true;

	currentAnim = &Cristal;

	collider = App->collisions->AddCollider({ position.x,position.y,36,34 }, Collider::Type::NONE, (Module*)App->enemies);
}

void Stage::Update()
{
	position.x += mondongo;

	if (position.x >= 35 + 250) {
		mondongo = 0;
	}

	position.y -= App->sceneLevel_1->aprendeaprogramar;

	Enemy::Update();
}