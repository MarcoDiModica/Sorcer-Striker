#include "Warning.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "SceneLevel1.h"

Warning::Warning(int x, int y) : Enemy(x, y)
{
	cnt = 1;
	tipo = Enemy_Type::WARNING;
	start = SDL_GetTicks();
	next = start + interval;

	Cristal.PushBack({838,128,209,34});
	Cristal.PushBack({ 839,163,209,34 });
	Cristal.loop = true;
	Cristal.speed = 0.05f;
	
	currentAnim = &Cristal;

	collider = App->collisions->AddCollider({ position.x,position.y,36,34 }, Collider::Type::NONE, (Module*)App->enemies);
}

void Warning::Update()
{
	position.y += mondongo;

	if (position.y >= App->render->camera.y + 155) {
		mondongo = 0;
	}
	
	current = SDL_GetTicks();
	if (current > next) {
		SetToDelete();
	}
	
	position.y -= App->sceneLevel_1->aprendeaprogramar;

	Enemy::Update();
}