#ifndef __ARROW_H__
#define __ARROW_H__

#include "Enemy.h"
#include "Path.h"
#include "ModuleParticles.h"

class Arrow : public Enemy {
public:

	Arrow(int x, int y);

	void Update();

private:


	int mondongo = 2.00f;


	Uint32 current;
	Uint32 next;
	Uint32 interval = 2700;
	Uint32 start;



	Animation Cristal;

	//mabybe add some more
};
#endif
