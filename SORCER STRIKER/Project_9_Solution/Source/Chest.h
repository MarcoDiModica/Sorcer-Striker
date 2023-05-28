#ifndef __CHEST_H__
#define __CHEST_H__

#include "Enemy.h"

class Chest :public Enemy {
public:

	Chest(int x, int y);

	void Update();

private:

	float waveRatio = 0.0f;

	// The speed at which the wave ratio is increased
	float waveRatioSpeed = 0.1f;

	// The original spawning position. The wave will be calculated from that
	int spawn_y = 0;

	// The total height of the wave
	int waveHeight = 15;

	// The enemy animation
	Animation hoverAnim;
	Animation hoverAnim2;

};

#endif // __Chest_H__ 