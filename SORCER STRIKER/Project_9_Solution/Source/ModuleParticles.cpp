#include "ModuleParticles.h"

#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"
#include "coin.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		particles[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{

}

bool ModuleParticles::Start()
{
	LOG("Loading particles");
	texture = App->textures->Load("Assets/Sprites/particles2.png");

	// Explosion particle
	explosion.anim.PushBack({ 116, 10, 34, 35 });
	explosion.anim.PushBack({ 158, 10, 34, 35 });
	explosion.anim.PushBack({ 206, 10, 34, 35 });
	explosion.anim.PushBack({ 246, 10, 34, 35 });
	explosion.anim.PushBack({ 288, 10, 34, 35 });
	explosion.anim.PushBack({ 330, 10, 34, 35 });
	explosion.anim.loop = false;
	explosion.anim.speed = 0.3f;
	

	laser2.anim.PushBack({ 24, 26, 8, 21 });
	
	laser2.speed.y = App->player->laserspeed;
	laser2.lifetime = 50;
	laser2.anim.speed = 0.2f;

	laser3.anim.PushBack({ 6, 23, 12, 24 });

	laser3.speed.y = App->player->laserspeed;
	laser3.lifetime = 50;
	laser3.anim.speed = 0.2f;

	laser4.anim.PushBack({ 24, 26, 22, 21 });

	laser4.speed.y = App->player->laserspeed;
	laser4.lifetime = 50;
	laser4.anim.speed = 0.2f;

	laser5.anim.PushBack({ 50, 23, 22, 24 });

	laser5.speed.y = App->player->laserspeed;
	laser5.lifetime = 50;
	laser5.anim.speed = 0.2f;

	EnemyL.anim.PushBack({ 265,82,17,15 });
	EnemyL.anim.PushBack({ 264,106,16,15 });
	EnemyL.anim.PushBack({ 297,108,18,17 });
	EnemyL.anim.PushBack({ 327,97,19,17 });

	EnemyL.lifetime = 120;
	EnemyL.anim.speed = 0.2f;
	EnemyL.anim.loop = true;

	tubo.anim.PushBack({ 0,233,254,35 });

	tubo.speed.y = 4.0f;
	tubo.lifetime = 600;
	tubo.anim.speed = 0.2f;

	coin.anim.PushBack({ 90,93,11,11 }); 
	coin.anim.PushBack({ 112,95,11,11 });
	coin.anim.PushBack({ 134,95,11,11 });
	coin.anim.PushBack({ 150,95,11,11 });
	coin.anim.PushBack({ 167,96,11,11 });
	coin.anim.PushBack({ 183,96,11,11 });
	coin.anim.loop = true;
	
	coin.speed.y = 1;
	coin.lifetime = 120;
	coin.anim.speed = 0.2f;

	Stage.anim.PushBack({ 122,150,95,46 });

	Stage.speed.y = -2;
	Stage.speed.x = LSD;
	Stage.lifetime = 500;
	
	Clear.anim.PushBack({ 223,150,180,46 });

	Clear.speed.y = -2;
	Clear.lifetime = 500;

	DoubleTankMark.anim.PushBack({ 16,103,63,33 });
	
	DoubleTankMark.speed.y = 0;
	DoubleTankMark.lifetime = 120;

	SingleTankMark.anim.PushBack({ 17,146,36,35 });
	
	SingleTankMark.speed.y = 0;
	SingleTankMark.lifetime = 120;

	enemieShot.anim.PushBack({ 20,201,13,13 });
	enemieShot.anim.PushBack({ 73,201,13,13 });
	enemieShot.anim.PushBack({ 56,201,13,13 });
	enemieShot.anim.PushBack({ 38,201,13,13 });

	enemieShot.speed.y = 1;
	enemieShot.speed.x = cocaina;
	enemieShot.lifetime = 120;
	enemieShot.anim.loop = true;
	enemieShot.anim.speed = 0.2f;
	enemieShot.direction = man;

	enemieShot2.anim.PushBack({ 20,201,13,13 });
	enemieShot2.anim.PushBack({ 73,201,13,13 });
	enemieShot2.anim.PushBack({ 56,201,13,13 });
	enemieShot2.anim.PushBack({ 38,201,13,13 });
		
	enemieShot2.speed.y = 1;
	enemieShot2.speed.x = cocaina2;
	enemieShot2.lifetime = 120;
	enemieShot2.anim.loop = true;
	enemieShot2.anim.speed = 0.2f;
	enemieShot2.direction = man;

	enemieShot3.anim.PushBack({ 20,201,13,13 });
	enemieShot3.anim.PushBack({ 73,201,13,13 });
	enemieShot3.anim.PushBack({ 56,201,13,13 });
	enemieShot3.anim.PushBack({ 38,201,13,13 });
			  
	enemieShot3.speed.y = 1;
	enemieShot3.speed.x = cocaina3;
	enemieShot3.lifetime = 120;
	enemieShot3.anim.loop = true;
	enemieShot3.anim.speed = 0.2f;
	enemieShot3.direction = man;

	enemieShot4.anim.PushBack({ 20,201,13,13 });
	enemieShot4.anim.PushBack({ 73,201,13,13 });
	enemieShot4.anim.PushBack({ 56,201,13,13 });
	enemieShot4.anim.PushBack({ 38,201,13,13 });
			  
	enemieShot4.speed.y = 1;
	enemieShot4.speed.x = cocaina4;
	enemieShot4.lifetime = 120;
	enemieShot4.anim.loop = true;
	enemieShot4.anim.speed = 0.2f;
	enemieShot4.direction = man;

	enemieShot5.anim.PushBack({ 20,201,13,13 });
	enemieShot5.anim.PushBack({ 73,201,13,13 });
	enemieShot5.anim.PushBack({ 56,201,13,13 });
	enemieShot5.anim.PushBack({ 38,201,13,13 });
		  
	enemieShot5.speed.y = 1;
	enemieShot5.speed.x = cocaina5;
	enemieShot5.lifetime = 120;
	enemieShot5.anim.loop = true;
	enemieShot5.anim.speed = 0.2f;
	enemieShot5.direction = man;

	enemieShot6.anim.PushBack({ 20,201,13,13 });
	enemieShot6.anim.PushBack({ 73,201,13,13 });
	enemieShot6.anim.PushBack({ 56,201,13,13 });
	enemieShot6.anim.PushBack({ 38,201,13,13 });
			  
	enemieShot6.speed.y = 1;
	enemieShot6.speed.x = cocaina6;
	enemieShot6.lifetime = 120;
	enemieShot6.anim.loop = true;
	enemieShot6.anim.speed = 0.2f;
	enemieShot6.direction = man;

	enemieShot8.anim.PushBack({ 20,201,13,13 });
	enemieShot8.anim.PushBack({ 73,201,13,13 });
	enemieShot8.anim.PushBack({ 56,201,13,13 });
	enemieShot8.anim.PushBack({ 38,201,13,13 });
			  
	enemieShot8.speed.y = 1;
	enemieShot8.speed.x = cocaina8;
	enemieShot8.lifetime = 120;
	enemieShot8.anim.loop = true;
	enemieShot8.anim.speed = 0.2f;
	enemieShot8.direction = man;

	enemieShot7.anim.PushBack({ 20,201,13,13 });
	enemieShot7.anim.PushBack({ 73,201,13,13 });
	enemieShot7.anim.PushBack({ 56,201,13,13 });
	enemieShot7.anim.PushBack({ 38,201,13,13 });
			  
	enemieShot7.speed.y = 1;
	enemieShot7.speed.x = cocaina7;
	enemieShot7.lifetime = 120;
	enemieShot7.anim.loop = true;
	enemieShot7.anim.speed = 0.2f;
	enemieShot7.direction = man;

	enemieShotTANK.anim.PushBack({ 20,201,13,13 });
	enemieShotTANK.anim.PushBack({ 73,201,13,13 });
	enemieShotTANK.anim.PushBack({ 56,201,13,13 });
	enemieShotTANK.anim.PushBack({ 38,201,13,13 });

	enemieShotTANK.speed.y = 2;
	enemieShotTANK.speed.x = -1;
	enemieShotTANK.lifetime = 120;
	enemieShotTANK.anim.loop = true;
	enemieShotTANK.anim.speed = 0.3f;
	enemieShotTANK.direction = man;

	enemieShotTANK2.anim.PushBack({ 20,201,13,13 });
	enemieShotTANK2.anim.PushBack({ 73,201,13,13 });
	enemieShotTANK2.anim.PushBack({ 56,201,13,13 });
	enemieShotTANK2.anim.PushBack({ 38,201,13,13 });
				  
	enemieShotTANK2.speed.y = 2;
	enemieShotTANK2.speed.x = 1;
	enemieShotTANK2.lifetime = 120;
	enemieShotTANK2.anim.loop = true;
	enemieShotTANK2.anim.speed = 0.3f;
	enemieShotTANK2.direction = man;

	directionshot.anim.PushBack({ 20,201,13,13 });
	directionshot.anim.PushBack({ 73,201,13,13 });
	directionshot.anim.PushBack({ 56,201,13,13 });
	directionshot.anim.PushBack({ 38,201,13,13 });

	directionshot.lifetime = 120;
	directionshot.anim.loop = true;
	directionshot.anim.speed = 0.3f;
	directionshot.direction = man;

	BigExplosion.anim.PushBack({ 330,148,55,55 });
	BigExplosion.anim.PushBack({ 400,148,55,55 });
	BigExplosion.anim.PushBack({ 462,148,55,55 });
	
	BigExplosion.anim.loop = false;
	BigExplosion.anim.speed = 0.2f;
	BigExplosion.speed.y = -2;
	

	InsaneEXplosion.anim.PushBack({ 4,283,98,90 });
	InsaneEXplosion.anim.PushBack({ 128,294,76,76 });
	InsaneEXplosion.anim.PushBack({ 234,298,70,70 });

	InsaneEXplosion.anim.loop = false;
	InsaneEXplosion.anim.speed = 0.2f;

	flamethrower.anim.PushBack({ 323,329,20,18 });
	flamethrower.anim.PushBack({ 349,327,22,21 });
	flamethrower.anim.PushBack({376,320,27,32});
	flamethrower.anim.PushBack({ 410,318,33,38 });
	flamethrower.anim.PushBack({ 410,318,33,38 });
	flamethrower.anim.PushBack({ 448,322,34,33 });
	flamethrower.anim.PushBack({ 448,322,34,33 });

	flamethrower.speed.y = 2;
	flamethrower.lifetime = 120;
	flamethrower.anim.loop = false;
	flamethrower.anim.speed = 0.1f;

	
	return true;
}

