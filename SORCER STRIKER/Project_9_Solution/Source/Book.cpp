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

	hoverAnim.PushBack({ 39,333,15,19 });
	hoverAnim.PushBack({ 15,333,15,19 });
	hoverAnim.loop = true;
	hoverAnim.speed = 0.05f;

	currentAnim = &hoverAnim;

	collider = App->collisions->AddCollider({ 0, 0, 15, 19 }, Collider::Type::BOOK, (Module*)App->enemies);

}

void Book::Update()
{
	position.y += 1.5f;
	
	if (position.x >= App->player->position.x && position.x + 11 <= App->player->position.x + 32 && position.y + 11 >= App->player->position.y)
	{
		/*App->audio->PlayFx(App->player->coinFx);*/

		SetToDelete();
	}

	Enemy::Update();
}