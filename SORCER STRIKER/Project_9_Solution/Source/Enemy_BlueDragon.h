#ifndef __ENEMY_BLUEDRAGON_H__
#define __ENEMY_BLUEDRAGON_H__

#include "Enemy.h"
#include "Path.h"
#include "ModuleParticles.h"

class Enemy_BlueDragon : public Enemy {
public:

	Enemy_BlueDragon(int x, int y);

	void Update();

private:

	Path path;

	float waveRatio = 0.0f;

	float waveRatioSpeed = 0.2f;

	int spawn_y = 0;

	int waveHeight = 15;

	Animation DrakeAnim1;
	
};
#endif // __ENEMY_SINGLETANK_H__