Update_Status ModuleParticles::PreUpdate()
{
	// Remove all particles scheduled for deletion
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (particles[i] != nullptr && particles[i]->pendingToDelete)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}
	
	return Update_Status::UPDATE_CONTINUE;
}

bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");

	// Delete all remaining active particles on application exit 
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(particles[i] != nullptr)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}

	return true;
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (particles[i] != nullptr && particles[i]->collider == c1)
		{
			particles[i]->pendingToDelete = true;
			particles[i]->collider->pendingToDelete = true;
			break;
		}
	}
}

Update_Status ModuleParticles::Update()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if(particle == nullptr)	continue;

		// Call particle Update. If it has reached its lifetime, destroy it
		if(particle->Update() == false)
		{
			particles[i]->SetToDelete();
		}
	}

	enemieShot.speed.x = cocaina;
	enemieShot2.speed.x = cocaina2;
	enemieShot3.speed.x = cocaina3;
	enemieShot4.speed.x = cocaina4;
	enemieShot5.speed.x = cocaina5;
	enemieShot6.speed.x = cocaina6;
	enemieShot7.speed.x = cocaina7;
	enemieShot8.speed.x = cocaina8;
	Stage.speed.x = LSD;
	enemieShot.direction = man;
	enemieShot2.direction = man;
	enemieShot3.direction = man;
	enemieShot4.direction = man;
	enemieShot5.direction = man;
	enemieShot6.direction = man;
	/*if (App->particles->Stage.position.x >= 35) {
		App->particles->Stage.position.x -= 2;
	}*/
	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleParticles::PostUpdate()
{
	//Iterating all particle array and drawing any active particles
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if (particle != nullptr && particle->isAlive)
		{
			App->render->Blit(texture, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Particle* ModuleParticles::AddParticle(const Particle& particle, int x, int y, Collider::Type colliderType, uint delay)
{
	Particle* newParticle = nullptr;

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		//Finding an empty slot for a new particle
		if (particles[i] == nullptr)
		{
			newParticle = new Particle(particle);
			newParticle->frameCount = -(int)delay;			// We start the frameCount as the negative delay
			newParticle->position.x = x;						// so when frameCount reaches 0 the particle will be activated
			newParticle->position.y = y;

			//Adding the particle's collider
			if (colliderType != Collider::Type::NONE )
				newParticle->collider = App->collisions->AddCollider(newParticle->anim.GetCurrentFrame(), colliderType, this);

			particles[i] = newParticle;
			break;
		}
	}

	return newParticle;
}