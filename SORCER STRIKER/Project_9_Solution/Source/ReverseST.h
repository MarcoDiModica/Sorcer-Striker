#ifndef __REVERSEST_H__
#define __REVERSEST_H__

#include "Enemy.h"
#include "Path.h"

class ReverseST : public Enemy {
public:

	ReverseST(int x, int y);

	void Update();

private:

	Path path;

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
#endif // __REVERSEST_H__

