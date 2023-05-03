#include "Item.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"

Item::Item(int x, int y) : position(x, y)
{
	spawnPos = position;
}

Item::~Item()
{
	if (collider != nullptr)
		collider->pendingToDelete = true;
}

const Collider* Item::GetCollider() const
{
	return collider;
}

void Item::Update()
{
	if (currentAnim2 != nullptr)
		currentAnim2->Update();

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);
}

void Item::Draw()
{
	if (currentAnim2 != nullptr)
		App->render->Blit(texture2, position.x, position.y, &(currentAnim2->GetCurrentFrame()));
}


void Item::OnCollision(Collider* collider)
{

		App->particles->AddParticle(App->particles->explosion, position.x, position.y);
		App->audio->PlayFx(collectedFx);

		SetToDelete();


}

void Item::SetToDelete()
{
	pendingToDelete = true;
	if (collider != nullptr)
		collider->pendingToDelete = true;
}