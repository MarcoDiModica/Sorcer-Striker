#include "Chest.h"
#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"

Chest::Chest(int x, int y) : Enemy(x, y)
{
	cnt = 1;
	tipo = Enemy_Type::CHEST;

	hoverAnim.PushBack({ 95,332,28,27 });

	currentAnim = &hoverAnim;

	collider = App->collisions->AddCollider({ 0, 0, 28,27 }, Collider::Type::ENEMY, (Module*)App->enemies);

}

void Chest::Update()
{
	waveRatio += waveRatioSpeed;

	position.x = spawnPos.x + (waveHeight * sinf(waveRatio));

	if (position.y > (App->player->OPTMIZENELJUEGUITO + 70)) {
		position.y -= 3;
	}

	Enemy::Update();
}