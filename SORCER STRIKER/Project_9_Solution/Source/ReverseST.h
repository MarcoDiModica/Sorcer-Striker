#ifndef __REVERSEST_H__
#define __REVERSEST_H__

#include "Enemy.h"

class ReverseST : public Enemy {
public:

	ReverseST(int x, int y);

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
#endif // __REVERSEST_H__

