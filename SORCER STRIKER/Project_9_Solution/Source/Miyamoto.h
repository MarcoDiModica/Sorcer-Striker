#ifndef __MIYAMOTO_H__
#define __MIYAMOTO_H__

#include "Enemy.h"
#include "Path.h"
#include "ModuleParticles.h"

class Miyamoto : public Enemy {
public:

	Miyamoto(int x, int y);

	void Update();

private:


	int mondongo = 5.00f;


	Uint32 current;
	Uint32 next;
	Uint32 interval = 8000;
	Uint32 start;



	Animation Cristal;

	//mabybe add some more
};
#endif
