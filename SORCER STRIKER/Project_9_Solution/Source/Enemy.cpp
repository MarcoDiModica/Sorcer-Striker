#include "Enemy.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"

Enemy::Enemy(int x, int y) : position(x, y)
{
	spawnPos = position;
}

Enemy::~Enemy()
{
	if (collider != nullptr)
		collider->pendingToDelete = true;
}

const Collider* Enemy::GetCollider() const
{
	return collider;
}

void Enemy::Update()
{
	if (currentAnim != nullptr)
		currentAnim->Update();

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);
}

void Enemy::Draw()
{
	if (currentAnim != nullptr)
		App->render->Blit(texture, position.x, position.y, &(currentAnim->GetCurrentFrame()));
}

void Enemy::OnCollision(Collider* collider)
{
	cnt--;
	
	if (tipo == Enemy_Type::BROWNSHIP) 
	{
		if (cnt == 0) {
			App->particles->AddParticle(App->particles->explosion, position.x, position.y);
			App->audio->PlayFx(destroyedFx);

			App->player->score += 50;

			SetToDelete();
		}
		else if (cnt == 1)
		{
			App->particles->AddParticle(App->particles->explosion, position.x, position.y);
			App->audio->PlayFx(destroyedFx);
			App->player->score += 10;
			Anim2 = Anim3;
			currentAnim = &Anim2;
		}
		else if (cnt == 2)
		{
			App->particles->AddParticle(App->particles->explosion, position.x, position.y);
			App->audio->PlayFx(destroyedFx);
			App->player->score += 10;
			currentAnim = &Anim2;
		}	
	}

	if (tipo == Enemy_Type::BAG)
	{
		if (cnt == 0) {
			App->particles->AddParticle(App->particles->explosion, position.x, position.y);
			App->audio->PlayFx(destroyedFx);
			
			SetToDelete();
			App->enemies->AddEnemy(Enemy_Type::COIN, position.x, position.y);
		}

	}

	if (tipo == Enemy_Type::CHEST)
	{
		if (cnt == 0) {
			App->particles->AddParticle(App->particles->explosion, position.x, position.y);
			App->audio->PlayFx(destroyedFx);

			SetToDelete();
			App->enemies->AddEnemy(Enemy_Type::BOOK, position.x, position.y);
		}

	}

	if (tipo == Enemy_Type::DOUBLETANK)
	{
		if (cnt == 0) {
			App->audio->PlayFx(destroyedFx);
			App->particles->AddParticle(App->particles->DoubleTankMark, position.x, position.y);
			App->particles->AddParticle(App->particles->InsaneEXplosion, position.x , position.y -10);


			//rumble when killed the doubletank
			App->input->ShakeController(0, 60, 0.2f);
			App->player->score += 100;
			
			SetToDelete();
		}
		else
		{
			App->particles->AddParticle(App->particles->explosion, collider->rect.x - 15, position.y + 26);
			App->player->score += 10;
		}
	}

	if (tipo == Enemy_Type::REDBIRD)
	{
		if (cnt == 0) {
			App->particles->AddParticle(App->particles->explosion, position.x, position.y);
			App->audio->PlayFx(destroyedFx);

			App->player->score += 50;

			SetToDelete();
		}
	}

	if (tipo == Enemy_Type::SINGLETANK)
	{
		if (cnt == 0) {
			App->audio->PlayFx(destroyedFx);
			App->particles->AddParticle(App->particles->SingleTankMark, position.x, position.y);
			App->particles->AddParticle(App->particles->BigExplosion, position.x - 8, position.y + 5);
			

			App->player->score += 100;

			SetToDelete();
		}
		else
		{
			App->particles->AddParticle(App->particles->explosion, collider->rect.x - 15, position.y);
			App->player->score += 10;
			App->audio->PlayFx(destroyedFx);
		}
	}
	
	if (tipo == Enemy_Type::BlUEDRAGON)
	{
		if (cnt == 0) {
			App->audio->PlayFx(destroyedFx);
			App->particles->AddParticle(App->particles->InsaneEXplosion, position.x + 20 , position.y + 20);

			App->player->score += 100;

			SetToDelete();
		}
		else
		{
			App->particles->AddParticle(App->particles->BigExplosion, collider->rect.x - 25, position.y + 76);
			App->audio->PlayFx(destroyedFx);
			App->player->score += 10;
		}
	}

	if (tipo == Enemy_Type::FLYINGLIZARD)
	{
		if (cnt == 0) {
			App->audio->PlayFx(destroyedFx);
			App->particles->AddParticle(App->particles->explosion, position.x, position.y);

			App->player->score += 100;

			SetToDelete();
		}
	}

	if (tipo == Enemy_Type::REVERSEST)
	{
		if (cnt == 0) {
			App->audio->PlayFx(destroyedFx);
			App->particles->AddParticle(App->particles->SingleTankMark, position.x- 3, position.y- 3);
			App->particles->AddParticle(App->particles->BigExplosion, position.x - 8, position.y + 5);

			App->player->score += 100;

			SetToDelete();
		}
		else
		{
			App->particles->AddParticle(App->particles->explosion, collider->rect.x - 15, position.y);
			App->player->score += 10;
			App->audio->PlayFx(destroyedFx);
		}
	}

	if (tipo == Enemy_Type::REVERSEDT)
	{
		if (cnt == 0) {
			App->audio->PlayFx(destroyedFx);
			App->particles->AddParticle(App->particles->DoubleTankMark, position.x, position.y);
			App->particles->AddParticle(App->particles->InsaneEXplosion, position.x, position.y - 10);

			//rumble when killed the doubletank
			App->input->ShakeController(0, 60, 0.2f);
			App->player->score += 100;

			SetToDelete();
		}
		else
		{
			App->particles->AddParticle(App->particles->explosion, collider->rect.x - 15, position.y + 26);
			App->player->score += 10;
		}
	}
}

void Enemy::SetToDelete()
{
	pendingToDelete = true;
	if (collider != nullptr)
		collider->pendingToDelete = true;
}