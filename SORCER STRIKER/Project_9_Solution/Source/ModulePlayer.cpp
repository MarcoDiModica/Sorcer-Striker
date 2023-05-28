#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "ModuleCollisions.h"
#include "ModuleWindow.h"
#include <random>

#include <stdio.h>

ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled)
{
	// idle animation - just one sprite
	idleAnim.PushBack({ 138, 154, 32, 29 });
	idleAnim.PushBack({ 172, 154, 32, 29 });
	idleAnim.PushBack({ 204, 154, 32, 29 });
	idleAnim.loop = true;
	idleAnim.speed = 0.07f;

	// move leftwards
	idleAnim.PushBack({ 138, 154, 32, 29 });
	leftAnim.PushBack({ 85, 153, 28, 29 });
	leftAnim.PushBack({ 113, 153, 24, 29 });
	leftAnim.loop = false;
	leftAnim.speed = 0.1f;

	// Move rightwards
	idleAnim.PushBack({ 138, 154, 32, 29 });
	rightAnim.PushBack({ 126, 65, 28, 29 });
	rightAnim.PushBack({ 101, 66, 24, 29 });
	rightAnim.loop = false;
	rightAnim.speed = 0.1f;
}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("Assets/Sprites/character.png");
	win = App->textures->Load("Assets/Sprites/victoryroyale.png");
	currentAnimation = &idleAnim;
	
	laserFx = App->audio->LoadFx("Assets/Fx/laser.wav");
	explosionFx = App->audio->LoadFx("Assets/Fx/explosion.wav");
	winFx = App->audio->LoadFx("Assets/Fx/win.wav");
	loseFx = App->audio->LoadFx("Assets/Fx/lose.wav");
	coinFx = App->audio->LoadFx("Assets/Fx/coin.wav");
	//damageFx = App->audio->LoadFx("Assets/Fx/damage.wav");
	//lasthitFx = App->audio->LoadFx("Assets/Fx/lasthit.wav");

	position.x = 111;
	position.y = 250;
	OPTMIZENELJUEGUITO = 0;

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

	//Debug key for gamepad rumble testing purposes
	if (App->input->keys[SDL_SCANCODE_1] == Key_State::KEY_DOWN)
	{
		App->input->ShakeController(0, 60, 0.33f);
	}

	//Debug key for gamepad rumble testing purposes
	if (App->input->keys[SDL_SCANCODE_2] == Key_State::KEY_DOWN)
	{
		App->input->ShakeController(0, 60, 0.66f);
	}

	//Debug key for gamepad rumble testing purposes
	if (App->input->keys[SDL_SCANCODE_3] == Key_State::KEY_DOWN)
	{
		App->input->ShakeController(0, 60, 1.0f);
	}
	
	App->player->position.y -= speed;
	OPTMIZENELJUEGUITO -= speed;


	if (position.y <= OPTMIZENELJUEGUITO)
	{
		position.y = OPTMIZENELJUEGUITO;
	}

	if (position.y >= OPTMIZENELJUEGUITO + 289)
	{
		position.y = OPTMIZENELJUEGUITO + 289;
	}

	if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT || pad.l_x < 0.0f ||pad.left == true)
	{
		position.x -= speed + 2;
		if (currentAnimation != &leftAnim)
		{
			leftAnim.Reset();
			currentAnimation = &leftAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT || pad.l_x > 0.0f || pad.right == true)
	{
	    position.x += speed + 2;
		if (currentAnimation != &rightAnim)
		{
			rightAnim.Reset();
			currentAnimation = &rightAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT || pad.l_y > 0.0f || pad.down == true)
	{
		position.y += speed +2;
	}

	if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT || pad.l_y < 0.0f || pad.up == true)
	{
		position.y -= speed + 2;
	}

	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN || pad.a == true )
	{
		if (shotCountdown == 0)
		{

			Particle* newParticle = App->particles->AddParticle(App->particles->laser, position.x + 12, position.y - 10, Collider::Type::PLAYER_SHOT);
			newParticle->collider->AddListener(this);
			App->audio->PlayFx(laserFx);
			shotCountdown = shotMaxCountdown;
		}

		//rumble the Gamepad when firing
		/*App->input->ShakeController(0, 60, 0.02f);*/
	}

	if (App->input->keys[SDL_SCANCODE_F2] == Key_State::KEY_DOWN || pad.back == true)
	{
		god_mode = !god_mode;
	}

	if (App->input->keys[SDL_SCANCODE_F3] == Key_State::KEY_DOWN)
	{
		/*App->audio->PlayFx(winFx);*/
		App->collisions->debug = false;
		if (score > highscore) {
			highscore = score;
		}
		score = 0;
		lives = 3;
		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneStageclear, 70);
	}

	if (App->input->keys[SDL_SCANCODE_F4] == Key_State::KEY_DOWN)
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
	}

	if (App->input->keys[SDL_SCANCODE_1] == Key_State::KEY_DOWN)
	{
		App->enemies->AddEnemy(Enemy_Type::REDBIRD, (rand() % 211) + 10, App->player->position.y - 260);
	}

	if (App->input->keys[SDL_SCANCODE_2] == Key_State::KEY_DOWN)
	{
		App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, (rand() % 211) + 10, App->player->position.y - 260);
	}
	if (App->input->keys[SDL_SCANCODE_3] == Key_State::KEY_DOWN)
	{
		App->enemies->AddEnemy(Enemy_Type::DOUBLETANK, (rand() % 211) + 10, App->player->position.y - 260);
	}
	if (App->input->keys[SDL_SCANCODE_4] == Key_State::KEY_DOWN)
	{
		App->enemies->AddEnemy(Enemy_Type::BAG, (rand() % 211) + 10, App->player->position.y - 260);
	}
	if (App->input->keys[SDL_SCANCODE_5] == Key_State::KEY_DOWN)
	{
		App->enemies->AddEnemy(Enemy_Type::CHEST, (rand() % 210) + 10, App->player->position.y - 260);
	}
	if (App->input->keys[SDL_SCANCODE_6] == Key_State::KEY_DOWN)
	{
		App->enemies->AddEnemy(Enemy_Type::BlUEDRAGON, (rand() % 210) + 10, App->player->position.y - 260);
	}
	if (App->input->keys[SDL_SCANCODE_7] == Key_State::KEY_DOWN)
	{
		App->enemies->AddEnemy(Enemy_Type::FLYINGLIZARD, (rand() % 210) + 10, App->player->position.y - 260);
	}
	if (App->input->keys[SDL_SCANCODE_8] == Key_State::KEY_DOWN)
	{
		App->enemies->AddEnemy(Enemy_Type::SINGLETANK, (rand() % 210) + 10, App->player->position.y - 260);
	}

    // If no up/down movement detected, set the current animation back to idle
	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_IDLE
		&&(pad.up == false && pad.down == false)&&(pad.l_y == 0 && pad.l_x == 0))
		currentAnimation = &idleAnim;

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
		App->input->ShakeController(0, 140, 0.9f);

		if (god_mode) { destroyed = false; }
		else {
			App->particles->AddParticle(App->particles->explosion, position.x, position.y, Collider::Type::NONE, 9);
			App->particles->AddParticle(App->particles->explosion, position.x + 8, position.y + 11, Collider::Type::NONE, 14);
			App->particles->AddParticle(App->particles->explosion, position.x - 7, position.y + 12, Collider::Type::NONE, 40);
			App->particles->AddParticle(App->particles->explosion, position.x + 5, position.y - 5, Collider::Type::NONE, 28);
			App->particles->AddParticle(App->particles->explosion, position.x - 4, position.y - 4, Collider::Type::NONE, 21);

			App->audio->PlayFx(explosionFx);

			App->audio->PlayFx(loseFx);

			//Rumble the Gamepad when colliding
			App->input->ShakeController(0, 140, 0.9f);
			
			destroyed = true;
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
		}
	}

	if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::COIN)
	{
		score += 200;
		App->audio->PlayFx(coinFx);
		App->particles->coin.pendingToDelete = true;
	}

	if (c1->type == Collider::Type::PLAYER_SHOT && c2->type == Collider::Type::ENEMY)
	{
		//rumble the gamepad when colliding
		App->input->ShakeController(0, 60, 0.1f);
		score += 50;
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