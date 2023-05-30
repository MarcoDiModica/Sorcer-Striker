#ifndef __ENEMY_SINGLETANK_H__
#define __ENEMY_SINGLETANK_H__

#include "Enemy.h"

class Enemy_SingleTank : public Enemy {
public:

	Enemy_SingleTank(int x, int y);

	void Update();

private:

	float waveRatio = 0.0f;

	float waveRatioSpeed = 0.2f;

	int spawn_y = 0;

	int waveHeight = 15;

	Animation Anim1;
	Animation Anim2;
	Animation Anim1Rev;
};
#endif // __ENEMY_SINGLETANK_H__
