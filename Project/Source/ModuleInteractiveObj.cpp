#include "ModuleInteractiveObj.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"

#include "InteractiveObj.h"
#include "InteractiveObj_Plant.h"

#define SPAWN_MARGIN 50


ModuleInteractiveObj::ModuleInteractiveObj(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_INTERACTIVE_OBJECTS; ++i)
		interactiveObject[i] = nullptr;
}

ModuleInteractiveObj::~ModuleInteractiveObj()
{

}

bool ModuleInteractiveObj::Start()
{
	texture = App->textures->Load("Assets/interactive.png");
	interactiveObjectFx = App->audio->LoadFx("Assets/Fx/explosion.wav");

	return true;
}


Update_Status ModuleInteractiveObj::PreUpdate()
{
	// Remove all interactiveObjects scheduled for deletion
	for (uint i = 0; i < MAX_INTERACTIVE_OBJECTS; ++i)
	{
		if (interactiveObject[i] != nullptr && interactiveObject[i]->pendingToDelete)
		{
			delete interactiveObject[i];
			interactiveObject[i] = nullptr;
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleInteractiveObj::Update()
{
	HandleInteractiveObjectsSpawn();

	for (uint i = 0; i < MAX_INTERACTIVE_OBJECTS; ++i)
	{
		if(interactiveObject[i] != nullptr)
			interactiveObject[i]->Update();
	}

	HandleInteractiveObjectsDespawn();

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleInteractiveObj::PostUpdate()
{
	for (uint i = 0; i < MAX_INTERACTIVE_OBJECTS; ++i)
	{
		if (interactiveObject[i] != nullptr)
			interactiveObject[i]->Draw();
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInteractiveObj::CleanUp()
{
	LOG("Freeing all interactiveObjects");

	for(uint i = 0; i < MAX_INTERACTIVE_OBJECTS; ++i)
	{
		if(interactiveObject[i] != nullptr)
		{
			delete interactiveObject[i];
			interactiveObject[i] = nullptr;
		}
	}

	return true;
}

bool ModuleInteractiveObj::AddInteractiveObject(Interactive_Object_Type type, int x, int y)
{
	bool ret = false;

	for(uint i = 0; i < MAX_INTERACTIVE_OBJECTS; ++i)
	{
		if(spawnQueue[i].type == Interactive_Object_Type::NO_TYPE)
		{
			spawnQueue[i].type = type;
			spawnQueue[i].x = x;
			spawnQueue[i].y = y;
			ret = true;
			break;
		}
	}

	return ret;
}

void ModuleInteractiveObj::HandleInteractiveObjectsSpawn()
{
	// Iterate all the interactiveObjects queue
	for (uint i = 0; i < MAX_INTERACTIVE_OBJECTS; ++i)
	{
		if (spawnQueue[i].type != Interactive_Object_Type::NO_TYPE)
		{
			// Spawn a new interactive object if the screen has reached a spawn position
			if (spawnQueue[i].x * SCREEN_SIZE < App->render->camera.x + (App->render->camera.w * SCREEN_SIZE) + SPAWN_MARGIN)
			{
				//Not used
			}
			LOG("Spawning interactive object at %d", spawnQueue[i].x * SCREEN_SIZE);

			SpawnInteractiveObject(spawnQueue[i]);
			spawnQueue[i].type = Interactive_Object_Type::NO_TYPE; // Removing the newly spawned interactive object from the queue
		}
	}
}

void ModuleInteractiveObj::HandleInteractiveObjectsDespawn()
{
	// Iterate existing interactiveObjects
	for (uint i = 0; i < MAX_INTERACTIVE_OBJECTS; ++i)
	{
		if (interactiveObject[i] != nullptr)
		{
			// Delete the interactive object when it has reached the end of the screen
			if (interactiveObject[i]->position.x * SCREEN_SIZE < (App->render->camera.x) - SPAWN_MARGIN)
			{
				//Not used
			}
			//LOG("DeSpawning interactive object at %d", interactiveObject[i]->position.x * SCREEN_SIZE);

			//interactiveObject[i]->SetToDelete();
		}
	}
}

void ModuleInteractiveObj::SpawnInteractiveObject(const InteractiveObjSpawnpoint& info)
{
	// Find an empty slot in the interactiveObjects array
	for (uint i = 0; i < MAX_INTERACTIVE_OBJECTS; ++i)
	{
		if (interactiveObject[i] == nullptr)
		{
			switch (info.type)
			{
				
				case Interactive_Object_Type::PLANT:
					interactiveObject[i] = new InteractiveObj_Plant(info.x, info.y);
					break;
				
			}
			interactiveObject[i]->texture = texture;
			interactiveObject[i]->destroyedFx = interactiveObjectFx;
			break;
		}
	}
}

void ModuleInteractiveObj::OnCollision(Collider* c1, Collider* c2)
{
	for(uint i = 0; i < MAX_INTERACTIVE_OBJECTS; ++i)
	{
		if(interactiveObject[i] != nullptr && interactiveObject[i]->GetCollider() == c1)
		{
			interactiveObject[i]->OnCollision(c2); //Notify the interactive object of a collision
			break;
		}
	}
}