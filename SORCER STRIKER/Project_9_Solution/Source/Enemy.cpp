#include "Enemy.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModuleEnemies.h"

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

			SetToDelete();
		}
		else
		{
			App->particles->AddParticle(App->particles->explosion, position.x, position.y);
			App->particles->AddParticle(App->particles->EnemyL, position.x, position.y, Collider::Type::ENEMY_SHOT);
			App->audio->PlayFx(destroyedFx);
		}
	}

	if (tipo == Enemy_Type::BAG)
	{
		if (cnt == 0) {
			App->particles->AddParticle(App->particles->explosion, position.x, position.y);
			App->audio->PlayFx(destroyedFx);
			App->particles->AddParticle(App->particles->coin, position.x, position.y, Collider::Type::PICK);

			SetToDelete();
		}
	}

	if (tipo == Enemy_Type::DOUBLETANK)
	{
		if (cnt == 0) {
			App->audio->PlayFx(destroyedFx);
			App->particles->AddParticle(App->particles->explosion, position.x + 35, position.y + 20);
			App->particles->AddParticle(App->particles->DoubleTankMark, position.x, position.y);

			SetToDelete();
		}
		else
		{
			App->particles->AddParticle(App->particles->explosion, position.x + 30, position.y + 26);
		}
	}

	if (tipo == Enemy_Type::REDBIRD)
	{
		if (cnt == 0) {
			App->particles->AddParticle(App->particles->explosion, position.x, position.y);
			App->audio->PlayFx(destroyedFx);

			SetToDelete();
		}
	}
}

void Enemy::SetToDelete()
{
	pendingToDelete = true;
	if (collider != nullptr)
		collider->pendingToDelete = true;
}