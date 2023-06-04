#ifndef __ENEMY_BOSS_H__
#define __ENEMY_BOSS_H__

#include "Enemy.h"
#include "Path.h"
#include "ModuleParticles.h"
#include "Boss_Left.h"
#include "Boss_Right.h"
#include "Application.h"



class Boss :public Enemy {
public:

	Boss(int x, int y);

	void Update();

private:

	Path path;

	int yoldi;

	float waveRatio = 0.03f;

	float waveRatioSpeed = 0.03f;

	int spawn_y = 0;

	int waveHeight = 10;
	uint loseFx = 0;
	bool erm = false;
	Animation flyAnim;
	Animation dedge;
	uint next;
	uint current;
	uint spawnInterval;

	uint id = 0;
};

#endif 