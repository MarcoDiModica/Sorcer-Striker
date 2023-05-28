#ifndef __COIN_H__
#define __COIN_H__

#include "Enemy.h"

class Coin :public Enemy {
public:

	Coin(int x, int y);

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

#endif // __COIN_H__ 