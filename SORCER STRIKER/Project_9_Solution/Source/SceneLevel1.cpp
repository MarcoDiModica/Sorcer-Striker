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

	bgTexture = App->textures->Load("Assets/Sprites/inicio.png");
	bgTexture2 = App->textures->Load("Assets/Sprites/tank.png");
	bgTexture3 = App->textures->Load("Assets/Sprites/boss.png");
	eldenboy = false;

	App->audio->PlayMusic("Assets/Music/stage1.ogg", 1.0f);

	App->particles->AddParticle(App->particles->tubo, 0 + space, 520, Collider::Type::NONE);
	App->particles->AddParticle(App->particles->tubo, 0 + space, 250, Collider::Type::NONE);
	App->particles->AddParticle(App->particles->tubo, 0 + space, -50, Collider::Type::NONE);
	App->particles->AddParticle(App->particles->tubo, 0 + space, -350, Collider::Type::NONE);
	App->particles->AddParticle(App->particles->tubo, 0 + space, -650, Collider::Type::NONE);
	App->particles->AddParticle(App->particles->tubo, 0 + space, -950, Collider::Type::NONE);
	App->particles->AddParticle(App->particles->tubo, 0 + space, -1250, Collider::Type::NONE);

	////1rst wave  izquierda a derecha  //
	//App->enemies->AddEnemy(Enemy_Type::REDBIRD, 48 + 250, -900);
	//App->enemies->AddEnemy(Enemy_Type::REDBIRD, 48 + 250, -930);
	//App->enemies->AddEnemy(Enemy_Type::REDBIRD, 48 + 250, -960);
	//App->enemies->AddEnemy(Enemy_Type::REDBIRD, 48 + 250, -990);
	//App->enemies->AddEnemy(Enemy_Type::REDBIRD, 48 + 250, -1020);
	//App->enemies->AddEnemy(Enemy_Type::REDBIRD, 48 + 250, -1050);
	//App->enemies->AddEnemy(Enemy_Type::REDBIRD, 48 + 250, -1080);
	//App->enemies->AddEnemy(Enemy_Type::REDBIRD, 48 + 250, -1110);

	////bag//
	//App->enemies->AddEnemy(Enemy_Type::BAG, 80 + 250, -1150);

	////2nd wave derecha a izquierda//
	//App->enemies->AddEnemy(Enemy_Type::REDBIRD, 190 + 250, -1150);
	//App->enemies->AddEnemy(Enemy_Type::REDBIRD, 190 + 250, -1180);
	//App->enemies->AddEnemy(Enemy_Type::REDBIRD, 190 + 250, -1210);
	//App->enemies->AddEnemy(Enemy_Type::REDBIRD, 190 + 250, -1240);
	//App->enemies->AddEnemy(Enemy_Type::REDBIRD, 190 + 250, -1270);
	//App->enemies->AddEnemy(Enemy_Type::REDBIRD, 190 + 250, -1300);
	//App->enemies->AddEnemy(Enemy_Type::REDBIRD, 190 + 250, -1330);
	//App->enemies->AddEnemy(Enemy_Type::REDBIRD, 190 + 250, -1360);

	////chest//
	//App->enemies->AddEnemy(Enemy_Type::CHEST, 48 + 250, -1680);

	////3rd wave  estaticos //
	//App->enemies->AddEnemy(Enemy_Type::REDBIRD, 48 + 250, -1420);
	//App->enemies->AddEnemy(Enemy_Type::REDBIRD, 48 + 250, -1450);
	//App->enemies->AddEnemy(Enemy_Type::REDBIRD, 48 + 250, -1480);
	//App->enemies->AddEnemy(Enemy_Type::REDBIRD, 48 + 250, -1510);
	//App->enemies->AddEnemy(Enemy_Type::REDBIRD, 48 + 250, -1540);
	//App->enemies->AddEnemy(Enemy_Type::REDBIRD, 48 + 250, -1570);
	//App->enemies->AddEnemy(Enemy_Type::REDBIRD, 48 + 250, -1600);
	//App->enemies->AddEnemy(Enemy_Type::REDBIRD, 48 + 250, -1630);

	////mages //
	//App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 160 + 250, -1700);
	//App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 200 + 250, -1700);
	//App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 175 + 250, -1960);
	//App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 175 + 250, -2250);
	//App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 80 + 250, -2400);

	////bag//
	//App->enemies->AddEnemy(Enemy_Type::BAG, 140 + 250, -2300);

	////4th wave derecha a izquierda//
	//App->enemies->AddEnemy(Enemy_Type::REDBIRD, 190 + 250, -2550);
	//App->enemies->AddEnemy(Enemy_Type::REDBIRD, 190 + 250, -2580);
	//App->enemies->AddEnemy(Enemy_Type::REDBIRD, 190 + 250, -2610);
	//App->enemies->AddEnemy(Enemy_Type::REDBIRD, 190 + 250, -2640);
	//App->enemies->AddEnemy(Enemy_Type::REDBIRD, 190 + 250, -2670);
	//App->enemies->AddEnemy(Enemy_Type::REDBIRD, 190 + 250, -2700);
	//App->enemies->AddEnemy(Enemy_Type::REDBIRD, 190 + 250, -2730);
	//App->enemies->AddEnemy(Enemy_Type::REDBIRD, 190 + 250, -2760);

	////5th wave   izquierda a derecha //
	//App->enemies->AddEnemy(Enemy_Type::REDBIRD, 48 + 250, -2800);
	//App->enemies->AddEnemy(Enemy_Type::REDBIRD, 48 + 250, -2830);
	//App->enemies->AddEnemy(Enemy_Type::REDBIRD, 48 + 250, -2860);
	//App->enemies->AddEnemy(Enemy_Type::REDBIRD, 48 + 250, -2890);
	//App->enemies->AddEnemy(Enemy_Type::REDBIRD, 48 + 250, -2920);
	//App->enemies->AddEnemy(Enemy_Type::REDBIRD, 48 + 250, -2950);
	//App->enemies->AddEnemy(Enemy_Type::REDBIRD, 48 + 250, -2980);
	//App->enemies->AddEnemy(Enemy_Type::REDBIRD, 48 + 250, -3010);

	////more mages//
	//App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 175 + 250, -3060);
	//App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 80 + 250, -3060);

	////bags//
	//App->enemies->AddEnemy(Enemy_Type::BAG, 85 + 250, -3500);
	//App->enemies->AddEnemy(Enemy_Type::BAG, 170 + 250, -3700);


	////dragon//
	//App->enemies->AddEnemy(Enemy_Type::BlUEDRAGON, 20 + 250, -3960);
	////chest//
	//App->enemies->AddEnemy(Enemy_Type::CHEST, 120 + 250, -4250);

	//App->enemies->AddEnemy(Enemy_Type::BlUEDRAGON, 150 + 250, -4460);

	////6th wave   izquierda a derecha //
	//App->enemies->AddEnemy(Enemy_Type::REDBIRD, 48 + 250, -4560);
	//App->enemies->AddEnemy(Enemy_Type::REDBIRD, 48 + 250, -4590);
	//App->enemies->AddEnemy(Enemy_Type::REDBIRD, 48 + 250, -4620);
	//App->enemies->AddEnemy(Enemy_Type::REDBIRD, 48 + 250, -4650);
	//

	//

	////more dragons//
	//App->enemies->AddEnemy(Enemy_Type::BlUEDRAGON, 20 + 250, -4860);


	////bag//
	//App->enemies->AddEnemy(Enemy_Type::BAG, 170 + 250, -5000);

	//////Tanks DERECHA //

	//App->enemies->AddEnemy(Enemy_Type::SINGLETANK, 145 + 250, -5590 - 400);
	//App->enemies->AddEnemy(Enemy_Type::SINGLETANK, 185 + 250, -5590 - 400);
	//App->enemies->AddEnemy(Enemy_Type::SINGLETANK, 225 + 250, -5590 - 400);

	//App->enemies->AddEnemy(Enemy_Type::SINGLETANK, 210 + 250, -5850 - 900);
	//App->enemies->AddEnemy(Enemy_Type::SINGLETANK, 210 + 250, -5890 - 900);
	//App->enemies->AddEnemy(Enemy_Type::SINGLETANK, 210 + 250, -5930 - 900);
	//App->enemies->AddEnemy(Enemy_Type::SINGLETANK, 210 + 250, -5970 - 900);
	//App->enemies->AddEnemy(Enemy_Type::SINGLETANK, 210 + 250, -6010 - 900);
	//App->enemies->AddEnemy(Enemy_Type::SINGLETANK, 210 + 250, -6040 - 900);

	////flying lizards //
	//
	//
	//App->enemies->AddEnemy(Enemy_Type::FLYINGLIZARD, 225 + 250, -5680 - 400); 
	//App->enemies->AddEnemy(Enemy_Type::FLYINGLIZARD, 225 + 250, -5700 - 400); 
	//App->enemies->AddEnemy(Enemy_Type::FLYINGLIZARD, 225 + 250, -5730 - 400); 
	//App->enemies->AddEnemy(Enemy_Type::FLYINGLIZARD, 225 + 250, -5760 - 400); 
	//App->enemies->AddEnemy(Enemy_Type::FLYINGLIZARD, 225 + 250, -5800 - 400); 
	//App->enemies->AddEnemy(Enemy_Type::FLYINGLIZARD, 225 + 250, -5850 - 400);  
	//App->enemies->AddEnemy(Enemy_Type::FLYINGLIZARD, 225 + 250, -5900 - 400); 
	//App->enemies->AddEnemy(Enemy_Type::FLYINGLIZARD, 225 + 250, -5950 - 400); 
	//App->enemies->AddEnemy(Enemy_Type::FLYINGLIZARD, 225 + 250, -6000 - 400);
	//App->enemies->AddEnemy(Enemy_Type::FLYINGLIZARD, 225 + 250, -6050 - 400);
	//App->enemies->AddEnemy(Enemy_Type::FLYINGLIZARD, 225 + 250, -6100 - 400); 
	//App->enemies->AddEnemy(Enemy_Type::FLYINGLIZARD, 225 + 250, -6150 - 400);
	//App->enemies->AddEnemy(Enemy_Type::FLYINGLIZARD, 225 + 250, -6200 - 400);
	//App->enemies->AddEnemy(Enemy_Type::FLYINGLIZARD, 225 + 250, -6250 - 400);

	//App->enemies->AddEnemy(Enemy_Type::FLYINGLIZARD, 5 + 250, -5680 - 400);
	//App->enemies->AddEnemy(Enemy_Type::FLYINGLIZARD, 5 + 250, -5700 - 400);
	//App->enemies->AddEnemy(Enemy_Type::FLYINGLIZARD, 5 + 250, -5730 - 400);
	//App->enemies->AddEnemy(Enemy_Type::FLYINGLIZARD, 5 + 250, -5760 - 400);
	//App->enemies->AddEnemy(Enemy_Type::FLYINGLIZARD, 5 + 250, -5800 - 400);
	//App->enemies->AddEnemy(Enemy_Type::FLYINGLIZARD, 5 + 250, -5850 - 400);
	//App->enemies->AddEnemy(Enemy_Type::FLYINGLIZARD, 5 + 250, -5900 - 400);
	//App->enemies->AddEnemy(Enemy_Type::FLYINGLIZARD, 5 + 250, -5950 - 400);
	//App->enemies->AddEnemy(Enemy_Type::FLYINGLIZARD, 5 + 250, -6000 - 400);
	//App->enemies->AddEnemy(Enemy_Type::FLYINGLIZARD, 5 + 250, -6050 - 400);
	//App->enemies->AddEnemy(Enemy_Type::FLYINGLIZARD, 5 + 250, -6100 - 400);
	//App->enemies->AddEnemy(Enemy_Type::FLYINGLIZARD, 5 + 250, -6150 - 400);
	//App->enemies->AddEnemy(Enemy_Type::FLYINGLIZARD, 5 + 250, -6200 - 400);
	//App->enemies->AddEnemy(Enemy_Type::FLYINGLIZARD, 5 + 250, -6250 - 400);

	////cofre//

	// App->enemies->AddEnemy(Enemy_Type::CHEST, 120 + 250, -5930 -900);


	////tanks izquierda//
	//App->enemies->AddEnemy(Enemy_Type::REVERSEST, 5 + 250, -5560 - 400);
	//App->enemies->AddEnemy(Enemy_Type::REVERSEST, 40 + 250, -5560 - 400);
	//App->enemies->AddEnemy(Enemy_Type::REVERSEST, 75 + 250, -5560 - 400);

	//App->enemies->AddEnemy(Enemy_Type::REVERSEST, 15 + 250, -5850 - 900);
	//App->enemies->AddEnemy(Enemy_Type::REVERSEST, 15 + 250, -5890 - 900);
	//App->enemies->AddEnemy(Enemy_Type::REVERSEST, 15 + 250, -5930 -900);
	//App->enemies->AddEnemy(Enemy_Type::REVERSEST, 15 + 250, -5970 - 900);
	//App->enemies->AddEnemy(Enemy_Type::REVERSEST, 15 + 250, -6010 - 900);
	//App->enemies->AddEnemy(Enemy_Type::REVERSEST, 15 + 250, -6040 - 900);

	//// doubletank derecha //

	//App->enemies->AddEnemy(Enemy_Type::DOUBLETANK, 175 + 250, -6170 - 900);
	//App->enemies->AddEnemy(Enemy_Type::DOUBLETANK, 175 + 250, -6290 - 920);


	////double tank izquierda//
	//App->enemies->AddEnemy(Enemy_Type::REVERSEDT, 10 + 250, -6290 - 925);

	//App->enemies->AddEnemy(Enemy_Type::REVERSEST, 15 + 250, -6320 - 925);



	//App->enemies->AddEnemy(Enemy_Type::SINGLETANK, 130 + 250, -6470 - 930);
	//App->enemies->AddEnemy(Enemy_Type::SINGLETANK, 170 + 250, -6470 - 930);
	//App->enemies->AddEnemy(Enemy_Type::SINGLETANK, 210 + 250, -6470 - 930);


	//App->enemies->AddEnemy(Enemy_Type::DOUBLETANK, 160 + 250, -6580 - 950);
	//App->enemies->AddEnemy(Enemy_Type::DOUBLETANK, 160 + 250, -6700 - 950);

	//App->enemies->AddEnemy(Enemy_Type::REVERSEST, 10 + 250, -6700 - 950);
	//App->enemies->AddEnemy(Enemy_Type::REVERSEST, 50 + 250, -6700 - 950);
	//

	//App->enemies->AddEnemy(Enemy_Type::REVERSEST, 10 + 250, -6900 - 950);
	//App->enemies->AddEnemy(Enemy_Type::REVERSEST, 50 + 250, -6900 - 950);


	//App->enemies->AddEnemy(Enemy_Type::DOUBLETANK, 160 + 250, -6910 - 950);
	//App->enemies->AddEnemy(Enemy_Type::DOUBLETANK, 160 + 250, -7020 - 950);



	//App->enemies->AddEnemy(Enemy_Type::REVERSEDT, 10 + 250, -7190 - 925);
	//App->enemies->AddEnemy(Enemy_Type::REVERSEST, 50 + 250, -7270 - 950);
	//App->enemies->AddEnemy(Enemy_Type::REVERSEST, 5 + 250, -7270 - 950);

	//App->enemies->AddEnemy(Enemy_Type::SINGLETANK, 145 + 250, -7190 - 925);
	//App->enemies->AddEnemy(Enemy_Type::SINGLETANK, 190 + 250, -7190 - 925);

	//App->enemies->AddEnemy(Enemy_Type::DOUBLETANK, 160 + 250, -7470 - 950);



	//App->enemies->AddEnemy(Enemy_Type::DOUBLETANK, 160 + 250, -7620 - 950);

	//App->enemies->AddEnemy(Enemy_Type::REVERSEDT, 10 + 250, -7620 - 950);


	//boss/
	App->enemies->AddEnemy(Enemy_Type::BOSSLEFT, 0+250, -8800);
	App->enemies->AddEnemy(Enemy_Type::BOSS, 83+250, -8800);
	App->enemies->AddEnemy(Enemy_Type::BOSSRIGHT, 180+250, -8800);
	


	App->render->camera.x = 0 + space;
	App->render->camera.y = 0 + space;
	
	App->items->Enable();
	App->player->Enable();
	App->enemies->Enable();
	

	return ret;
}

