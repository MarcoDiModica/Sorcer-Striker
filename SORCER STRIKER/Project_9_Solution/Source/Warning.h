#ifndef __WARNING_H__
#define __WARNING_H__

#include "Enemy.h"
#include "Path.h"
#include "ModuleParticles.h"

class Warning : public Enemy {
public:

	Warning(int x, int y);

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