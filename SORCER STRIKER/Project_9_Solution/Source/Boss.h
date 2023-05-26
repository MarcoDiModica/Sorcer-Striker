#ifndef __ENEMY_BOSS_H__
#define __ENEMY_BOSS_H__

#include "Enemy.h"
#include "Path.h"
#include "ModuleParticles.h"


class Boss :public Enemy {
public:

	Boss(int x, int y);

	void Update();

private:

	Path path;

	int yoldi;

	float waveRatio = 0.9f;

	float waveRatioSpeed = 0.03f;

	int spawn_y = 0;

	int waveHeight = 50;

	Animation flyAnim;
};

#endif 