Update_Status SceneLevel1::Update()
{
	App->render->camera.y -= 2;

	if (App->player->position.x <= 0 + space)
	{
		App->player->position.x = 0 + space;
	}

	if (App->player->position.x + 32 >= (SCREEN_WIDTH  / 2) + space)
	{
		App->player->position.x = (SCREEN_WIDTH / 2 - 32) + space;
	}
	//Codigo para el mensaje de warning antes del boss
	/*if (App->render->camera.y == -200) {
		App->enemies->AddEnemy(Enemy_Type::WARNING, 17, App->render->camera.y - 50);
		App->enemies->AddEnemy(Enemy_Type::ARROW, 107, App->render->camera.y - 80);
	}*/

	/*if (App->player->position.y <= -16700)
	{
		App->audio->PlayFx(App->player->winFx);
		App->particles->AddParticle(App->particles->Stage, 35, -140, Collider::Type::NONE);

		if (App->player->score > App->player->highscore) {
			App->player->highscore = App->player->score;
		}

		App->collisions->debug = false;
		App->player->lives = 3;
		App->player->score = 0;
		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneStageclear, 40);
	}*/

	if (App->render->camera.y <= -5930)
	{
		App->render->camera.y += 1;
		App->player->position.y += 1;
		aprendeaprogramar = 1;
	}
	else if (App->render->camera.y >= -880)
	{
		App->render->camera.y -= 4;
		App->player->position.y -= 4.5f;
	}
	else
	{
		eldenboy = true;
	}
	
	return Update_Status::UPDATE_CONTINUE;
}

Update_Status SceneLevel1::PostUpdate()
{

	App->render->Blit(bgTexture, 0 + space, -4200, NULL);
	App->render->Blit(bgTexture2, 0 + space, -8760, NULL);
	App->render->Blit(bgTexture3, 0 + space, -13060, NULL);

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneLevel1::CleanUp()
{
	App->player->Disable();
	App->enemies->Disable();
	App->items->Disable();


	return true;
}