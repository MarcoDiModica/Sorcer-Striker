#include "Enemy.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include <SDL_mixer/include/SDL_mixer.h>
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

	if (position.y > App->render->camera.y + SCREEN_HEIGHT)
	{
		SetToDelete();
	}

	if (tipo == Enemy_Type::MIYAMOTO && !text) {
		if (position.y >= App->render->camera.y + 100) {
			App->enemies->AddEnemy(Enemy_Type::TEXT, 84 + 250, App->render->camera.y + 178);
			text = true;
		}
	}

	if (tipo == Enemy_Type::CLEAR && !miya) {
		if (position.x <= 140 + 250) {
			App->enemies->AddEnemy(Enemy_Type::MIYAMOTO, 90 + 250, App->render->camera.y - 80);
			miya = true;
		}
	}

	if (tipo == Enemy_Type::BOSS && !win) {
		if (cnt == 0) {
			
			win = true;
		}
	}
}

void Enemy::Draw()
{
	if (currentAnim != nullptr)
		App->render->Blit(texture, position.x, position.y, &(currentAnim->GetCurrentFrame()));
}

void Enemy::OnCollision(Collider* collider)
{
	if (position.y + enemieH> App->render->camera.y)
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

		if (tipo == Enemy_Type::BROWNSHIP2)
		{
			if (cnt == 0)
			{
				App->particles->AddParticle(App->particles->explosion, position.x, position.y);
				App->audio->PlayFx(destroyedFx);
				App->player->score += 50;

				SetToDelete();
			}
			else
			{
				App->particles->AddParticle(App->particles->explosion, position.x, position.y);
				App->audio->PlayFx(destroyedFx);
				App->player->score += 10;
			}
		}

		if (tipo == Enemy_Type::BAG)
		{
			if (cnt == 0) {
				App->particles->AddParticle(App->particles->explosion, position.x, position.y);
				App->audio->PlayFx(destroyedFx);
				App->player->score += 20;
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
				App->particles->AddParticle(App->particles->InsaneEXplosion, position.x, position.y - 10);
				App->input->ShakeController(0, 60, 0.2f);
			}
			else
			{
				App->particles->AddParticle(App->particles->explosion, collider->rect.x - 15, position.y + 26);
				App->audio->PlayFx(destroyedFx);
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
			else
			{
				App->particles->AddParticle(App->particles->explosion, position.x, position.y);
				App->audio->PlayFx(destroyedFx);

				App->player->score += 10;
			}
		}

		if (tipo == Enemy_Type::REDBIRD2)
		{
			if (cnt == 0) {
				App->particles->AddParticle(App->particles->explosion, position.x, position.y);
				App->audio->PlayFx(destroyedFx);

				App->player->score += 50;

				SetToDelete();
			}
			else
			{
				App->particles->AddParticle(App->particles->explosion, position.x, position.y);
				App->audio->PlayFx(destroyedFx);

				App->player->score += 10;
			}
		}

		if (tipo == Enemy_Type::REDBIRD3)
		{
			if (cnt == 0) {
				App->particles->AddParticle(App->particles->explosion, position.x, position.y);
				App->audio->PlayFx(destroyedFx);

				App->player->score += 50;

				SetToDelete();
			}
			else
			{
				App->particles->AddParticle(App->particles->explosion, position.x, position.y);
				App->audio->PlayFx(destroyedFx);

				App->player->score += 10;
			}
		}

		if (tipo == Enemy_Type::SINGLETANK)
		{
			if (cnt == 0) {
				App->audio->PlayFx(destroyedFx);

				App->particles->AddParticle(App->particles->BigExplosion, position.x - 8, position.y + 5);


				App->player->score += 100;


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
				App->audio->PlayFx(App->player->bigexplioson);
				App->particles->AddParticle(App->particles->InsaneEXplosion, position.x + 20, position.y + 20);
				App->input->ShakeController(0, 60, 0.2f);
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

		if (tipo == Enemy_Type::BlUEDRAGON2)
		{
			if (cnt == 0) {
				App->audio->PlayFx(App->player->bigexplioson);
				App->particles->AddParticle(App->particles->InsaneEXplosion, position.x + 20, position.y + 20);
				App->input->ShakeController(0, 60, 0.2f);
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

		if (tipo == Enemy_Type::MINION)
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
				App->particles->AddParticle(App->particles->BigExplosion, position.x - 8, position.y + 5);

				App->player->score += 100;
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

				App->particles->AddParticle(App->particles->InsaneEXplosion, position.x, position.y - 10);

				//rumble when killed the doubletank
				App->input->ShakeController(0, 60, 0.2f);
				App->player->score += 100;

			}
			else
			{
				App->particles->AddParticle(App->particles->explosion, collider->rect.x - 15, position.y + 26);
				App->audio->PlayFx(destroyedFx);
				App->player->score += 10;
			}
		}

		if (tipo == Enemy_Type::BOSSLEFT)
		{
			if (cnt == 0) {
				App->input->ShakeController(0, 100, 0.3f);
				
				App->audio->PlayFx(App->player->pkfire);
				App->particles->AddParticle(App->particles->InsaneEXplosion, position.x + 40, position.y);
				App->particles->AddParticle(App->particles->explosion, position.x + 25, position.y - 8);
				App->particles->AddParticle(App->particles->explosion, position.x + 20, position.y + 25);
				App->particles->AddParticle(App->particles->BigExplosion, position.x + 55, position.y + 60);
				App->particles->AddParticle(App->particles->explosion, position.x + 60, position.y - 10);
				App->player->score += 1000;

				App->particles->AddParticle(App->particles->flamethrower, position.x + 130, position.y, Collider::Type::ENEMY_SHOT, 80);
				App->particles->AddParticle(App->particles->flamethrower, position.x + 130, position.y, Collider::Type::ENEMY_SHOT, 90);
				App->particles->AddParticle(App->particles->flamethrower, position.x + 130, position.y, Collider::Type::ENEMY_SHOT, 110);
				App->particles->AddParticle(App->particles->flamethrower, position.x + 130, position.y, Collider::Type::ENEMY_SHOT, 120);
				App->particles->AddParticle(App->particles->flamethrower, position.x + 130, position.y, Collider::Type::ENEMY_SHOT, 130);
			}
			else
			{
				App->particles->AddParticle(App->particles->explosion, collider->rect.x-17, position.y + 46);
				App->audio->PlayFx(destroyedFx);
				
				App->player->score += 100;
			}
		}

		if (tipo == Enemy_Type::BOSSRIGHT)
		{
			if (cnt == 0) {
				App->input->ShakeController(0, 100, 0.3f);
				
				App->audio->PlayFx(App->player->pkfire);
				App->particles->AddParticle(App->particles->InsaneEXplosion, position.x + 30, position.y);
				App->particles->AddParticle(App->particles->explosion, position.x + 15, position.y - 8);
				App->particles->AddParticle(App->particles->explosion, position.x + 10, position.y + 25);
				App->particles->AddParticle(App->particles->BigExplosion, position.x + 45, position.y + 60);
				App->particles->AddParticle(App->particles->explosion, position.x + 50, position.y - 10);
				App->player->score += 1000;

				
				App->particles->AddParticle(App->particles->flamethrower, position.x - 50, position.y, Collider::Type::ENEMY_SHOT, 80);
				App->particles->AddParticle(App->particles->flamethrower, position.x - 50, position.y, Collider::Type::ENEMY_SHOT, 90);
				App->particles->AddParticle(App->particles->flamethrower, position.x - 50, position.y, Collider::Type::ENEMY_SHOT, 110);
				App->particles->AddParticle(App->particles->flamethrower, position.x - 50, position.y, Collider::Type::ENEMY_SHOT, 120);
				App->particles->AddParticle(App->particles->flamethrower, position.x - 50, position.y, Collider::Type::ENEMY_SHOT, 130);
			}
			else
			{
				App->particles->AddParticle(App->particles->explosion, collider->rect.x-17, position.y + 46);
				App->audio->PlayFx(destroyedFx);
				App->player->score += 100;
			}
		}

		if (tipo == Enemy_Type::BOSS)
		{
			if (cnt == 0) {
				App->input->ShakeController(0, 100, 0.3f);
				Mix_PauseMusic();
				App->audio->PlayFx(App->player->bigexplioson, 2);
				App->particles->AddParticle(App->particles->InsaneEXplosion, position.x - 25, position.y, Collider::Type::NONE, 9);
				App->particles->AddParticle(App->particles->InsaneEXplosion, position.x, position.y, Collider::Type::NONE, 12);
				App->particles->AddParticle(App->particles->InsaneEXplosion, position.x + 25, position.y, Collider::Type::NONE, 15);
				App->particles->AddParticle(App->particles->InsaneEXplosion, position.x + 50, position.y, Collider::Type::NONE, 17);
				App->particles->AddParticle(App->particles->InsaneEXplosion, position.x + 55, position.y+25, Collider::Type::NONE, 20);
				App->particles->AddParticle(App->particles->InsaneEXplosion, position.x - 25, position.y+30, Collider::Type::NONE, 21);
				App->particles->AddParticle(App->particles->InsaneEXplosion, position.x, position.y+28, Collider::Type::NONE, 22);
				App->particles->AddParticle(App->particles->InsaneEXplosion, position.x + 20, position.y+23, Collider::Type::NONE, 24);
				App->particles->AddParticle(App->particles->InsaneEXplosion, position.x + 75, position.y+17, Collider::Type::NONE, 27);
				App->particles->AddParticle(App->particles->InsaneEXplosion, position.x - 25, position.y-30, Collider::Type::NONE, 30);
				App->particles->AddParticle(App->particles->InsaneEXplosion, position.x, position.y-19, Collider::Type::NONE, 15);
				App->particles->AddParticle(App->particles->InsaneEXplosion, position.x - 40, position.y-12, Collider::Type::NONE, 8);
				App->particles->AddParticle(App->particles->InsaneEXplosion, position.x - 33, position.y-30, Collider::Type::NONE, 9);
				App->particles->AddParticle(App->particles->InsaneEXplosion, position.x - 70, position.y + 5, Collider::Type::NONE, 31);
				App->particles->AddParticle(App->particles->InsaneEXplosion, position.x - 65, position.y - 22, Collider::Type::NONE, 18);
				//A�adir explosiones para disimular que hemos deleteado todos los enemigos : OPCION 1
				
				App->enemies->Disable();
				App->enemies->Enable();
				
				App->audio->PlayMusic("Assets/Music/win.ogg", 0.0f);
				/*App->audio->PlayFx(App->player->winFx);*/
				if (App->player->score > App->player->highscore) {
					App->player->highscore = App->player->score;
				}

				App->enemies->AddEnemy(Enemy_Type::STAGE, -20 + 250, App->render->camera.y + 50);
				App->enemies->AddEnemy(Enemy_Type::CLEAR, SCREEN_WIDTH / 2 - 30 + 250, App->render->camera.y + 50);
				//App->enemies->AddEnemy(Enemy_Type::MIYAMOTO, 90 + 250, App->render->camera.y - 80);

				App->player->collider->type = Collider::Type::NONE;

				App->player->start = SDL_GetTicks();
				App->player->next = App->player->start + App->player->interval;
				App->player->crack = !App->player->crack;
				App->player->score += 10000;
			}
			else
			{
				App->particles->AddParticle(App->particles->explosion, collider->rect.x - 17, position.y + 76); /////////////////
				App->audio->PlayFx(destroyedFx);
				App->player->score += 100;
			}
		}
		
	}
}

void Enemy::SetToDelete()
{
	pendingToDelete = true;
	if (collider != nullptr)
		collider->pendingToDelete = true;
}