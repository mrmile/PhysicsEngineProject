#ifndef __MODULE_PHYSICS_H__
#define __MODULE_PHYSICS_H__

#include "Module.h"

#include "Globals.h"
#include "Collider.h"

struct Collider;

class ModulePhysics : public Module
{
public:
	ModulePhysics(bool startEnabled);

	~ModulePhysics();

	//Called at the beginning of the application execution
	//bool Init();

	//Called when the module is activated
	//By now we will consider all modules to be permanently active
	bool Start();

	//Called at the beginning of each application loop
	Update_Status PreUpdate();

	//Called at the middle of each application loop
	Update_Status Update();

	//Called at the end of each application loop
	Update_Status PostUpdate();

	//Called at the end of the application
	bool CleanUp();

	//Called when two colliders are intersecting
	//and the module is registered as the listener
	void OnCollision(Collider* c1, Collider* c2);

	float ApplyForce(float force, float objectMass, float& t);

	float ReduceForce(float force, float objectMass, float& t);

	//inline bool IsEnabled() const { return isEnabled; }

	
	float x, y;
	float Vx, Vy;
	float ax, ay;
	float Fx, Fy;
	
	
	int mass, surface, cd;

	int timeCounter;

private:
	//bool isEnabled = true;
};

#endif // __MODULE_PHYSICS_H__