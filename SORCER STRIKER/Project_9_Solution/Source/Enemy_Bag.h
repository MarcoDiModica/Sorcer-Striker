#ifndef __ENEMY_BAG_H__
#define __ENEMY_BAG_H__

#include "Enemy.h"

class Enemy_Bag :public Enemy {
public:

	Enemy_Bag(int x, int y);

	void Update();

private:

	int mondongo = 2;

	Animation hoverAnim;

};

#endif // __ENEMY_BAG_H__ 