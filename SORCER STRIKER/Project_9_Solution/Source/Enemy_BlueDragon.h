#ifndef __ENEMY_BLUEDRAGON_H__
#define __ENEMY_BLUEDRAGON_H__

#include "Enemy.h"
#include "Path.h"
#include "ModuleParticles.h"

class Enemy_BlueDragon : public Enemy {
public:

	Enemy_BlueDragon(int x, int y);

	void Update();

private:

	Path path;

	Animation DrakeAnim1;
	Animation DrakeAnim2;
	Animation DrakeAnim3;
	Animation DrakeAnim4;

	Uint32 current;
	Uint32 next;
	Uint32 interval = 800;
};
#endif // __ENEMY_SINGLETANK_H__
