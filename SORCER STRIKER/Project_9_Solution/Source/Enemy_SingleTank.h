#ifndef __ENEMY_SINGLETANK_H__
#define __ENEMY_SINGLETANK_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_SingleTank : public Enemy {
public:

	Enemy_SingleTank(int x, int y);

	void Update();

private:

	Path path;
	bool mikados = false;

	float waveRatio = 0.0f;

	float waveRatioSpeed = 0.2f;

	int spawn_y = 0;

	int waveHeight = 15;

	Animation Anim1;
	Animation Anim2;
	Animation Anim1Rev;
	Animation Mark;

	Uint32 current;
	Uint32 next;
	Uint32 interval = 800;
};
#endif // __ENEMY_SINGLETANK_H__
