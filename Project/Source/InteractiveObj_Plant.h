#ifndef __INTERACTIVEOBJ_PLANT_H__
#define __INTERACTIVEOBJ_PLANT_H__

#include "InteractiveObj.h"
#include "Path.h"

class InteractiveObj_Plant : public InteractiveObject
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	InteractiveObj_Plant(int x, int y);

	// The Interactive Object is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

	//

private:
	// A set of steps that define the position in the screen
	// And an animation for each step
	Path path;

	// This Interactive Object has one sprite and one frame
	// We are keeping it an animation for consistency with other enemies
	Animation stand;
};

#endif // __INTERACTIVEOBJ_PLANT_H__