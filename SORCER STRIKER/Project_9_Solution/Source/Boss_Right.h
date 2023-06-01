#ifndef __ENEMY_BOSSRIGHT_H__
#define __ENEMY_BOSSRIGHT_H__

#include "Enemy.h"
#include "Path.h"
#include "ModuleParticles.h"



class BossRight :public Enemy {
public:

	BossRight(int x, int y);

	void Update();

	Animation dedge;

	void DestroyRight() {
		cnt = 0;
	}

private:

	Path path;

	int yoldi;

	float waveRatio = 0.03f;

	float waveRatioSpeed = 0.03f;

	int spawn_y = 0;

	int waveHeight = 0;

	Animation flyAnim;
	


};

#endif 