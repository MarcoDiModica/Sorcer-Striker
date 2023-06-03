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
	enemieH = 15;

	hoverAnim.PushBack({ 14,369,15,15 });
	hoverAnim.PushBack({ 33,369, 15, 15 });
	hoverAnim.PushBack({ 52,369, 15, 15});
	hoverAnim.PushBack({ 69,369, 15, 15 });
	hoverAnim.PushBack({ 85,369, 15, 15 });
	hoverAnim.PushBack({ 101,369, 15, 15 });
	hoverAnim.speed = 0.2f;
	hoverAnim.loop = true;

	currentAnim = &hoverAnim;

	collider = App->collisions->AddCollider({ 0, 0, 15, 15 }, Collider::Type::COIN, (Module*)App->enemies);

}

void Coin::Update()
{
	position.y += 1.5f;
	
	if (App->player->position.x < position.x + 15 && App->player->position.x + 32 > position.x && App->player->position.y < position.y + enemieH && App->player->position.y + 29 > position.y) 
	{
		App->player->score += 200;
		App->audio->PlayFx(App->player->coinFx);
		App->player->laserspeed -= 0.5f;
		SetToDelete();
	}

	Enemy::Update();
}