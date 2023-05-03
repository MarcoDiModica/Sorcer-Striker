#include "Item_MoneyBag.h"
#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"

Item_MoneyBag::Item_MoneyBag(int x, int y) : Item(x, y)
{
	
	hoveranim.PushBack({0, 4, 35, 25 });
	hoveranim.PushBack({ 40, 4, 35, 25 });
	hoveranim.PushBack({ 81, 1, 25, 92 });
	hoveranim.PushBack({ 110, 3, 36, 28 });

	hoveranim.speed = 0.02f;
	
	currentAnim2 = &hoveranim;

	path.PushBack({ 0.0f, -0.5f }, 400);      

	path.PushBack({ 0.6f, -0.8f }, 150);
	path.PushBack({ 0.0f, -2.0f }, 500);

	collider = App->collisions->AddCollider({ 0, 0, 45, 25 }, Collider::Type::ITEM, (Module*)App->items);
}

void Item_MoneyBag::Update()
{
	path.Update();
	position = spawnPos + path.GetRelativePosition();

	if (position.y > (App->player->OPTMIZENELJUEGUITO + 90)) {
		position.y -= 3;
	}

	Item::Update();
}