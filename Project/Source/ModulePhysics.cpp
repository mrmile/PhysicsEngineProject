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
#include "ModuleEnemies.h"
#include "Enemy.h"

#include <iostream>
using namespace std;

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

	vx = 0;
	vy = 0;

	ax = 0;
	ay = 0;

	fx = 0;
	fy = 0;


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
	
	//Test
	/*
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
	*/

	// Step #0: Reset total acceleration and total accumulated force of the player (clear old values)
	//App->player->fy = 0.0f;
	//App->player->ay = 0.0f;

	//App->player->fx = 0.0f;
	//App->player->ax = 0.0f;

	// Step #1: Compute forces

		// Compute Gravity force
	double fgx = App->player->mass * 0.0f;
	double fgy = App->player->mass * 0.005f; // Let's assume gravity is constant and downwards

	// Add gravity force to the total accumulated force of the player
	App->player->fx += fgx;
	if(App->player->touchingGround==false)App->player->fy += fgy;
	dt = 1;

	// Compute Aerodynamic Lift & Drag forces (not done yet)
	//double speed = App->player->speed(App->player->vx - atmosphere.windx, App->player->vy - atmosphere.windy);
	//double fdrag = 0.5 * atmosphere.density * speed * speed * App->player->surface * App->player->cd;
	//double flift = 0.5 * atmosphere.density * speed * speed * App->player->surface * App->player->cl;
	//double fdx = -fdrag; // Let's assume Drag is aligned with x-axis (in your game, generalize this)
	//double fdy = flift; // Let's assume Lift is perpendicular with x-axis (in your game, generalize this)

	// Add drag force to the total accumulated force of the player
	//App->player->fx += fdx;
	//App->player->fy += fdy;

	//App->player->fx += App->player->ffx;

	// Other forces
	// ...

// Step #2: 2nd Newton's Law: SUM_Forces = mass * accel --> accel = SUM_Forces / mass
	App->player->ax = App->player->fx / App->player->mass;
	if (App->player->touchingGround == false)App->player->ay = App->player->fy / App->player->mass;

	// Step #3: Integrate --> from accel to new velocity & new position. 
	// We will use the 2nd order "Velocity Verlet" method for integration.
	// You can also move this code into a subroutine: integrator_velocity_verlet(player, dt);
	App->player->position.x += App->player->vx * dt + 0.5 * App->player->ax * dt * dt;
	if (App->player->touchingGround == false)App->player->position.y += App->player->vy * dt + 0.5 * App->player->ay * dt * dt;
	App->player->vx += App->player->ax * dt;
	if (App->player->touchingGround == false)App->player->vy += App->player->ay * dt;

	//cout << App->player->position.x << endl;
	//cout << App->player->position.y << endl << endl;

	//LOG("Player vX: %i\n", App->player->vx);
	//LOG("Player vY: %i\n", App->player->vy);

	// Step #4: solve collisions <-- En el apartado de collisions de la entidad
	/*
	if (App->player->position.y < ground.y)
	{
		// For now, just stop the player when it reaches the ground.
		App->player->vx = App->player->vy = 0.0;
		App->player->ax = App->player->ay = 0.0;
		App->player->fx = App->player->fy = 0.0;
		App->player->physics_enabled = false;
	}
	*/
	
	//Enemies physics had to change the enemies list to public
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (App->enemies->enemies[i] != nullptr)
		{
			double fgx_enemies = App->enemies->enemies[i]->mass * 0.0f;
			double fgy_enemies = App->enemies->enemies[i]->mass * 0.005f;


			App->enemies->enemies[i]->fx += fgx_enemies;
			if (App->enemies->enemies[i]->touchingGround == false)App->enemies->enemies[i]->fy += fgy_enemies;
			dt = 1;
			App->enemies->enemies[i]->ax = App->enemies->enemies[i]->fx / App->enemies->enemies[i]->mass;
			if (App->enemies->enemies[i]->touchingGround == false)App->enemies->enemies[i]->ay = App->enemies->enemies[i]->fy / App->enemies->enemies[i]->mass;

			App->enemies->enemies[i]->position.x += App->enemies->enemies[i]->vx * dt + 0.5 * App->enemies->enemies[i]->ax * dt * dt;
			if (App->enemies->enemies[i]->touchingGround == false)App->enemies->enemies[i]->position.y += App->enemies->enemies[i]->vy * dt + 0.5 * App->enemies->enemies[i]->ay * dt * dt;
			App->enemies->enemies[i]->vx += App->enemies->enemies[i]->ax * dt;
			if (App->enemies->enemies[i]->touchingGround == false)App->enemies->enemies[i]->vy += App->enemies->enemies[i]->ay * dt;
		}
	}
	
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (App->particles->particles[i] != nullptr)
		{
			if (App->particles->particles[i]->collider->type != Collider::Type::EXPLOSION)
			{
				double fgx_particles = App->particles->particles[i]->mass * 0.0f;
				double fgy_particles = App->particles->particles[i]->mass * 0.005f;

				App->particles->particles[i]->fx += fgx_particles;
				App->particles->particles[i]->fy += fgy_particles;
				dt = 1;
				App->particles->particles[i]->ax = App->particles->particles[i]->fx / App->particles->particles[i]->mass;
				App->particles->particles[i]->ay = App->particles->particles[i]->fy / App->particles->particles[i]->mass;

				App->particles->particles[i]->position.x += App->particles->particles[i]->vx * dt + 0.5 * App->particles->particles[i]->ax * dt * dt;
				App->particles->particles[i]->position.y += App->particles->particles[i]->vy * dt + 0.5 * App->particles->particles[i]->ay * dt * dt - 2;
				App->particles->particles[i]->vx += App->particles->particles[i]->ax * dt;
				App->particles->particles[i]->vy += App->particles->particles[i]->ay * dt;
			}

		}
		
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

float ModulePhysics::DragForceRight(double velocity)
{
	float force;
	
	float dragCoeficient = 0.52; //Cambiar aqui el Coeficiente de la Drag Force
	force = -dragCoeficient * velocity;

	return force;
	
}
float ModulePhysics::DragForceLeft(double velocity)
{
	float force;
	float dragCoeficient = 7.52; //Cambiar aqui el Coeficiente de la Drag Force

	force = -dragCoeficient * velocity;

	return force;
}