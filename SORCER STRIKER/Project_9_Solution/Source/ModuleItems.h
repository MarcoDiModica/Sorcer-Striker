#ifndef __MODULE_ITEMS_H__
#define __MODULE_ITEMS_H__

#include "Module.h"

#define MAX_ITEMS 100

enum class Item_Type 
{
	NO_TYPE,
	MONEY_BAG,

};

struct ItemSpawnPoint
{
	Item_Type type = Item_Type::NO_TYPE;
	int x, y;
};

class Item;
struct SDL_Texture;

class ModuleItems : public Module 
{
public:

	ModuleItems(bool startEnabled);

	~ModuleItems();

	bool Start() override;

	Update_Status PreUpdate() override;

	Update_Status Update() override;

	Update_Status PostUpdate() override;

	bool CleanUp() override;

	void OnCollision(Collider* c1, Collider* c2) override;

	bool AddItem(Item_Type type, int x, int y);
	
	void HandleItemsSpawn();

	void HandleItemsDespawn();

private:

	void SpawnItem(const ItemSpawnPoint& info);

private:

	ItemSpawnPoint spawnQueue[MAX_ITEMS];

	Item* items[MAX_ITEMS] = { nullptr };

	SDL_Texture* texture2 = nullptr;

	int itemCollectedFx = 0;

};

#endif // __MODULE_ITEMS_H__
