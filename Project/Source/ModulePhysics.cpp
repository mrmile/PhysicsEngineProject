#include "ModulePhysics.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "SceneLevel1.h"
#include "ModulePlayer.h"

ModulePhysics::ModulePhysics(bool startEnabled) : Module(startEnabled)
{

}

ModulePhysics::~ModulePhysics()
{

}

bool ModulePhysics::Start()
{
	
	x = 0;
	y = 0;

	Vx = 0;
	Vy = 0;

	ax = 0;
	ay = 0;

	Fx = 0;
	Fy = 0;


	mass = 0;
	surface = 0;
	cd = 0;
	

	timeCounter = 0;

	return true;
}

Update_Status ModulePhysics::PreUpdate()
{


	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModulePhysics::Update()
{
	timeCounter++;
	
	App->player->position.x += App->player->vx * App->player->dt + 0.5 * App->player->ax * App->player->dt * App->player->dt;
	App->player->position.y += App->player->vy * App->player->dt + 0.5 * App->player->ay * App->player->dt * App->player->dt;
	if (App->player->vx < 3 && App->player->vx > -3)
	{
		App->player->vx += App->player->ax * App->player->dt;
	}
	if (App->player->vy < 4 && App->player->vy > -4)
	{
		App->player->vy += App->player->ay * App->player->dt;
	}


	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModulePhysics::PostUpdate()
{


	return Update_Status::UPDATE_CONTINUE;
}

bool ModulePhysics::CleanUp()
{


	return true;
}

void ModulePhysics::OnCollision(Collider* c1, Collider* c2)
{

}

float ModulePhysics::ApplyForce(float force, float objectMass, float& t)
{
	float Vx;
	if (t == 0)Vx = 0.0f;

	Vx = (force / objectMass) * t;

	t = t + (1 / 60);

	return Vx;
}

float ModulePhysics::ReduceForce(float force, float objectMass, float& t)
{
	float Vx;
	if (t == 0)Vx = 0.0f;

	Vx = (force / objectMass) * t;

	t = t - (1 / 60);

	return Vx;
}
