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
	cuidado = App->audio->LoadFx("Assets/Fx/Warning.wav");
	App->particles->AddParticle(App->particles->tubo, 0 + space, 520, Collider::Type::NONE);
	App->particles->AddParticle(App->particles->tubo, 0 + space, 250, Collider::Type::NONE);
	App->particles->AddParticle(App->particles->tubo, 0 + space, -50, Collider::Type::NONE);
	App->particles->AddParticle(App->particles->tubo, 0 + space, -350, Collider::Type::NONE);
	App->particles->AddParticle(App->particles->tubo, 0 + space, -650, Collider::Type::NONE);
	App->particles->AddParticle(App->particles->tubo, 0 + space, -950, Collider::Type::NONE);
	App->particles->AddParticle(App->particles->tubo, 0 + space, -1250, Collider::Type::NONE);

	aprendeaprogramar = 2;

	//bag//
	App->enemies->AddEnemy(Enemy_Type::BAG, 80 + 250, -1150);


	//chest//
	App->enemies->AddEnemy(Enemy_Type::CHEST, 48 + 250, -1680);


	//mages //
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 160 + 250, -1450);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP2, 200 + 250, -1500);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 160 + 250, -1700);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP2, 200 + 250, -1700);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 175 + 250, -1960);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 175 + 250, -2250);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP2, 80 + 250, -2400);

	//bag//
	App->enemies->AddEnemy(Enemy_Type::BAG, 120 + 250, -2300);

	
	//more mages//
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 175 + 250, -3060);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP2, 80 + 250, -3060);

	//bags//
	App->enemies->AddEnemy(Enemy_Type::BAG, 70 + 250, -3500);
	App->enemies->AddEnemy(Enemy_Type::BAG, 100 + 250, -3700);


	//dragon//
	App->enemies->AddEnemy(Enemy_Type::BlUEDRAGON, 20 + 250, -3960);
	//chest//
	App->enemies->AddEnemy(Enemy_Type::CHEST, 120 + 250, -4250);

	App->enemies->AddEnemy(Enemy_Type::BlUEDRAGON, 150 + 250, -4460);



	//more dragons//
	App->enemies->AddEnemy(Enemy_Type::BlUEDRAGON, 20 + 250, -4860);


	//bag//
	App->enemies->AddEnemy(Enemy_Type::BAG, 110 + 250, -5000);

	

	//cofre//

	 App->enemies->AddEnemy(Enemy_Type::CHEST, 120 + 250, -5930 -900);


	


	// doubletank derecha //

	App->enemies->AddEnemy(Enemy_Type::DOUBLETANK, 175 + 250, -6170 - 900);
	App->enemies->AddEnemy(Enemy_Type::DOUBLETANK, 175 + 250, -6290 - 920);


	//double tank izquierda//
	App->enemies->AddEnemy(Enemy_Type::REVERSEDT, 10 + 250, -6290 - 925);

	


	App->enemies->AddEnemy(Enemy_Type::DOUBLETANK, 160 + 250, -6580 - 950);
	App->enemies->AddEnemy(Enemy_Type::DOUBLETANK, 160 + 250, -6700 - 950);



	App->enemies->AddEnemy(Enemy_Type::DOUBLETANK, 160 + 250, -6910 - 950);
	



	App->enemies->AddEnemy(Enemy_Type::REVERSEDT, 10 + 250, -7190 - 925);
	

	App->enemies->AddEnemy(Enemy_Type::DOUBLETANK, 160 + 250, -7470 - 950);



	App->enemies->AddEnemy(Enemy_Type::DOUBLETANK, 160 + 250, -7620 - 950);

	App->enemies->AddEnemy(Enemy_Type::REVERSEDT, 10 + 250, -7620 - 950);


	//boss/


	App->render->camera.x = 0 + space;
	App->render->camera.y = 0 + space;

	App->items->Enable();
	App->player->Enable();
	App->enemies->Enable();
	App->collisions->Enable();
	/*App->particles->Enable();*/

	return ret;
}

