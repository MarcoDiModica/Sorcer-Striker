#include "Coin.h"
#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"

Coin::Coin(int x, int y) : Enemy(x, y)
{
	cnt = 1;
	tipo = Enemy_Type::COIN;

	hoverAnim.PushBack({ 22,377,15,15 });
	hoverAnim.PushBack({ 44, 379, 15, 15 });
	hoverAnim.PushBack({ 66, 379, 15, 15});
	hoverAnim.PushBack({ 82, 379, 15, 15 });
	hoverAnim.PushBack({ 99, 379, 15, 15 });
	hoverAnim.PushBack({ 115, 379, 15, 15 });
	hoverAnim.speed = 0.2f;
	hoverAnim.loop = true;

	currentAnim = &hoverAnim;

	collider = App->collisions->AddCollider({ 0, 0, 15, 15 }, Collider::Type::COIN, (Module*)App->enemies);

}

void Coin::Update()
{
	position.y += 1.5f;
	
	if (position.x >= App->player->position.x && position.x + 11 <= App->player->position.x + 32 && position.y + 11 >= App->player->position.y)
	{
		App->player->score += 200;
		App->audio->PlayFx(App->player->coinFx);
		App->player->laserspeed -= 0.5f;
		SetToDelete();
	}

	Enemy::Update();
}