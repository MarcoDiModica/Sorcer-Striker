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

	EnemyL.speed.y = 2;
	EnemyL.lifetime = 120;
	EnemyL.anim.speed = 0.2f;
	EnemyL.anim.loop = true;

	tubo.anim.PushBack({ 0,233,254,35 });

	tubo.speed.y = 0;
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

	SingleTankMark.anim.PushBack({ 16,103,33,33 });
	
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
	enemieShot.direction = -1;

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
	Stage.speed.x = LSD;

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