Update_Status SceneLevel1::Update()
{
	App->render->camera.y -= 2;

	if (App->player->position.x <= 0 + space)
	{
		App->player->position.x = 0 + space;
	}

	if (App->player->position.x + 32 >= (SCREEN_WIDTH / 2) + space)
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

	//globos//
	if (App->render->camera.y == -900) {
		App->enemies->AddEnemy(Enemy_Type::REDBIRD3,190 + 250, -1000);
		App->enemies->AddEnemy(Enemy_Type::REDBIRD3,205 + 250, -1030);
		App->enemies->AddEnemy(Enemy_Type::REDBIRD3,220 + 250, -1060);
		App->enemies->AddEnemy(Enemy_Type::REDBIRD3,235+ 250, -1090);
		App->enemies->AddEnemy(Enemy_Type::REDBIRD3,250  + 250, -1120);
		App->enemies->AddEnemy(Enemy_Type::REDBIRD3, 265 + 250, -1150);

	}

	if (App->render->camera.y == -1140) {

		App->enemies->AddEnemy(Enemy_Type::REDBIRD2, 50 + 250, -1150);
		App->enemies->AddEnemy(Enemy_Type::REDBIRD2, 30 + 250, -1180);
		App->enemies->AddEnemy(Enemy_Type::REDBIRD2, 20 + 250, -1210);
		App->enemies->AddEnemy(Enemy_Type::REDBIRD2, 5 + 250, -1240);
		App->enemies->AddEnemy(Enemy_Type::REDBIRD2, -10 + 250, -1270);
		App->enemies->AddEnemy(Enemy_Type::REDBIRD2, -25 + 250, -1300);

	}

	if (App->render->camera.y == -1430) {
		App->enemies->AddEnemy(Enemy_Type::REDBIRD,50  + 250, -1420);
		App->enemies->AddEnemy(Enemy_Type::REDBIRD,50  + 250, -1450);
		App->enemies->AddEnemy(Enemy_Type::REDBIRD,50  + 250, -1480);
		App->enemies->AddEnemy(Enemy_Type::REDBIRD,50  + 250, -1510);
		App->enemies->AddEnemy(Enemy_Type::REDBIRD,50  + 250, -1540);
		App->enemies->AddEnemy(Enemy_Type::REDBIRD,50  + 250, -1570);

	}


	if (App->render->camera.y == -1890) {
		App->enemies->AddEnemy(Enemy_Type::REDBIRD3, 190 + 250, -1900);
		App->enemies->AddEnemy(Enemy_Type::REDBIRD3, 205 + 250, -1930);
		App->enemies->AddEnemy(Enemy_Type::REDBIRD3, 220 + 250, -1960);
		App->enemies->AddEnemy(Enemy_Type::REDBIRD3, 235 + 250, -1990);
		App->enemies->AddEnemy(Enemy_Type::REDBIRD3, 250 + 250, -2020);
		App->enemies->AddEnemy(Enemy_Type::REDBIRD3, 265 + 250, -2050);

	}

	if (App->render->camera.y == -2540) {
		App->enemies->AddEnemy(Enemy_Type::REDBIRD2, 50 + 250, -2550);
		App->enemies->AddEnemy(Enemy_Type::REDBIRD2, 30 + 250, -2580);
		App->enemies->AddEnemy(Enemy_Type::REDBIRD2, 20 + 250, -2610);
		App->enemies->AddEnemy(Enemy_Type::REDBIRD2, 5 + 250, -2640);
		App->enemies->AddEnemy(Enemy_Type::REDBIRD2, -10 + 250, -2670);
		App->enemies->AddEnemy(Enemy_Type::REDBIRD2, -25 + 250, -2700);

	}

	if (App->render->camera.y == -2790) {
		App->enemies->AddEnemy(Enemy_Type::REDBIRD3,190 + 250, -2800);
		App->enemies->AddEnemy(Enemy_Type::REDBIRD3,205 + 250, -2830);
		App->enemies->AddEnemy(Enemy_Type::REDBIRD3,220 + 250, -2860);
		App->enemies->AddEnemy(Enemy_Type::REDBIRD3,235 + 250, -2890);
		App->enemies->AddEnemy(Enemy_Type::REDBIRD3,250 + 250, -2920);
		App->enemies->AddEnemy(Enemy_Type::REDBIRD3,265 + 250, -2950);
	}

	if (App->render->camera.y == -3230) {
		App->enemies->AddEnemy(Enemy_Type::REDBIRD, 50 + 250, -3240);
		App->enemies->AddEnemy(Enemy_Type::REDBIRD, 50 + 250, -3270);
		App->enemies->AddEnemy(Enemy_Type::REDBIRD, 50 + 250, -3300);
		App->enemies->AddEnemy(Enemy_Type::REDBIRD, 50 + 250, -3330);
		App->enemies->AddEnemy(Enemy_Type::REDBIRD, 50 + 250, -3360);
		App->enemies->AddEnemy(Enemy_Type::REDBIRD, 50 + 250, -3390);

	}

	if (App->render->camera.y == -3960) {
		App->enemies->AddEnemy(Enemy_Type::REDBIRD, 170 + 250, -3970);
		App->enemies->AddEnemy(Enemy_Type::REDBIRD, 170 + 250, -4000);
		App->enemies->AddEnemy(Enemy_Type::REDBIRD, 170 + 250, -4030);
		App->enemies->AddEnemy(Enemy_Type::REDBIRD, 170 + 250, -4060);
		App->enemies->AddEnemy(Enemy_Type::REDBIRD, 170 + 250, -4090);
		App->enemies->AddEnemy(Enemy_Type::REDBIRD, 170 + 250, -4120);

	}


	if (App->render->camera.y == -4550) {
		App->enemies->AddEnemy(Enemy_Type::REDBIRD2, 48 + 250, -4560);
		App->enemies->AddEnemy(Enemy_Type::REDBIRD2, 48 + 250, -4590);
		App->enemies->AddEnemy(Enemy_Type::REDBIRD2, 48 + 250, -4620);
		App->enemies->AddEnemy(Enemy_Type::REDBIRD2, 48 + 250, -4650);
	}

	if (App->render->camera.y == -4850) {
		App->enemies->AddEnemy(Enemy_Type::REDBIRD, 170 + 250, -4860);
		App->enemies->AddEnemy(Enemy_Type::REDBIRD, 170 + 250, -4890);
		App->enemies->AddEnemy(Enemy_Type::REDBIRD, 170 + 250, -4920);
		App->enemies->AddEnemy(Enemy_Type::REDBIRD, 170 + 250, -4950);
		App->enemies->AddEnemy(Enemy_Type::REDBIRD, 170 + 250, -4980);
		App->enemies->AddEnemy(Enemy_Type::REDBIRD, 170 + 250, -5020);

	}
	

	//tanks//
	if (App->render->camera.y == -5540 - 400) {
		App->enemies->AddEnemy(Enemy_Type::SINGLETANK, 155 + 250, -5590 - 400);
		App->enemies->AddEnemy(Enemy_Type::SINGLETANK, 195 + 250, -5590 - 400);
		App->enemies->AddEnemy(Enemy_Type::SINGLETANK, 235 + 250, -5590 - 400);

		App->enemies->AddEnemy(Enemy_Type::REVERSEST, 5 + 240, -5560 - 400);
		App->enemies->AddEnemy(Enemy_Type::REVERSEST, 40 + 240, -5560 - 400);
		App->enemies->AddEnemy(Enemy_Type::REVERSEST, 75 + 240, -5560 - 400);

	}


	if (App->render->camera.y == -5830 - 900) {
		
		App->enemies->AddEnemy(Enemy_Type::SINGLETANK, 225 + 250, -5850 - 900);
		App->enemies->AddEnemy(Enemy_Type::SINGLETANK, 225 + 250, -5890 - 900);
		App->enemies->AddEnemy(Enemy_Type::SINGLETANK, 225 + 250, -5930 - 900);
		
	}

	if (App->render->camera.y == -5950 - 900) {
		
		App->enemies->AddEnemy(Enemy_Type::SINGLETANK, 225 + 250, -5970 - 900);
		App->enemies->AddEnemy(Enemy_Type::SINGLETANK, 225 + 250, -6010 - 900);
		App->enemies->AddEnemy(Enemy_Type::SINGLETANK, 225 + 250, -6040 - 900);
	}

	if (App->render->camera.y == -5830 - 900) {

		App->enemies->AddEnemy(Enemy_Type::REVERSEST, 0 + 250, -5850 - 900);
		App->enemies->AddEnemy(Enemy_Type::REVERSEST, 0 + 250, -5890 - 900);
		App->enemies->AddEnemy(Enemy_Type::REVERSEST, 0 + 250, -5930 - 900);

	}

	if (App->render->camera.y == -5950- 900) {


		App->enemies->AddEnemy(Enemy_Type::REVERSEST, 0 + 250, -5970 - 900);
		App->enemies->AddEnemy(Enemy_Type::REVERSEST, 0 + 250, -6010 - 900);
		App->enemies->AddEnemy(Enemy_Type::REVERSEST, 0 + 250, -6040 - 900);
	}

	if (App->render->camera.y == -6310 - 925) {

		App->enemies->AddEnemy(Enemy_Type::REVERSEST, 15 + 250, -6320 - 925);
	}

	if (App->render->camera.y == -6460 - 930) {

		
		App->enemies->AddEnemy(Enemy_Type::SINGLETANK, 170 + 250, -6470 - 930);
		App->enemies->AddEnemy(Enemy_Type::SINGLETANK, 210 + 250, -6470 - 930);
	}
	
	if (App->render->camera.y == -6690 - 950) {
		App->enemies->AddEnemy(Enemy_Type::REVERSEST, 10 + 250, -6700 - 950);
		
	}
	
	if (App->render->camera.y == -6890 - 950) {
		App->enemies->AddEnemy(Enemy_Type::REVERSEST, 10 + 250, -6900 - 950);
		App->enemies->AddEnemy(Enemy_Type::REVERSEST, 50 + 250, -6900 - 950);
	}
	if (App->render->camera.y == -7260 - 950) {
		App->enemies->AddEnemy(Enemy_Type::REVERSEST, 50 + 250, -7270 - 950);
		
	}

	if (App->render->camera.y == -7180 - 925) {
		App->enemies->AddEnemy(Enemy_Type::SINGLETANK, 145 + 250, -7190 - 925);
		App->enemies->AddEnemy(Enemy_Type::SINGLETANK, 190 + 250, -7190 - 925);
	}



	// Flying lizards//
	if (App->render->camera.y == -5650 - 400) {
		App->enemies->AddEnemy(Enemy_Type::FLYINGLIZARD, 225 + 250, -5680 - 400); 
		App->enemies->AddEnemy(Enemy_Type::FLYINGLIZARD, 205 + 250, -5700 - 400); 
		App->enemies->AddEnemy(Enemy_Type::FLYINGLIZARD, 185 + 250, -5730 - 400); 
		
		App->enemies->AddEnemy(Enemy_Type::FLYINGLIZARD, 5 + 250, -5680 - 400);
		App->enemies->AddEnemy(Enemy_Type::FLYINGLIZARD, 20 + 250, -5700 - 400);
		App->enemies->AddEnemy(Enemy_Type::FLYINGLIZARD, 35 + 250, -5730 - 400);
	}

	if (App->render->camera.y == -5800 - 400) {

		App->enemies->AddEnemy(Enemy_Type::FLYINGLIZARD, 175 + 250, -5760 - 400); 
		App->enemies->AddEnemy(Enemy_Type::FLYINGLIZARD, 195 + 250, -5800 - 400); 
		App->enemies->AddEnemy(Enemy_Type::FLYINGLIZARD, 235 + 250, -5850 - 400);
		 
		App->enemies->AddEnemy(Enemy_Type::FLYINGLIZARD, 5 + 250, -5760 - 400);
		App->enemies->AddEnemy(Enemy_Type::FLYINGLIZARD, 50 + 250, -5800 - 400);
		App->enemies->AddEnemy(Enemy_Type::FLYINGLIZARD, 30 + 250, -5850 - 400);
	}

	if (App->render->camera.y == -5950 - 400) {

		App->enemies->AddEnemy(Enemy_Type::FLYINGLIZARD, 195 + 250, -5900 - 400); 
		App->enemies->AddEnemy(Enemy_Type::FLYINGLIZARD, 145 + 250, -5950 - 400); 
		App->enemies->AddEnemy(Enemy_Type::FLYINGLIZARD, 215 + 250, -6000 - 400);
		
		App->enemies->AddEnemy(Enemy_Type::FLYINGLIZARD, 70 + 250, -5900 - 400);
		App->enemies->AddEnemy(Enemy_Type::FLYINGLIZARD, 25 + 250, -5950 - 400);
		App->enemies->AddEnemy(Enemy_Type::FLYINGLIZARD, 20 + 250, -6000 - 400);
	}

	if (App->render->camera.y == -6100 - 400) {

		App->enemies->AddEnemy(Enemy_Type::FLYINGLIZARD, 230 + 250, -6050 - 400);
		App->enemies->AddEnemy(Enemy_Type::FLYINGLIZARD, 165 + 250, -6100 - 400); 
		App->enemies->AddEnemy(Enemy_Type::FLYINGLIZARD, 200 + 250, -6150 - 400);

		App->enemies->AddEnemy(Enemy_Type::FLYINGLIZARD, 50 + 250, -6050 - 400);
		App->enemies->AddEnemy(Enemy_Type::FLYINGLIZARD, 0 + 250, -6100 - 400);
		App->enemies->AddEnemy(Enemy_Type::FLYINGLIZARD, 25 + 250, -6150 - 400);

	} 
	
	if (App->render->camera.y == -9150) {

		App->enemies->AddEnemy(Enemy_Type::BOSSLEFT, 0 + 250 - 10, -9250);
		App->enemies->AddEnemy(Enemy_Type::BOSS, 90 + 250 - 10, -9250);
		App->enemies->AddEnemy(Enemy_Type::BOSSRIGHT, 180 + 250 - 10, -9250);

		App->audio->PlayMusic("Assets/Music/boss.ogg", 0.0f);

	}
	if (App->render->camera.y == -8900)
	{
		App->audio->PlayFx(cuidado);
		App->enemies->AddEnemy(Enemy_Type::WARNING, 20 + 250, -8900 - 40);
		

	}
	if (App->render->camera.y == -8960)
	{
		
		App->enemies->AddEnemy(Enemy_Type::ARROW, 110 + 250, -8960 + 35);

	}
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