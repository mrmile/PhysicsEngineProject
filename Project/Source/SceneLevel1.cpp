#include "SceneLevel1.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModuleInteractiveObj.h"
#include "ModulePlayer.h"

SceneLevel1::SceneLevel1(bool startEnabled) : Module(startEnabled)
{

}

SceneLevel1::~SceneLevel1()
{

}

// Load assets
bool SceneLevel1::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTextureL1 = App->textures->Load("Assets/background_L1.png");
	

	level = App->textures->Load("Assets/scenario.png");

	App->audio->PlayMusic("Assets/_.ogg", 1.0f);

	//Collider example
	//App->collisions->AddCollider({ 0, 224, 3930, 16 }, Collider::Type::WALL);

	App->collisions->AddCollider({ 0, 0, 90000, 90000 }, Collider::Type::NULL_COLLIDER);

	

	App->render->camera.x = 2200;
	App->render->camera.y = 0;

	App->player->Enable();
	App->enemies->Enable();
	App->interactiveObj->Enable();

	return ret;
}

Update_Status SceneLevel1::Update()
{
	//App->render->camera.x += 3;

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneLevel1::PostUpdate()
{
	// Draw everything --------------------------------------

	App->render->Blit(bgTextureL1, 0, 0, NULL, 0.6f);
	
	App->render->Blit(level, 0, 0, NULL, 1.0f);

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneLevel1::CleanUp()
{
	App->player->Disable();
	App->enemies->Disable();
	App->interactiveObj->Disable();

	return true;
}