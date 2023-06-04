#ifndef __CLEAR_H__
#define __CLEAR_H__

#include "Enemy.h"
#include "Path.h"
#include "ModuleParticles.h"

class Clear : public Enemy {
public:

	Clear(int x, int y);

	void Update();

private:

	Path path;

	int mondongo = -3.00f;

	Animation Heroina;

	//mabybe add some more
};

#endif
