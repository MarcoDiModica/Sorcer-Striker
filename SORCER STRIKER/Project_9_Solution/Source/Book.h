#ifndef __BOOK_H__
#define __BOOK_H__

#include "Enemy.h"

class Book :public Enemy {
public:

	Book(int x, int y);

	void Update();

private:

	uint buk = 0;

	// The enemy animation
	Animation hoverAnim;

};

#endif // __Chest_H__ 