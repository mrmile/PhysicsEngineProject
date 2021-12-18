#ifndef __ENEMY_BROWNSHIP_H__
#define __ENEMY_BROWNSHIP_H__

#include "Enemy.h"


class Enemy_BrownShip : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_BrownShip(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

private:
	
	Animation idleRightAnim;
	Animation idleLeftAnim;

	Animation rightAnim;
	Animation leftAnim;

	Animation jumpAnim;
};

#endif // __ENEMY_BROWNSHIP_H__