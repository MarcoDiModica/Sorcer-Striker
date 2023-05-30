#ifndef __BOOK_H__
#define __BOOK_H__

#include "Enemy.h"

class Book :public Enemy {
public:

	Book(int x, int y);

	void Update();

private:

	float waveRatio = 0.0f;

	// The speed at which the wave ratio is increased
	float waveRatioSpeed = 0.2f;

	// The original spawning position. The wave will be calculated from that
	int spawn_y = 0;

	// The total height of the wave
	int waveHeight = 15;

	uint buk = 0;

	// The enemy animation
	Animation hoverAnim;

};

#endif // __Chest_H__ 