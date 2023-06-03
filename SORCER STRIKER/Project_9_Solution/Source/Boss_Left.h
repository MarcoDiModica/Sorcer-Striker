#ifndef __ENEMY_BOSSLEFT_H__
#define __ENEMY_BOSSLEFT_H__

#include "Enemy.h"
#include "Path.h"
#include "ModuleParticles.h"



class BossLeft :public Enemy {
public:

	BossLeft(int x, int y);

	void Update();

	Animation dedge;
	
private:

	Path path;

	int yoldi;

	float waveRatio = 0.03f;

	float waveRatioSpeed = 0.03f;

	int spawn_y = 0;

	int waveHeight = 10;

	Animation flyAnim;

};

#endif 