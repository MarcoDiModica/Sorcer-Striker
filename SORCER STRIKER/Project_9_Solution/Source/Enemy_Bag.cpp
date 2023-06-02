#include "Enemy_Bag.h"
#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "SceneLevel1.h"

Enemy_Bag::Enemy_Bag(int x, int y) : Enemy(x, y) 
{
	cnt = 1;
	tipo = Enemy_Type::BAG;
	enemieH = 30;

	hoverAnim.PushBack({ 176,367,36,31 });
	hoverAnim.PushBack({ 247,366,37,34 });
	hoverAnim.PushBack({ 176,367,36,31 });
	hoverAnim.PushBack({ 135,368,37,30 });
	hoverAnim.PushBack({ 215,363,28,35 });
	hoverAnim.PushBack({ 135,368,37,30 });
	hoverAnim.loop = true;
	hoverAnim.speed = 0.2f;

	currentAnim = &hoverAnim;

	collider = App->collisions->AddCollider({ position.x, position.y, 35, 30 }, Collider::Type::ENEMY, (Module*)App->enemies);

}

void Enemy_Bag::Update()
{
	position.x += mondongo;

	if (position.x < 30 + 250 || position.x > 160 + 250)
	{
		mondongo *= -1;
	}

	if (position.y > (App->render->camera.y + 100)) {
		position.y -= App->sceneLevel_1->aprendeaprogramar;
	}

	Enemy::Update();
}