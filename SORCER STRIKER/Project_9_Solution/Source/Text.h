#ifndef __TEXT_H__
#define __TEXT_H__

#include "Enemy.h"
#include "Path.h"
#include "ModuleParticles.h"

class Text : public Enemy {
public:

	Text(int x, int y);

	void Update();

private:


	int mondongo = 2.00f;


	Uint32 current;
	Uint32 next;
	Uint32 interval = 8000;
	Uint32 start;



	Animation Cristal;

	//mabybe add some more
};
#endif
