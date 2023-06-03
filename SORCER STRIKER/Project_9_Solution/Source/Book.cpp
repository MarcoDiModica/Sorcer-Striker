#include "Book.h"
#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"

Book::Book(int x, int y) : Enemy(x, y)
{
	cnt = 1;
	tipo = Enemy_Type::BOOK;
	buk = App->audio->LoadFx("Assets/Fx/book.wav");
	enemieH = 21;

	hoverAnim.PushBack({ 110,334,17,21 });
	hoverAnim.PushBack({ 139,334,17,21 });
	hoverAnim.loop = true;
	hoverAnim.speed = 0.05f;

	currentAnim = &hoverAnim;

	collider = App->collisions->AddCollider({ 0, 0, 15, 19 }, Collider::Type::BOOK, (Module*)App->enemies);

}

void Book::Update()
{
	position.y += 1.5f;
	
	if (App->player->position.x < position.x + 15 && App->player->position.x + 32 > position.x && App->player->position.y < position.y + enemieH && App->player->position.y + 29 > position.y)
	{
		App->audio->PlayFx(buk);
		if (App->player->playershots <= 5)
		{
			App->player->playershots += 1;

		}
		SetToDelete();
	}

	Enemy::Update();
}