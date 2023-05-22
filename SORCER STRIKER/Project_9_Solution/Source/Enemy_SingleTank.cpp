#include "Enemy_SingleTank.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"

Enemy_SingleTank::Enemy_SingleTank(int x, int y) : Enemy(x, y) 
{

	//rollingAnim.PushBack()

}

void Enemy_SingleTank::Update()
{

	Enemy:: Update();
}
