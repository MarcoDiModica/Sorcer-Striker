#ifndef __ENEMY_BAG_H__
#define __ENEMY_BAG_H__

#include "Enemy.h"

class Enemy_Bag :public Enemy {
public:

	Enemy_Bag(int x, int y);

	void Update();

private:

	float waveRatio = 0.0f;

	// The speed at which the wave ratio is increased
	float waveRatioSpeed = 0.2f;

	// The original spawning position. The wave will be calculated from that
	int spawn_y = 0;

	// The total height of the wave
	int waveHeight = 15;

	// The enemy animation
	Animation hoverAnim;

};

#endif // __ENEMY_BAG_H__ 