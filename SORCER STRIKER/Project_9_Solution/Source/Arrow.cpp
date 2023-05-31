#include "Arrow.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "SceneLevel1.h"

Arrow::Arrow(int x, int y) : Enemy(x, y)
{
	cnt = 1;
	tipo = Enemy_Type::ARROW;
	start = SDL_GetTicks();
	next = start + interval;

	Cristal.PushBack({ 1075,126,39,39 });
	Cristal.PushBack({  });
	Cristal.loop = true;
	Cristal.speed = 0.05f;

	currentAnim = &Cristal;

	collider = App->collisions->AddCollider({ position.x,position.y,36,34 }, Collider::Type::NONE, (Module*)App->enemies);
}

void Arrow::Update()
{
	position.y += mondongo;

	if (position.y >= App->render->camera.y + 30) {
		mondongo = 0;
	}

	current = SDL_GetTicks();
	if (current > next) {
		SetToDelete();
	}

	position.y -= App->sceneLevel_1->aprendeaprogramar;

	Enemy::Update();
}