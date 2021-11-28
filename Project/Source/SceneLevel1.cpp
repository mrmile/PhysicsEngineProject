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
	bgTextureL2 = App->textures->Load("Assets/background_L2.png");
	bgTextureL3 = App->textures->Load("Assets/background_L3.png");
	bgTextureL4 = App->textures->Load("Assets/background_L4.png");

	level = App->textures->Load("Assets/scenario.png");

	App->audio->PlayMusic("Assets/western.ogg", 1.0f);

	//Collider example
	//App->collisions->AddCollider({ 0, 224, 3930, 16 }, Collider::Type::WALL);

	App->collisions->AddCollider({ 0, 0, 90000, 90000 }, Collider::Type::NULL_COLLIDER);

	App->collisions->AddCollider({ 1480, -234, 10, 510 }, Collider::Type::TELEPORT_R);
	App->collisions->AddCollider({ 720, -234, 10, 510 }, Collider::Type::TELEPORT_L);

	// Enemy example
	//App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 830, 100);

	// Interactive Plant
	App->interactiveObj->AddInteractiveObject(Interactive_Object_Type::PLANT, 620, 180);
	App->interactiveObj->AddInteractiveObject(Interactive_Object_Type::PLANT, 1350, 180);

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

	App->render->Blit(bgTextureL4, bgTextureL4X, -40, NULL, 0.2f);
	App->render->Blit(bgTextureL4, bgTextureL4X2 + 1120, -40, NULL, 0.2f);
	App->render->Blit(bgTextureL4, bgTextureL4X3 + 2240, -40, NULL, 0.2f);

	if (bgTextureL4X < -1264) bgTextureL4X = bgTextureL4X + 1120;
	if (bgTextureL4X2 < -1264) bgTextureL4X2 = bgTextureL4X2 + 1120;
	if (bgTextureL4X3 < -1264) bgTextureL4X3 = bgTextureL4X3 + 1120;

	if (bgTextureL4X > 100) bgTextureL4X = bgTextureL4X - 1120;
	if (bgTextureL4X2 > 100) bgTextureL4X2 = bgTextureL4X - 1120;
	if (bgTextureL4X3 > 100) bgTextureL4X3 = bgTextureL4X - 1120;

	App->render->Blit(bgTextureL3, bgTextureL3X, -40, NULL, 0.4f);
	App->render->Blit(bgTextureL3, bgTextureL3X2 + 560, -40, NULL, 0.4f);
	App->render->Blit(bgTextureL3, bgTextureL3X2 + 1120, -40, NULL, 0.4f);

	if (bgTextureL3X < -632) bgTextureL3X = bgTextureL3X + 1120;
	if (bgTextureL3X2 < -632) bgTextureL3X2 = bgTextureL3X2 + 1120;
	if (bgTextureL3X3 < -632) bgTextureL3X3 = bgTextureL3X3 + 1120;

	if (bgTextureL3X > 438) bgTextureL3X = bgTextureL3X - 1120;
	if (bgTextureL3X2 > 438) bgTextureL3X2 = bgTextureL3X - 1120;
	if (bgTextureL3X3 > 438) bgTextureL3X3 = bgTextureL3X - 1120;

	App->render->Blit(bgTextureL2, bgTextureL2X, -40, NULL, 0.5f);
	App->render->Blit(bgTextureL2, bgTextureL2X2 + 560, -40, NULL, 0.5f);
	App->render->Blit(bgTextureL2, bgTextureL2X2 + 1120, -40, NULL, 0.5f);

	if (bgTextureL2X < -632) bgTextureL2X = bgTextureL2X + 1120;
	if (bgTextureL2X2 < -632) bgTextureL2X2 = bgTextureL2X2 + 1120;
	if (bgTextureL2X3 < -632) bgTextureL2X3 = bgTextureL2X3 + 1120;

	if (bgTextureL2X > 438) bgTextureL2X = bgTextureL2X - 1120;
	if (bgTextureL2X2 > 438) bgTextureL2X2 = bgTextureL2X - 1120;
	if (bgTextureL2X3 > 438) bgTextureL2X3 = bgTextureL2X - 1120;

	App->render->Blit(bgTextureL1, bgTextureL1X, -40, NULL, 0.6f);
	App->render->Blit(bgTextureL1, bgTextureL1X2 + 560, -40, NULL, 0.6f);
	App->render->Blit(bgTextureL1, bgTextureL1X2 + 1120, -40, NULL, 0.6f);

	if (bgTextureL1X < -632) bgTextureL1X = bgTextureL1X + 1120;
	if (bgTextureL1X2 < -632) bgTextureL1X2 = bgTextureL1X2 + 1120;
	if (bgTextureL1X3 < -632) bgTextureL1X3 = bgTextureL1X3 + 1120;

	if (bgTextureL1X > 438) bgTextureL1X = bgTextureL1X - 1120;
	if (bgTextureL1X2 > 438) bgTextureL1X2 = bgTextureL1X - 1120;
	if (bgTextureL1X3 > 438) bgTextureL1X3 = bgTextureL1X - 1120;

	App->render->Blit(level, 730, -234, NULL, 1.0f);
	App->render->Blit(level, 0, -234, NULL, 1.0f);
	App->render->Blit(level, 1460, -234, NULL, 1.0f);

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneLevel1::CleanUp()
{
	App->player->Disable();
	App->enemies->Disable();
	App->interactiveObj->Disable();

	return true;
}