#include "SceneLevel1.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "SceneStageclear.h"
#include "ModuleFadeToBlack.h"
#include "ModuleItems.h"    


SceneLevel1::SceneLevel1(bool startEnabled) : Module(startEnabled)
{

}

SceneLevel1::~SceneLevel1()
{

}

// Load assets
bool SceneLevel1::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/background2.png");
	App->audio->PlayMusic("Assets/Music/stage1.ogg", 1.0f);

	//App->collisions->AddCollider({ 0, SCREEN_HEIGHT, 5, -3930 }, Collider::Type::WALL);
	//App->collisions->AddCollider({ SCREEN_WIDTH -5, SCREEN_HEIGHT, 5, -3930 }, Collider::Type::WALL);
	
	App->enemies->AddEnemy(Enemy_Type::BAG, 50, -700);
	App->enemies->AddEnemy(Enemy_Type::BAG, 80, -2400);
	App->enemies->AddEnemy(Enemy_Type::BAG, 210, -3400);
	App->enemies->AddEnemy(Enemy_Type::BAG, 150, -6300);
	App->enemies->AddEnemy(Enemy_Type::BAG, 200, -6300);
	App->enemies->AddEnemy(Enemy_Type::BAG, 30, -6300);

	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 30, -200);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 100, -200);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 170, -200);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 60, -600);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 130, -600);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 200, -600);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 30, -1000);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 100, -1000);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 170, -1000);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 60, -1400);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 130, -1400);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 200, -1400);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 30, -1800);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 100, -1800);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 170, -1800);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 60, -2200);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 130, -2200);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 200, -2200);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 30, -2600);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 100, -2600);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 170, -2600);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 60, -3000);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 130, -3000);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 200, -3000);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 30, -3400);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 100, -3400);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 170, -3400);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 60, -3800);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 130, -3800);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 200, -3800);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 30, -3800);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 100, -3800);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 170, -3800);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 60, -4200);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 130, -4200);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 200, -4200);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 30, -4600);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 100, -4600);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 170, -4600);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 60, -5000);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 130, -5000);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 200, -5000);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 30, -5400);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 100, -5400);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 170, -5400);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 60, -5800);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 130, -5800);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 200, -5800);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 30, -6200);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 100, -6200);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 170, -6200);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 60, -6600);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 200, -6600);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 30, -7000);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 100, -7000);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 170, -7000);


	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 50, -300);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 50, -600);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 50, -900);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 50, -1200);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 50, -1500);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 50, -1800);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 50, -2100);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 50, -2300);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 50, -2400);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 50, -2700);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 50, -3000);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 50, -3200);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 50, -3600);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 50, -3700);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 50, -4000);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 50, -4200);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 50, -4600);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 50, -4900);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 50, -5400);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 50, -5600);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 50, -5900);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 50, -6600);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 50, -6900);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 50, -7200);


	App->render->camera.x = 0;
	App->render->camera.y = 0;
	
	App->items->Enable();
	App->player->Enable();
	App->enemies->Enable();
	

	return ret;
}

Update_Status SceneLevel1::Update()
{
	App->render->camera.y -= 6;

	if (App->player->position.x <= 0)
	{
		App->player->position.x = 0;
	}

	if (App->player->position.x + 32 >= SCREEN_WIDTH)
	{
		App->player->position.x = SCREEN_WIDTH - 32;
	}

	if (App->player->position.y <= -6700)
	{
		App->audio->PlayFx(App->player->winFx);
		if (App->player->score > App->player->highscore) {
			App->player->highscore = App->player->score;
		}
		App->collisions->debug = false;
		App->player->lives = 3;
		App->player->score = 0;
		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneStageclear, 70);
	}
	
	return Update_Status::UPDATE_CONTINUE;
}

Update_Status SceneLevel1::PostUpdate()
{
	App->render->Blit(bgTexture, 0, -7050, NULL);

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneLevel1::CleanUp()
{
	App->player->Disable();
	App->enemies->Disable();
	App->items->Disable();

	return true;
}