#include "ModuleItems.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"

#include "Item.h"
#include "Item_MoneyBag.h"

#define SPAWN_MARGIN 50

ModuleItems::ModuleItems(bool startEnabled) : Module(startEnabled)
{
	for (uint i = 0; i < MAX_ITEMS;  ++i) {
		items[i] = nullptr;
	}
}

ModuleItems::~ModuleItems()
{

}

bool ModuleItems::Start()
{
	LOG("Loading item textures");
	texture2 = App->textures->Load("Assets/Sprites/items.png");
	itemCollectedFx = App->audio->LoadFx("Assets/Fx/coin.wav");         

	return true;
}

Update_Status ModuleItems::PreUpdate()
{
	// Remove all enemies scheduled for deletion
	for (uint i = 0; i < MAX_ITEMS; ++i)
	{
		if (items[i] != nullptr && items[i]->pendingToDelete)
		{
			delete items[i];
			items[i] = nullptr;
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleItems::Update()
{
	HandleItemsSpawn();

	for (uint i = 0; i < MAX_ITEMS; ++i)
	{
		if (items[i] != nullptr)
			items[i]->Update();
	}

	HandleItemsDespawn();

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleItems::PostUpdate()
{
	for (uint i = 0; i < MAX_ITEMS; ++i)
	{
		if (items[i] != nullptr)
			items[i]->Draw();
	}

	return Update_Status::UPDATE_CONTINUE;
}

bool ModuleItems::CleanUp()
{
	LOG("Freeing all items");

	for (uint i = 0; i < MAX_ITEMS; ++i)
	{
		if (items[i] != nullptr)
		{
			delete items[i];
			items[i] = nullptr;
		}
	}

	return true;
}

bool ModuleItems::AddItem(Item_Type type, int x, int y)
{
	bool ret = false;

	for (uint i = 0; i < MAX_ITEMS; ++i)
	{
		if (spawnQueue[i].type == Item_Type::NO_TYPE)
		{
			spawnQueue[i].type = type;
			spawnQueue[i].x = x;
			spawnQueue[i].y = y;
			ret = true;
			break;
		}
	}

	return ret;
}

void ModuleItems::HandleItemsSpawn()
{
	
	for (uint i = 0; i < MAX_ITEMS; ++i)
	{
		if (spawnQueue[i].type != Item_Type::NO_TYPE)
		{
			
			if (spawnQueue[i].x * SCREEN_SIZE < App->render->camera.x + (App->render->camera.w * SCREEN_SIZE) + SPAWN_MARGIN)
			{
				LOG("Spawning item at %d", spawnQueue[i].x * SCREEN_SIZE);

				SpawnItem(spawnQueue[i]);
				spawnQueue[i].type = Item_Type::NO_TYPE; 
			}
		}
	}
}

void ModuleItems::HandleItemsDespawn()
{
	
	for (uint i = 0; i < MAX_ITEMS; ++i)
	{
		if (items[i] != nullptr)
		{
			
			if (items[i]->position.x * SCREEN_SIZE < (App->render->camera.x) - SPAWN_MARGIN)
			{
				LOG("DeSpawning enemy at %d", items[i]->position.x * SCREEN_SIZE);

				items[i]->SetToDelete();
			}
		}
	}
}

void ModuleItems::SpawnItem(const ItemSpawnPoint& info)
{

	for (uint i = 0; i < MAX_ITEMS; ++i)
	{
		if (items[i] == nullptr)
		{
			switch (info.type)
			{
			case Item_Type::MONEY_BAG:
				items[i] = new Item_MoneyBag(info.x, info.y);
				break;
				//We will input the different types of items here
			}
			items[i]->texture2 = texture2;
			items[i]->collectedFx = itemCollectedFx;
			break;
		}
	}
}

void ModuleItems::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ITEMS; ++i)
	{
		if (items[i] != nullptr && items[i]->GetCollider() == c1)
		{
			items[i]->OnCollision(c2); //Notify the item of a collision
			break;
		}
	}
}
