#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "Boss.h"
#include "Miyamoto.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "ModuleCollisions.h"
#include "ModuleWindow.h"
#include <random>
#include <chrono>
#include <SDL_mixer/include/SDL_mixer.h>
#include "SceneLevel1.h"


#include <stdio.h>

//bool Animation::Finished() const
//{
//	return currentFrame >= totalFrames && !loop && !pingpong;
//}


ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled)
{
	// idle animation
	idleAnim.PushBack({ 138, 154, 32, 29 });
	idleAnim.PushBack({ 172, 154, 32, 29 });
	idleAnim.PushBack({ 204, 154, 32, 29 });
	idleAnim.loop = true;
	idleAnim.speed = 0.1f;

	// move leftwards
	idleAnim.PushBack({ 138, 154, 32, 29 });
	leftAnim.PushBack({ 85, 153, 28, 29 });
	leftAnim.PushBack({ 113, 153, 24, 29 });
	leftAnim.loop = false;
	leftAnim.speed = 0.2f;

	// Move rightwards
	idleAnim.PushBack({ 138, 154, 32, 29 });
	rightAnim.PushBack({ 126, 65, 28, 29 });
	rightAnim.PushBack({ 101, 66, 24, 29 });
	rightAnim.loop = false;
	rightAnim.speed = 0.2f;

	idleAnim.PushBack({ 138, 154, 32, 29 });
	bright1.PushBack({ 241, 154, 32, 29 });
	bright1.PushBack({ 138, 154, 32, 29 });
	bright1.PushBack({ 241, 154, 32, 29 });
	bright1.PushBack({ 138, 154, 32, 29 });
	bright1.PushBack({ 241, 154, 32, 29 });
	bright1.PushBack({ 138, 154, 32, 29 });
	bright1.loop = true;
	bright1.speed = 0.5f;

	boost.PushBack({ 188, 126, 44, 28 });
	boost.loop = true;
	boost.speed = 0.07f;

	//a flip animation for the player at the start of SceneLevel1
	
	//1
	flip.PushBack({ 127, 65, 31, 30 });
	//2
	flip.PushBack({ 101, 64, 24, 30 });
	//3
	flip.PushBack({ 153, 65, 21, 28 });
	//4
	flip.PushBack({ 175, 65, 29, 26 });
	//5
	flip.PushBack({ 204, 66, 32, 26 });
	//6
	flip.PushBack({ 36, 153, 29, 32 });
	//7
	flip.PushBack({ 63, 154, 26, 30 });
	//8
	flip.PushBack({ 85, 153, 30, 32 });
	// 0
	flip.PushBack({ 138, 154, 32, 29 });
	flip.loop = false;
	flip.speed = 0.3f;

	
}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;
	stage = false;
	over = false;

	texture = App->textures->Load("Assets/Sprites/character.png");
	//win = App->textures->Load("Assets/Sprites/Stage_Clear.png");
	currentAnimation = &idleAnim;
	
	muerteFx = App->audio->LoadFx("Assets/Fx/muerte.wav");
	laserFx = App->audio->LoadFx("Assets/Fx/laser.wav");
	explosionFx = App->audio->LoadFx("Assets/Fx/explosion.wav");
	winFx = App->audio->LoadFx("Assets/Music/win.ogg");
	loseFx = App->audio->LoadFx("Assets/Music/gameover.ogg");
	coinFx = App->audio->LoadFx("Assets/Fx/coin.wav");
	damageFx = App->audio->LoadFx("Assets/Fx/lose.wav");
	bigexplioson = App->audio->LoadFx("Assets/Fx/BIG-EXPLOSION.wav");
	pkfire = App->audio->LoadFx("Assets/Fx/bossfire.wav");
	hit = App->audio->LoadFx("Assets/Fx/lasthit.wav");
	//lasthitFx = App->audio->LoadFx("Assets/Fx/lasthit.wav");

	position.x = 63 + 250;
	position.y = 600;
	OPTMIZENELJUEGUITO = 0;
	playershots = 2;
	laserspeed = -8;
	lives = 3;
	score = 0;
	god_mode = false;
	App->collisions->debug = false;

	destroyed = false;

	collider = App->collisions->AddCollider({ position.x, position.y, 32, 29 }, Collider::Type::PLAYER, this);


	char lookupTable[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };
	scoreFont = App->fonts->Load("Assets/Fonts/textocosa.png", lookupTable, 2);

	return ret;
}

