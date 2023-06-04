#ifndef __COIN_H__
#define __COIN_H__

#include "Enemy.h"

class Coin :public Enemy {
public:

	Coin(int x, int y);

	void Update();

private:
	// The enemy animation
	Animation hoverAnim;

};

#endif // __COIN_H__ 