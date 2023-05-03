#ifndef __ENEMY_BROWNSHIP_H__
#define __ENEMY_BROWNSHIP_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_BrownShip : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_BrownShip(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update();

private:
	// A set of steps that define the position in the screen
	// And an animation for each step
	Path path;

	float waveRatio = 0.0f;

	// The speed at which the wave ratio is increased
	float waveRatioSpeed = 0.1f;

	// The original spawning position. The wave will be calculated from that
	int spawn_y = 0;

	// The total height of the wave
	int waveHeight = 15;

	// This enemy has one sprite and one frame
	// We are keeping it an animation for consistency with other enemies
	Animation flyAnim;
	Animation turnAnim1;
	Animation turnAnim2;
	Animation turnAnim3;
	Animation turnAnim4;
};

#endif // __ENEMY_BROWNSHIP_H__