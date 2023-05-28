#ifndef __ENEMY_FLYINGLIZARD_H__
#define __ENEMY_FLYINGLIZARD_H__

#include "Enemy.h"
#include "Path.h"
#include "ModuleParticles.h"

class Enemy_FlyingLizard : public Enemy {
public:

	Enemy_FlyingLizard(int x, int y);

	void Update();

private:

	Path path;

	float waveRatio = 0.0f;

	float waveRatioSpeed = 0.2f;

	int spawn_y = 0;

	int waveHeight = 15;

	Animation FlyAnim1;
	
	//mabybe add some more
};
#endif // __ENEMY_SINGLETANK_H__

