#ifndef __INTERACTIVEOBJ_H__
#define __INTERACTIVEOBJ_H__

#include "p2Point.h"
#include "Animation.h"

struct SDL_Texture;
struct Collider;

class InteractiveObject
{
public:
	// Constructor
	// Saves the spawn position for later movement calculations
	InteractiveObject(int x, int y);

	// Destructor
	virtual ~InteractiveObject();

	// Returns the interactive object's collider
	const Collider* GetCollider() const;

	// Called from inhering interactive' Udpate
	// Updates animation and collider position
	virtual void Update();

	// Called from Moduleinteractive object' Update
	virtual void Draw();

	// Collision response
	virtual void OnCollision(Collider* collider);

	// Sets flag for deletion and for the collider aswell
	virtual void SetToDelete();

public:
	// The current position in the world
	iPoint position;
	iPoint rotCenter;
	double angle;

	// The interactive object's texture
	SDL_Texture* texture = nullptr;

	// Sound fx when destroyed
	int destroyedFx = 0;

	// A flag for the interactive object. Important! We do not delete objects instantly
	bool pendingToDelete = false;

protected:
	// A ptr to the current animation
	Animation* currentAnim = nullptr;

	// The Interactive object collider
	Collider* collider = nullptr;

	// Original spawn position. Stored for movement calculations
	iPoint spawnPos;
};

#endif // __INTERACTIVEOBJ_H__