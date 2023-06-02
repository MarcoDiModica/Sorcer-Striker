#include "Chest.h"
#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "SceneLevel1.h"

Chest::Chest(int x, int y) : Enemy(x, y)
{
	cnt = 1;
	tipo = Enemy_Type::CHEST;
	enemieH = 28;

	hoverAnim.PushBack({ 105,306,28,28 });
	hoverAnim.PushBack({ 134,304,28,28 });
	hoverAnim.PushBack({ 167,303,28,28 });
	hoverAnim.speed = 0.1f;
	hoverAnim.loop = true;

	currentAnim = &hoverAnim;

	collider = App->collisions->AddCollider({ 0, 0, 28,28 }, Collider::Type::ENEMY, (Module*)App->enemies);

}

void Chest::Update()
{
	waveRatio += waveRatioSpeed;

	position.x = spawnPos.x + (waveHeight * sinf(waveRatio));

	if (position.y > (App->render->camera.y + 70)) {
		position.y -= App->sceneLevel_1->aprendeaprogramar;
	}

	Enemy::Update();
}