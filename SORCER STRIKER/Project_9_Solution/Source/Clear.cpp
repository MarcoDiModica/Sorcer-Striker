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

	Heroina.PushBack({ 947,213,80,37 });
	Heroina.loop = true;

	currentAnim = &Heroina;

	collider = App->collisions->AddCollider({ position.x,position.y,36,34 }, Collider::Type::NONE, (Module*)App->enemies);
}

void Clear::Update()
{
	position.x += mondongo;

	if (position.x <= 130) {
		mondongo = 0;
	}

	position.y -= App->sceneLevel_1->aprendeaprogramar;

	Enemy::Update();
}