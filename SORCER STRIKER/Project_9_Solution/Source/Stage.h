#ifndef __STAGE_H__
#define __STAGE_H__

#include "Enemy.h"
#include "Path.h"
#include "ModuleParticles.h"

class Stage : public Enemy {
public:

	Stage(int x, int y);

	void Update();

private:

	Path path;

	float waveRatio = 0.0f;

	float waveRatioSpeed = 0.2f;
	int mondongo = 2.00f;
	int spawn_y = 0;
	int spawn_x = 0;

	int waveHeight = 15;


	Animation Cristal;

	//mabybe add some more
};
#endif