#ifndef __ENEMY_BLUEDRAGON2_H__
#define __ENEMY_BLUEDRAGON2_H__

#include "Enemy.h"
#include "Path.h"
#include "ModuleParticles.h"

class Enemy_BlueDragon2 : public Enemy {
public:

	Enemy_BlueDragon2(int x, int y);

	void Update();

private:

	Animation DrakeAnim1;
	Animation DrakeAnim2;

	Uint32 current;
	Uint32 next;
	Uint32 interval = 800;
};
#endif
