#include "InteractiveObj_Plant.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"

InteractiveObj_Plant::InteractiveObj_Plant(int x, int y) : InteractiveObject(x, y)
{
	stand.PushBack({ 5,70,56,32 });
	currentAnim = &stand;

	//path.PushBack({ -1.0f, -0.5f }, 100);
	//path.PushBack({ -1.0f, 0.5f }, 80);
	//path.PushBack({ -1.0f, 1.0f }, 80);

	rotCenter.x = 56 / 2;
	rotCenter.y = 32;

	collider = App->collisions->AddCollider({ 0, 0, 54, 32 }, Collider::Type::PLANT, (Module*)App->interactiveObj);
}

void InteractiveObj_Plant::Update()
{
	path.Update();
	//position = spawnPos + path.GetRelativePosition();

	if (App->player->plantCollision == true)
	{
		if (App->player->position.x > position.x + 25)
		{
			//angle = 0;
			angle = -3 - App->player->speed_F * 3;
		}
		else if (App->player->position.x < position.x + 20)
		{
			//angle = 0;
			angle = 3 + App->player->speed_F * 3;
		}
		else
		{
			//if (App->player->PlayerLookingPosition == 1) 
			//if (App->player->PlayerLookingPosition == 2) 
			angle = 0;
		}
	}
	else if (App->player->plantCollision == false)
	{
		angle = 0;
	}

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	InteractiveObject::Update();
}

//