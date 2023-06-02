#ifndef __ENEMY_DOUBLETANK_H__
#define __ENEMY_DUBLETANK_H__

#include "Enemy.h"

class Enemy_DoubleTank : public Enemy {
public:

	Enemy_DoubleTank(int x, int y);

	void Update();

private:

	float waveRatio = 0.0f;

	float waveRatioSpeed = 0.2f;

	int spawn_y = 0;

	int waveHeight = 15;

	Animation Anim1;
	Animation Anim1Rev;
	Animation Anim2;
	Animation Mark;

	Uint32 current;
	Uint32 next;
	Uint32 interval = 400;
};
#endif // __ENEMY_SINGLETANK_H__