#ifndef __MODULE_INTERACTIVEOBJ_H__
#define __MODULE_INTERACTIVEOBJ_H__

#include "Module.h"
#include "InteractiveObj.h"

#define MAX_INTERACTIVE_OBJECTS 100

enum class Interactive_Object_Type
{
	NO_TYPE,
	PLANT,
};

struct InteractiveObjSpawnpoint
{
	Interactive_Object_Type type = Interactive_Object_Type::NO_TYPE;
	int x, y;
};

class IteractiveObject;
struct SDL_Texture;

class ModuleInteractiveObj : public Module
{
public:
	// Constructor
	ModuleInteractiveObj(bool startEnabled);

	// Destructor
	~ModuleInteractiveObj();

	// Called when the module is activated
	// Loads the necessary textures for the interactive objects
	bool Start() override;

	// Called at the beginning of the application loop
	// Removes all interactive objects pending to delete
	Update_Status PreUpdate() override;

	// Called at the middle of the application loop
	// Handles all interactive objects logic and spawning/despawning
	Update_Status Update() override;

	// Called at the end of the application loop
	// Iterates all the interactive objects and draws them
	Update_Status PostUpdate() override;

	// Called on application exit
	// Destroys all active interactive objects left in the array
	bool CleanUp() override;

	// Called when an interactive object collider hits another collider
	// The interactive object is destroyed and an explosion particle is fired
	void OnCollision(Collider* c1, Collider* c2) override;

	// Add an interactive object into the queue to be spawned later
	bool AddInteractiveObject(Interactive_Object_Type type, int x, int y);

	// Iterates the queue and checks for camera position
	void HandleInteractiveObjectsSpawn();

	// Destroys any interactive object that have moved outside the camera limits
	void HandleInteractiveObjectsDespawn();

private:
	// Spawns a new interactive object using the data from the queue
	void SpawnInteractiveObject(const InteractiveObjSpawnpoint& info);

private:
	// A queue with all spawn points information
	InteractiveObjSpawnpoint spawnQueue[MAX_INTERACTIVE_OBJECTS];

	// All spawned interactive objects in the scene
	InteractiveObject* interactiveObject[MAX_INTERACTIVE_OBJECTS] = { nullptr };

	// The interactive object sprite sheet
	SDL_Texture* texture = nullptr;

	// The audio fxs for interactive objects
	int interactiveObjectFx = 0;
};

#endif // __MODULE_INTERACTIVEOBJ_H__