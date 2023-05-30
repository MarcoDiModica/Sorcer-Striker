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

	float waveRatio = 0.0f;

	float waveRatioSpeed = 0.2f;
	int mondongo = -3.00f;
	int spawn_y = 0;
	int spawn_x = 0;

	int waveHeight = 15;


	Animation Heroina;

	//mabybe add some more
};

#endif
