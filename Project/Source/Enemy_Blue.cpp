#include "Enemy_Blue.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModulePhysics.h"
#include "ModuleAudio.h"
#include "p2Point.h"
#include "ModuleInput.h"
#include "SceneLevel1.h"
#include "ModuleRender.h"
#include "Particle.h"

Enemy_Blue::Enemy_Blue(int x, int y) : Enemy(x, y)
{
	Enemy::EnemyHp = 100;
	position.x = 150;
	position.y = 157;

	// idle left
	idleLeftAnim.PushBack({ 2, 0, 31, 39 });
	idleLeftAnim.PushBack({ 32, 0, 30, 39 });
	idleLeftAnim.PushBack({ 61, 0, 30, 39 });
	idleLeftAnim.loop = true;
	idleLeftAnim.speed = 0.1f;

	// idle Right
	idleRightAnim.PushBack({ 660, 0, 30, 39 });
	idleRightAnim.PushBack({ 690, 0, 27, 39 });
	idleRightAnim.PushBack({ 717, 0, 30, 39 });
	idleRightAnim.loop = true;
	idleRightAnim.speed = 0.1f;

	// Move left
	leftAnim.PushBack({ 375, 0, 29, 39 });
	leftAnim.PushBack({ 407, 0, 29, 39 });
	leftAnim.PushBack({ 440, 0, 29, 39 });
	leftAnim.PushBack({ 472, 0, 29, 39 });
	leftAnim.PushBack({ 502, 0, 29, 39 });
	leftAnim.PushBack({ 530, 0, 28, 39 });
	leftAnim.PushBack({ 561, 0, 29, 39 });
	leftAnim.PushBack({ 593, 0, 29, 39 });
	leftAnim.PushBack({ 621, 0, 29, 39 });
	leftAnim.loop = true;
	leftAnim.speed = 0.3f;

	// Move right
	rightAnim.PushBack({ 97, 0, 32, 39 });
	rightAnim.PushBack({ 129, 0, 27, 39 });
	rightAnim.PushBack({ 156, 0, 28, 39 });
	rightAnim.PushBack({ 187, 0, 31, 39 });
	rightAnim.PushBack({ 218, 0, 31, 39 });
	rightAnim.PushBack({ 247, 0, 29, 39 });
	rightAnim.PushBack({ 277, 0, 30, 39 });
	rightAnim.PushBack({ 308, 0, 31, 39 });
	rightAnim.PushBack({ 342, 0, 34, 39 });
	rightAnim.loop = true;
	rightAnim.speed = 0.3f;

	// jump
	jumpAnim.PushBack({ 717, 0, 31, 39 });
	jumpAnim.PushBack({ 687, 0, 30, 39 });
	jumpAnim.PushBack({ 658, 0, 30, 39 });
	jumpAnim.loop = true;
	jumpAnim.speed = 0.1f;

	deadAnim.PushBack({ 717, 0, 31, 39 });
	deadAnim.PushBack({ 687, 0, 30, 39 });
	deadAnim.PushBack({ 658, 0, 30, 39 });
	deadAnim.loop = true;
	deadAnim.speed = 0.1f;

	x = 0.0f;
	y = 0.0f;
	vx = 0.0f;
	vy = 0.0f;
	ax = 0.0f; //
	ay = 0.0f; //
	fx = 0.0f;
	fy = 0.0f;
	dt = 1.0f; //


	mass = 10.0f;
	surface = 2.0f;
	cd = 0.4f;
	cl = 1.2f;

	forceTimerX = 0.0f;
	enemy1FPS = 0;

	collider = App->collisions->AddCollider({position.x+10, position.y+6, 16, 30}, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_Blue::Update()
{
	Enemy_Counter++;
	enemy1FPS++;
	collider->SetPos(position.x+10, position.y+6);
	currentAnim = &idleRightAnim;
	if (App->sceneLevel_1->turnDelay < 120) hasShot = false;
	if (App->sceneLevel_1->TURN == 2 && App->sceneLevel_1->turnDelay > 120 && destroyed == false)
	{
		//ADD TURN THINGS HERE
		if (position.x > App->player->position.x && hasShot==false)
		{
			if (Enemy_Counter >= 0 && Enemy_Counter < 240)
			{
				currentAnim = &idleLeftAnim;
				speed_F = 1;
				position.x--;
				fx = -1.0f;
			}
			if (position.DistanceTo(App->player->position) > 100 && position.DistanceTo(App->player->position) < 500)
			{
				App->audio->PlayFx(App->player->shoot);
				App->particles->AddParticle(App->particles->shootLeft, position.x + 10, position.y, Collider::Type::ENEMY_SHOT);
				for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
				{
					if (App->particles->particles[i] != nullptr)
					{
						App->particles->particles[i]->vx = (((double)App->player->position.x - position.x) / 240);
					}
				}
				hasShot = true;
			}
			if (Enemy_Counter > 240)
			{
				App->sceneLevel_1->TURN = 1;
				Enemy_Counter = 0;
			}
			
		}
		if (position.x < App->player->position.x && hasShot==false)
		{
			if (Enemy_Counter >= 0 && Enemy_Counter < 240)
			{
				currentAnim = &idleRightAnim;
				speed_F = 1;
				fx = 1.0f;
			}
			if (position.DistanceTo(App->player->position) > 100 && position.DistanceTo(App->player->position) < 500)
			{
				App->audio->PlayFx(App->player->shoot);
				App->particles->AddParticle(App->particles->shootRight, position.x + 10, position.y, Collider::Type::ENEMY_SHOT);
				for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
				{
					if (App->particles->particles[i] != nullptr)
					{
						App->particles->particles[i]->vx = (((double)App->player->position.x - position.x) / 240);
					}
				}
				hasShot = true;
			}
			if (Enemy_Counter > 240)
			{
				App->sceneLevel_1->TURN = 1;
				Enemy_Counter = 0;
			}
			
		}

		if (hasShot == true)
		{
			App->player->throwCounter = 0;
			App->sceneLevel_1->TURN = 1;

		}
			
	}
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	if (EnemyHp == 0)
	{
		if (currentAnim != &deadAnim)
		{
			deadAnim.Reset();
			currentAnim = &deadAnim;
		}

		//SetToDelete(); // Se hace automaticamente luego
	}

	Enemy::Update();
}
