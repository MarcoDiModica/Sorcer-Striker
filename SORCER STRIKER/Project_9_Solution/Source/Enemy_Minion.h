#ifndef __ENEMY_MINION_H__
#define __ENEMY_MINION_H__

#include "Enemy.h"
#include "Path.h"
#include "ModuleParticles.h"



class Enemy_Minion :public Enemy {
public:

	Enemy_Minion(int x, int y);

	void Update();

	/*Animation dedge;*/


private:

	Path path;

	int yoldi;

	float waveRatio = 0.03f;

	float waveRatioSpeed = 0.03f;

	int spawn_y = 0;

	int waveHeight = 50;

	Animation flyAnim;

	int initialY;
	uint distanceUp;
	int randomNumber;



	enum class State {
		MovingUp,
	    MovingDown
	};

	State state;





};

#endif 