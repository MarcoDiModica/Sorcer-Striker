#ifndef __REVERSEDT_H__
#define __REVERSEDT_H__

#include "Enemy.h"

class ReverseDT : public Enemy {
public:

	ReverseDT(int x, int y);

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
	Uint32 interval = 800;
};
#endif // __REVERSEDT__
