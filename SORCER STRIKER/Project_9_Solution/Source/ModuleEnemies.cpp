#include "ModuleEnemies.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"

#include "Enemy.h"
#include "Enemy_RedBird.h"
#include "Enemy_BrownShip.h"
#include "Enemy_Bag.h"
#include "Enemy_SingleTank.h"
#include "Enemy_DoubleTank.h"
#include "Enemy_FlyingLizard.h"
#include "Enemy_BlueDragon.h"
#include "Boss.h"
#include "coin.h"
#include "chest.h"
#include "book.h"

#include "Stage.h"
#include "Clear.h"

#include "ReverseDT.h"
#include "ReverseST.h"


#define SPAWN_MARGIN 50


ModuleEnemies::ModuleEnemies(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
}

ModuleEnemies::~ModuleEnemies()
{

}

bool ModuleEnemies::Start()
{
	texture = App->textures->Load("Assets/Sprites/enemies2.png");
	enemyDestroyedFx = App->audio->LoadFx("Assets/Fx/explosion.wav");

	return true;
}


Update_Status ModuleEnemies::PreUpdate()
{
	// Remove all enemies scheduled for deletion
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->pendingToDelete)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleEnemies::Update()
{
	HandleEnemiesSpawn();

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr)
			enemies[i]->Update();
	}

	HandleEnemiesDespawn();

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleEnemies::PostUpdate()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
			enemies[i]->Draw();
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEnemies::CleanUp()
{
	LOG("Freeing all enemies");

	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return true;
}

bool ModuleEnemies::AddEnemy(Enemy_Type type, int x, int y)
{
	bool ret = false;

	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(spawnQueue[i].type == Enemy_Type::NO_TYPE)
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

void ModuleEnemies::HandleEnemiesSpawn()
{
	// Iterate all the enemies queue
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (spawnQueue[i].type != Enemy_Type::NO_TYPE)
		{
			// Spawn a new enemy if the screen has reached a spawn position
			if (spawnQueue[i].x * SCREEN_SIZE < App->render->camera.x + (App->render->camera.w * SCREEN_SIZE) + SPAWN_MARGIN)
			{
				LOG("Spawning enemy at %d", spawnQueue[i].x * SCREEN_SIZE);

				SpawnEnemy(spawnQueue[i]);
				spawnQueue[i].type = Enemy_Type::NO_TYPE; // Removing the newly spawned enemy from the queue
			}
		}
	}
}

void ModuleEnemies::HandleEnemiesDespawn()
{
	// Iterate existing enemies
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			// Delete the enemy when it has reached the end of the screen
			if (enemies[i]->position.x * SCREEN_SIZE < (App->render->camera.x) - SPAWN_MARGIN)
			{
				LOG("DeSpawning enemy at %d", enemies[i]->position.x * SCREEN_SIZE);

				enemies[i]->SetToDelete();
			}
		}
	}
}

void ModuleEnemies::SpawnEnemy(const EnemySpawnpoint& info)
{
	// Find an empty slot in the enemies array
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] == nullptr)
		{
			switch (info.type)
			{
				case Enemy_Type::REDBIRD:
					enemies[i] = new Enemy_RedBird(info.x, info.y);
					break;
				case Enemy_Type::CHEST:
					enemies[i] = new Chest(info.x, info.y);
					break;
				case Enemy_Type::BOOK:
					enemies[i] = new Book(info.x, info.y);
					break;
				case Enemy_Type::BROWNSHIP:
					enemies[i] = new Enemy_BrownShip(info.x, info.y);
					break;
				case Enemy_Type::BAG:
					enemies[i] = new Enemy_Bag(info.x, info.y);
					break;
				case Enemy_Type::COIN:
					enemies[i] = new Coin(info.x, info.y);
					break;
				case Enemy_Type::SINGLETANK:
					enemies[i] = new Enemy_SingleTank(info.x, info.y);
					break;
				case Enemy_Type::DOUBLETANK:
					enemies[i] = new Enemy_DoubleTank(info.x, info.y);
					break;
				case Enemy_Type::FLYINGLIZARD:
					enemies[i] = new Enemy_FlyingLizard(info.x, info.y);
					break;
				case Enemy_Type::BlUEDRAGON:
					enemies[i] = new Enemy_BlueDragon(info.x, info.y);
					break;
				case Enemy_Type::BOSS:
					enemies[i] = new Boss(info.x, info.y);
					break;
				case Enemy_Type::STAGE:
					enemies[i] = new Stage(info.x, info.y);
					break;
				case Enemy_Type::CLEAR:
					enemies[i] = new Stage(info.x, info.y);
				case Enemy_Type::REVERSEDT:
					enemies[i] = new ReverseDT(info.x, info.y);
					break;
				case Enemy_Type::REVERSEST:
					enemies[i] = new ReverseST(info.x, info.y);
					break;

			}
			enemies[i]->texture = texture;
			enemies[i]->destroyedFx = enemyDestroyedFx;
			break;
		}
	}
}

void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)
{
	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
		{
			enemies[i]->OnCollision(c2); //Notify the enemy of a collision
			break;
		}
	}
}