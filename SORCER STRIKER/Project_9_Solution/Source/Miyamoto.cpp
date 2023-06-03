#include "Miyamoto.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "SceneLevel1.h"

Miyamoto::Miyamoto(int x, int y) : Enemy(x, y)
{
	cnt = 1;
	tipo = Enemy_Type::MIYAMOTO;
	start = SDL_GetTicks();
	next = start + interval;

	Cristal.PushBack({ 1127,127,84,83 });
	
	Cristal.speed = 0.05f;

	currentAnim = &Cristal;

	collider = App->collisions->AddCollider({ position.x,position.y,36,34 }, Collider::Type::NONE, (Module*)App->enemies);
}

void Miyamoto::Update()
{
	position.y += mondongo;

	if (position.y >= App->render->camera.y + 100) {
		mondongo = 0;
	}

	current = SDL_GetTicks();
	if (current > next) {
		SetToDelete();
	}

	position.y -= App->sceneLevel_1->aprendeaprogramar;

	Enemy::Update();
}