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

	Uint32 current;
	Uint32 next;
	Uint32 interval = 1000;


private:

	Path path;

	int yoldi;

	float waveRatio = 0.03f;

	float waveRatioSpeed = 0.03f;

	int spawn_y = 0;

	int waveHeight = 50;

	Animation flyAnim;
	Animation dedge;


};

#endif 