Update_Status ModulePlayer::Update()
{
	//put this before use controller
	GamePad& pad = App->input->pads[0];

	laserspeed;
	playershots;

	//Debug key for gamepad rumble testing purposes
	if (App->input->keys[SDL_SCANCODE_F6] == Key_State::KEY_DOWN)
	{
		App->input->ShakeController(0, 60, 0.33f);
	}

	//Debug key for gamepad rumble testing purposes
	if (App->input->keys[SDL_SCANCODE_F7] == Key_State::KEY_DOWN)
	{
		App->input->ShakeController(0, 60, 0.66f);
	}

	//Debug key for gamepad rumble testing purposes
	if (App->input->keys[SDL_SCANCODE_F8] == Key_State::KEY_DOWN)
	{
		App->input->ShakeController(0, 60, 1.0f);
	}
	
	App->player->position.y -= speed;
	OPTMIZENELJUEGUITO -= speed;
	

	if (position.y <= App->render->camera.y)
	{
		position.y = App->render->camera.y;
	}

	if (position.y >= App->render->camera.y + 289 && App->sceneLevel_1->eldenboy)
	{
		position.y = App->render->camera.y + 289;
	}

	
	
	////if camera position is 1000, do the flip animation once and then go back to idle
	//if (App->player->position.y <= -700 && App->sceneLevel_1->eldenboy)
	//{

	//	currentAnimation = &flip;
	//	if (flip.Finished())
	//	{
	//		currentAnimation = &idleAnim;
	//	}
	//	

	//}
	// this one doesn't work

	/*I created a class called Finished() in line 22, which seems to be working, but this is somehow connected to the control,
	which we don't want, please help it doesn't fucking make sense*/



	bool isFlipAnimationTriggered = false;

	if (App->player->position.y == -630 && App->sceneLevel_1->eldenboy && !isFlipAnimationTriggered)
	{
		if (currentAnimation != &flip)
		{
			flip.Reset();
			isFlipAnimationTriggered = true;
			currentAnimation = &flip;

		}
		else if (isFlipAnimationTriggered = true)
		{
			currentAnimation = &idleAnim;
		}
		
	}


	if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT && App->sceneLevel_1->eldenboy || pad.l_x < 0.0f && App->sceneLevel_1->eldenboy)
	{
		position.x -= speed + 4;
		if (currentAnimation != &leftAnim && flip.HasFinished())
		{
			leftAnim.Reset();
			currentAnimation = &leftAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT && App->sceneLevel_1->eldenboy || pad.l_x > 0.0f && App->sceneLevel_1->eldenboy)
	{
	    position.x += speed + 4;
		if (currentAnimation != &rightAnim && flip.HasFinished())
		{
			rightAnim.Reset();
			currentAnimation = &rightAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT && App->sceneLevel_1->eldenboy || pad.l_y > 0.0f && App->sceneLevel_1->eldenboy)
	{
		position.y += speed +2;
	}

	if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT && App->sceneLevel_1->eldenboy || pad.l_y < 0.0f && App->sceneLevel_1->eldenboy)
	{
		position.y -= speed + 2;
	}

	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_REPEAT && destroyed == false && App->sceneLevel_1->eldenboy == true || pad.a == true && destroyed == false && App->sceneLevel_1->eldenboy == true)
	{
		if (playershots <= 2)
		{
			if (shotCountdown == 0)
			{
				/*Particle* newParticle = */App->particles->AddParticle(App->particles->laser2, position.x + 12, position.y - 10, Collider::Type::PLAYER_SHOT);
				/*newParticle->collider->AddListener(this);*/
				App->audio->PlayFx(laserFx);
				shotCountdown = shotMaxCountdown;
			}
		}
		else if (playershots == 3)
		{
			if (shotCountdown == 0)
			{
				/*Particle* newParticle = */App->particles->AddParticle(App->particles->laser3, position.x + 10, position.y - 10, Collider::Type::PLAYER_SHOT);
				/*newParticle->collider->AddListener(this);*/
				App->audio->PlayFx(laserFx);
				shotCountdown = shotMaxCountdown;
			}
		}
		else if (playershots == 4)
		{
			if (shotCountdown == 0)
			{
				/*Particle* newParticle = */App->particles->AddParticle(App->particles->laser4, position.x + 5, position.y - 10, Collider::Type::PLAYER_SHOT);
				/*newParticle->collider->AddListener(this);*/
				App->audio->PlayFx(laserFx);
				shotCountdown = shotMaxCountdown;
			}
		}
		else
		{
			if (shotCountdown == 0)
			{
				/*Particle* newParticle = */App->particles->AddParticle(App->particles->laser5, position.x + 5, position.y - 10, Collider::Type::PLAYER_SHOT);
				/*newParticle->collider->AddListener(this);*/
				App->audio->PlayFx(laserFx);
				shotCountdown = shotMaxCountdown;
			}
		}
	}

	if (App->input->keys[SDL_SCANCODE_F2] == Key_State::KEY_DOWN || pad.back == true)
	{
		god_mode = !god_mode;
	}
	current = SDL_GetTicks();
	
	if (App->input->keys[SDL_SCANCODE_F3] == Key_State::KEY_DOWN && App->sceneLevel_1->eldenboy && !stage)
	{
		Mix_PauseMusic();
		App->audio->PlayFx(App->player->winFx);
		if (score > highscore) {
			highscore = score;
		}
		score = 0;
		lives = 3;

		App->enemies->AddEnemy(Enemy_Type::STAGE, -20 + 250, App->render->camera.y + 50);
		App->enemies->AddEnemy(Enemy_Type::CLEAR, SCREEN_WIDTH / 2 - 30 + 250, App->render->camera.y + 50);
		//App->enemies->AddEnemy(Enemy_Type::MIYAMOTO, 90 + 250, App->render->camera.y - 80);
		
		god_mode = true;
		App->player->collider->type = Collider::Type::NONE;

		start = SDL_GetTicks();
		next = start + interval;
		crack = !crack;
		stage = true;
	}

	if (crack) {
		if (current > next) {
			crack = !crack;
			App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneIntro3, 70);
		}
	}

	if (App->input->keys[SDL_SCANCODE_F4] == Key_State::KEY_DOWN && App->sceneLevel_1->eldenboy && !over)
	{
		App->audio->PlayFx(loseFx);
		App->collisions->debug = false;
		
		if (score > highscore) {
			highscore = score;
		}
		if (lives <= 0) {
			lives = 4;
			score = 0;
			App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneIntro3, 70);
		}
		if (lives > 0)
		{
			lives -= 1;
			App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneGameOver, 70);
		}		
		over = true;
	}

	if (App->input->keys[SDL_SCANCODE_1] == Key_State::KEY_DOWN && App->sceneLevel_1->eldenboy)
	{
		App->enemies->AddEnemy(Enemy_Type::REDBIRD, (rand() % 211) + 10 + 250, App->player->position.y - 260);
	}

	if (App->input->keys[SDL_SCANCODE_2] == Key_State::KEY_DOWN && App->sceneLevel_1->eldenboy)
	{
		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, (rand() % 211) + 10 + 250, App->player->position.y - 260);
	}
	if (App->input->keys[SDL_SCANCODE_3] == Key_State::KEY_DOWN && App->sceneLevel_1->eldenboy)
	{
		App->enemies->AddEnemy(Enemy_Type::DOUBLETANK, (rand() % 211) + 10 + 250, App->player->position.y - 260);
	}
	if (App->input->keys[SDL_SCANCODE_4] == Key_State::KEY_DOWN && App->sceneLevel_1->eldenboy)
	{
		App->enemies->AddEnemy(Enemy_Type::BAG, (rand() % 211) + 10 + 250, App->player->position.y - 260);
	}
	if (App->input->keys[SDL_SCANCODE_5] == Key_State::KEY_DOWN && App->sceneLevel_1->eldenboy)
	{
		App->enemies->AddEnemy(Enemy_Type::CHEST, (rand() % 210) + 10 + 250, App->player->position.y - 260);
	}
	if (App->input->keys[SDL_SCANCODE_6] == Key_State::KEY_DOWN && App->sceneLevel_1->eldenboy)
	{
		App->enemies->AddEnemy(Enemy_Type::BlUEDRAGON, (rand() % 210) + 10 + 250, App->player->position.y - 260);
	}
	if (App->input->keys[SDL_SCANCODE_7] == Key_State::KEY_DOWN && App->sceneLevel_1->eldenboy)
	{
		App->enemies->AddEnemy(Enemy_Type::FLYINGLIZARD, (rand() % 210) + 10 + 250, App->player->position.y - 260);
	}
	if (App->input->keys[SDL_SCANCODE_8] == Key_State::KEY_DOWN && App->sceneLevel_1->eldenboy)
	{
		App->enemies->AddEnemy(Enemy_Type::SINGLETANK, (rand() % 210) + 10 + 250, App->player->position.y - 260);
	}
	if (App->input->keys[SDL_SCANCODE_9] == Key_State::KEY_DOWN && App->sceneLevel_1->eldenboy)
	{
		App->enemies->AddEnemy(Enemy_Type::REVERSEDT, (rand() % 210) + 10 + 250, App->player->position.y - 260);
	}
	if (App->input->keys[SDL_SCANCODE_0] == Key_State::KEY_DOWN && App->sceneLevel_1->eldenboy)
	{
		App->enemies->AddEnemy(Enemy_Type::REVERSEST, (rand() % 210) + 10 + 250, App->player->position.y - 260);
	}
	if (App->input->keys[SDL_SCANCODE_Y] == Key_State::KEY_DOWN && App->sceneLevel_1->eldenboy)
	{
		App->enemies->AddEnemy(Enemy_Type::BlUEDRAGON2, (rand() % 210) + 10 + 250, App->player->position.y - 260);
	}
	if (App->input->keys[SDL_SCANCODE_H] == Key_State::KEY_DOWN && App->sceneLevel_1->eldenboy)
	{
		App->enemies->AddEnemy(Enemy_Type::REDBIRD2, (rand() % 210) + 10 + 250, App->player->position.y - 260);
	}
	if (App->input->keys[SDL_SCANCODE_G] == Key_State::KEY_DOWN && App->sceneLevel_1->eldenboy)
	{
		App->enemies->AddEnemy(Enemy_Type::REDBIRD3, (rand() % 210) + 10 + 250, App->player->position.y - 260);
	}

	if (App->input->keys[SDL_SCANCODE_M] == Key_State::KEY_DOWN && App->sceneLevel_1->eldenboy)
	{
		App->player->position.y = -5590;
		App->render->camera.y = -5525 - SCREEN_HEIGHT / 2;
		App->player->OPTMIZENELJUEGUITO = -5525 - SCREEN_HEIGHT / 2;
	}

	if (App->input->keys[SDL_SCANCODE_N] == Key_State::KEY_DOWN && App->sceneLevel_1->eldenboy)
	{
		App->player->position.y = -8640;
		App->render->camera.y = -8575 - SCREEN_HEIGHT / 2;
		App->player->OPTMIZENELJUEGUITO = -8575 - SCREEN_HEIGHT / 2;
	}

    // If no up/down movement detected, set the current animation back to idle
	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_IDLE
		&& App->sceneLevel_1->eldenboy
		&&(pad.up == false && pad.down == false)&&(pad.l_y == 0 && pad.l_x == 0)
		&& App->player->position.y <= -800)
		currentAnimation = &idleAnim;

	if (ahora)
	{
		currentTime = SDL_GetTicks();

		if (currentTime > nextNotificationTime) {
			App->player->position.x = 111 + 250;
			App->player->position.y = App->render->camera.y + 600;
			destroyed = false;
			ahora = false;
			currentTime = SDL_GetTicks();
			nextNotificationTime = currentTime + intervalo;
			anfetaminas = true;
			currentAnimation = &bright1;
		}
	}

	if (anfetaminas)
	{
		currentTime = SDL_GetTicks();
		
		if (currentTime > (nextNotificationTime))
		{
			App->player->collider->type = Collider::Type::PLAYER;
			anfetaminas = false;
		}
	}
	
	

	if (App->input->keys[SDL_SCANCODE_P] == Key_State::KEY_DOWN && App->sceneLevel_1->eldenboy)
	{
		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP2, 20 + 250, App->render->camera.y - 40);
	}
	

	
	//// Switch gamepad debug info
	//if (App->input->keys[SDL_SCANCODE_F6] == KEY_DOWN)
	//	debugGamepadInfo = !debugGamepadInfo;

	// Update animation and collider position
	collider->SetPos(position.x, position.y);

	currentAnimation->Update();

	// Update shot countdown
	if (shotCountdown > 0)
		--shotCountdown;

	

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModulePlayer::PostUpdate()
{
	if (!destroyed)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y, &rect);
	}
	//App->render->Blit(win, 0, 0, NULL);

	sprintf_s(scoreText, 10, "%7d", score);
	sprintf_s(highscoreText, 10, "%7d", highscore);
	sprintf_s(livesText, 10, "%7d", lives);

	App->fonts->BlitText(1, 15, scoreFont, scoreText);

	App->fonts->BlitText(2, 2, scoreFont, "player1");
	App->fonts->BlitText(88, 2, scoreFont, "highscore");
	App->fonts->BlitText(96, 15, scoreFont, highscoreText);
	App->fonts->BlitText(180, 2, scoreFont, "lives x ");
	App->fonts->BlitText(192, 2, scoreFont, livesText);

	if (god_mode)
	{
		App->fonts->BlitText(180, 15, scoreFont, "god mode");
	}

	/*if (debugGamepadInfo == true)
		DebugDrawGamepadInfo();
	else
		App->fonts->BlitText(5, 80, scoreFont, "f5 to display gamepad debug info");*/

	

	return Update_Status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == collider && destroyed == false)
	{
		//Rumble the Gamepad when colliding even in god mode
		App->input->ShakeController(0, 60, 0.9f);

		if (god_mode) { destroyed = false; }
		else {
			App->particles->AddParticle(App->particles->explosion, position.x, position.y, Collider::Type::NONE, 9);
			App->particles->AddParticle(App->particles->explosion, position.x + 8, position.y + 11, Collider::Type::NONE, 14);
			App->particles->AddParticle(App->particles->explosion, position.x - 7, position.y + 12, Collider::Type::NONE, 40);
			App->particles->AddParticle(App->particles->explosion, position.x + 5, position.y - 5, Collider::Type::NONE, 28);
			App->particles->AddParticle(App->particles->explosion, position.x - 4, position.y - 4, Collider::Type::NONE, 21);

			//Rumble the Gamepad when colliding
			App->input->ShakeController(0, 110, 0.9f);
			
			App->audio->PlayFx(muerteFx);

			destroyed = true;
			/*App->collisions->debug = false;*/
			
			if (score > highscore) {
				highscore = score;
			}

			if (lives <= 0) {
				Mix_PauseMusic();
				App->audio->PlayFx(loseFx);
				App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneGameOver, 70);
			}

			else if (lives > 0)
			{
				
				lives -= 1;
				currentTime = SDL_GetTicks();
				nextNotificationTime = currentTime + intervalo;
				ahora = true;
				App->player->collider->type = Collider::Type::NONE;
			}
		}
	}	
}

