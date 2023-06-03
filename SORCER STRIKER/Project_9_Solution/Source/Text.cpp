#include "Text.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "SceneLevel1.h"

Text::Text(int x, int y) : Enemy(x, y)
{
	cnt = 1;
	tipo = Enemy_Type::TEXT;
	start = SDL_GetTicks();
	next = start + interval;

	Cristal.PushBack({ 1211,177,95,31 });
	

	currentAnim = &Cristal;

	collider = App->collisions->AddCollider({ position.x,position.y,36,34 }, Collider::Type::NONE, (Module*)App->enemies);
}

void Text::Update()
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