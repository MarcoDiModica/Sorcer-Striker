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
#include "ModuleParticles.h"


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

	bgTexture = App->textures->Load("Assets/Sprites/backgroundedit2edit.png");
	
	App->audio->PlayMusic("Assets/Music/stage1.ogg", 1.0f);


	App->particles->AddParticle(App->particles->tubo, 0, -50, Collider::Type::NONE);
	App->particles->AddParticle(App->particles->tubo, 0, -250, Collider::Type::NONE);
	App->particles->AddParticle(App->particles->tubo, 0, -450, Collider::Type::NONE);
	App->particles->AddParticle(App->particles->tubo, 0, -650, Collider::Type::NONE);
	App->particles->AddParticle(App->particles->tubo, 0, -850, Collider::Type::NONE);
	App->particles->AddParticle(App->particles->tubo, 0, -1050, Collider::Type::NONE);
	App->particles->AddParticle(App->particles->tubo, 0, -1250, Collider::Type::NONE);
	App->particles->AddParticle(App->particles->tubo, 0, -1450, Collider::Type::NONE);
	App->particles->AddParticle(App->particles->tubo, 0, -1650, Collider::Type::NONE);

	


	App->collisions->AddCollider({ 0, SCREEN_HEIGHT, 1, -6930 }, Collider::Type::WALL);
	App->collisions->AddCollider({ SCREEN_WIDTH -1, SCREEN_HEIGHT, 1, -6930 }, Collider::Type::WALL);

	/*App->enemies->AddEnemy(Enemy_Type::BlUEDRAGON, 50, -700);

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
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 120, -600);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 75, -900);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 160, -1200);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 50, -1500);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 200, -1800);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 50, -2100);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 90, -2300);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 20, -2400);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 50, -2700);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 110, -3000);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 50, -3200);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 150, -3600);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 70, -3700);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 185, -4000);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 50, -4200);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 130, -4600);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 50, -4900);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 180, -5400);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 90, -5600);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 50, -5900);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 20, -6600);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 110, -6900);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 190, -7200);*/
	/*App->enemies->AddEnemy(Enemy_Type::BOSS, 0, -20);*/

	//1rst wave  izquierda a derecha  //
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 48, -900);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 48, -930);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 48, -960);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 48, -990);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 48, -1020);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 48, -1050);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 48, -1080);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 48, -1110);


	//2nd wave derecha a izquierda//
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 190, -1150);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 190, -1180);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 190, -1210);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 190, -1240);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 190, -1270);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 190, -1300);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 190, -1330);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 190, -1360);


	//3rd wave  estaticos //
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 48, -1420);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 48, -1450);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 48, -1480);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 48, -1510);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 48, -1540);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 48, -1570);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 48, -1600);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 48, -1630);

	//mages //
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 160, -1700);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 200, -1700);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 175, -1960);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 175, -2250);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 80, -2400);


	//4th wave derecha a izquierda//
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 190, -2550);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 190, -2580);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 190, -2610);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 190, -2640);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 190, -2670);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 190, -2700);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 190, -2730);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 190, -2760);

	//5th wave   izquierda a derecha //
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 48, -2800);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 48, -2830);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 48, -2860);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 48, -2890);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 48, -2920);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 48, -2950);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 48, -2980);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 48, -3010);

	//more mages//
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 175, -3060);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 80, -3060);

	//dragon//
	App->enemies->AddEnemy(Enemy_Type::BlUEDRAGON, 20, -3960);
	App->enemies->AddEnemy(Enemy_Type::BlUEDRAGON, 150, -4460);

	//6th wave   izquierda a derecha //
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 48, -4560);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 48, -4590);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 48, -4620);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 48, -4650);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 48, -4680);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 48, -4710);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 48, -4740);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 48, -4770);


	//more dragons//
	App->enemies->AddEnemy(Enemy_Type::BlUEDRAGON, 20, -4860);



	App->render->camera.x = 0;
	App->render->camera.y = 0;
	
	App->items->Enable();
	App->player->Enable();
	App->enemies->Enable();
	

	return ret;
}

Update_Status SceneLevel1::Update()
{
	App->render->camera.y -= 2;

	if (App->player->position.x <= 0)
	{
		App->player->position.x = 0;
	}

	if (App->player->position.x + 32 >= SCREEN_WIDTH / 2)
	{
		App->player->position.x = SCREEN_WIDTH / 2 - 32;
	}

	if (App->player->position.y <= -16700)
	{
		/*App->audio->PlayFx(App->player->winFx);*/
		//App->particles->AddParticle(App->particles->Stage, 35, -140, Collider::Type::NONE);

		if (App->player->score > App->player->highscore) {
			App->player->highscore = App->player->score;
		}

		App->collisions->debug = false;
		App->player->lives = 3;
		App->player->score = 0;
		//App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneStageclear, 40);
	}

	if (App->player->position.y <= -5530)
	{
		App->render->camera.y += 1;
		App->player->position.y += 1;
		aprendeaprogramar = 1;
	}
	
	return Update_Status::UPDATE_CONTINUE;
}

Update_Status SceneLevel1::PostUpdate()
{

	App->render->Blit(bgTexture, 0, -14690, NULL);

	
	

	



	return Update_Status::UPDATE_CONTINUE;
}

bool SceneLevel1::CleanUp()
{
	App->player->Disable();
	App->enemies->Disable();
	App->items->Disable();


	return true;
}