//void ModulePlayer::DebugDrawGamepadInfo()
//{
//	GamePad& pad = App->input->pads[0];
//
//	sprintf_s(scoreText, 150, "pad 0 %s, press 1/2/3 for rumble", (pad.enabled) ? "plugged" : "not detected");
//	App->fonts->BlitText(5, 10, scoreFont, scoreText);
//
//	sprintf_s(scoreText, 150, "buttons %s %s %s %s %s %s %s %s %s %s %s",
//		(pad.a) ? "a" : "",
//		(pad.b) ? "b" : "",
//		(pad.x) ? "x" : "",
//		(pad.y) ? "y" : "",
//		(pad.start) ? "start" : "",
//		(pad.back) ? "back" : "",
//		(pad.guide) ? "guide" : "",
//		(pad.l1) ? "lb" : "",
//		(pad.r1) ? "rb" : "",
//		(pad.l3) ? "l3" : "",
//		(pad.r3) ? "r3" : ""
//	);
//	App->fonts->BlitText(5, 20, scoreFont, scoreText);
//
//	sprintf_s(scoreText, 150, "dpad %s %s %s %s",
//		(pad.up) ? "up" : "",
//		(pad.down) ? "down" : "",
//		(pad.left) ? "left" : "",
//		(pad.right) ? "right" : ""
//	);
//	App->fonts->BlitText(5, 30, scoreFont, scoreText);
//
//	sprintf_s(scoreText, 150, "left trigger  %0.2f", pad.l2);
//	App->fonts->BlitText(5, 40, scoreFont, scoreText);
//	sprintf_s(scoreText, 150, "right trigger %0.2f", pad.r2);
//	App->fonts->BlitText(5, 50, scoreFont, scoreText);
//
//	sprintf_s(scoreText, 150, "left thumb    %.2fx, %0.2fy", pad.l_x, pad.l_y);
//	App->fonts->BlitText(5, 60, scoreFont, scoreText);
//
//	sprintf_s(scoreText, 150, "   deadzone   %0.2f", pad.l_dz);
//	App->fonts->BlitText(5, 70, scoreFont, scoreText);
//
//	sprintf_s(scoreText, 150, "right thumb   %.2fx, %0.2fy", pad.r_x, pad.r_y);
//	App->fonts->BlitText(5, 80, scoreFont, scoreText);
//
//	sprintf_s(scoreText, 150, "   deadzone   %0.2f", pad.r_dz);
//	App->fonts->BlitText(5, 90, scoreFont, scoreText);
//}