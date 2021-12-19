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
	idleLeftAnim.PushBack({ 2, 0, 30, 39 });
	idleLeftAnim.PushBack({ 32, 0, 31, 39 });
	idleLeftAnim.PushBack({ 61, 0, 30, 39 });
	idleLeftAnim.loop = true;
	idleLeftAnim.speed = 0.1f;

	// idle Right
	idleRightAnim.PushBack({ 717, 0, 30, 39 });
	idleRightAnim.PushBack({ 687, 0, 31, 39 });
	idleRightAnim.PushBack({ 658, 0, 30, 39 });
	idleRightAnim.loop = true;
	idleRightAnim.speed = 0.1f;

	// Move left
	leftAnim.PushBack({ 620, 0, 29, 39 });
	leftAnim.PushBack({ 593, 0, 27, 39 });
	leftAnim.PushBack({ 562, 0, 31, 39 });
	leftAnim.PushBack({ 531, 0, 31, 39 });
	leftAnim.PushBack({ 504, 0, 26, 39 });
	leftAnim.PushBack({ 473, 0, 28, 39 });
	leftAnim.PushBack({ 441, 0, 30, 39 });
	leftAnim.PushBack({ 407, 0, 33, 37 });
	leftAnim.PushBack({ 377, 0, 29, 39 });
	leftAnim.loop = true;
	leftAnim.speed = 0.3f;

	// Move right
	rightAnim.PushBack({ 100, 0, 29, 39 });
	rightAnim.PushBack({ 130, 0, 27, 39 });
	rightAnim.PushBack({ 157, 0, 31, 39 });
	rightAnim.PushBack({ 188, 0, 31, 39 });
	rightAnim.PushBack({ 220, 0, 26, 39 });
	rightAnim.PushBack({ 249, 0, 28, 39 });
	rightAnim.PushBack({ 279, 0, 30, 39 });
	rightAnim.PushBack({ 310, 0, 33, 39 });
	rightAnim.PushBack({ 343, 0, 29, 39 });
	rightAnim.loop = true;
	rightAnim.speed = 0.3f;

	// Jump left
	jumpleftAnim.PushBack({ 720, 177, 28, 46 });
	jumpleftAnim.PushBack({ 692, 178, 28, 44 });
	jumpleftAnim.PushBack({ 663, 179, 28, 42 });
	jumpleftAnim.PushBack({ 634, 180, 28, 39 });
	jumpleftAnim.PushBack({ 606, 181, 28, 35 });
	jumpleftAnim.PushBack({ 576, 181, 28, 34 });
	jumpleftAnim.PushBack({ 547, 181, 28, 35 });
	jumpleftAnim.PushBack({ 518, 181, 28, 39 });
	jumpleftAnim.PushBack({ 488, 180, 28, 42 });
	jumpleftAnim.loop = true;
	jumpleftAnim.speed = 0.1f;

	// Jump Right
	jumprightAnim.PushBack({ 2, 177, 28, 46 });
	jumprightAnim.PushBack({ 30, 178, 28, 44 });
	jumprightAnim.PushBack({ 59, 179, 28, 42 });
	jumprightAnim.PushBack({ 88, 180, 28, 39 });
	jumprightAnim.PushBack({ 116, 181, 28, 35 });
	jumprightAnim.PushBack({ 146, 181, 28, 34 });
	jumprightAnim.PushBack({ 175, 181, 28, 35 });
	jumprightAnim.PushBack({ 204, 181, 28, 39 });
	jumprightAnim.PushBack({ 234, 180, 28, 42 });
	jumprightAnim.loop = true;
	jumprightAnim.speed = 0.1f;

	// Jump
	jumpAnim.PushBack({ 717, 0, 28, 39 });
	jumpAnim.PushBack({ 687, 0, 30, 39 });
	jumpAnim.PushBack({ 658, 0, 30, 39 });
	jumpAnim.loop = true;
	jumpAnim.speed = 0.1f;


	// Die left
	dieleftAnim.PushBack({ 472, 467, 28, 40 });
	dieleftAnim.PushBack({ 443, 471, 28, 36 });
	dieleftAnim.PushBack({ 408, 484, 33, 23 });
	dieleftAnim.PushBack({ 378, 484, 30, 23 });
	dieleftAnim.PushBack({ 471, 511, 32, 23 });
	dieleftAnim.PushBack({ 439, 510, 32, 23 });
	dieleftAnim.loop = true;
	dieleftAnim.speed = 0.1f;

	// Die Right
	dierightAnim.PushBack({ 250, 467, 28, 40 });
	dierightAnim.PushBack({ 279, 471, 28, 36 });
	dierightAnim.PushBack({ 309, 484, 33, 23 });
	dierightAnim.PushBack({ 340, 484, 30, 23 });
	dierightAnim.PushBack({ 247, 511, 32, 23 });
	dierightAnim.PushBack({ 279, 510, 32, 23 });
	jumprightAnim.loop = true;
	jumprightAnim.speed = 0.1f;

	// Die
	deadAnim.PushBack({ 717, 0, 31, 39 });
	deadAnim.PushBack({ 687, 0, 30, 39 });
	deadAnim.PushBack({ 658, 0, 30, 39 });
	deadAnim.loop = false;
	deadAnim.speed = 0.1f;

	// Throw Left
	throwleftAnim.PushBack({ 709, 245, 36, 37 });
	jumpleftAnim.PushBack({ 676, 244, 30, 38 });
	jumpleftAnim.PushBack({ 624, 246, 30, 36 });
	jumpleftAnim.PushBack({ 568, 246, 30, 36 });
	jumpleftAnim.PushBack({ 533, 245, 27, 37 });
	jumpleftAnim.loop = true;
	jumpleftAnim.speed = 0.1f;

	// Throw Right
	throwrightAnim.PushBack({ 5, 245, 36, 37 });
	throwrightAnim.PushBack({ 44, 244, 30, 38 });
	throwrightAnim.PushBack({ 96, 246, 30, 36 });
	throwrightAnim.PushBack({ 152, 246, 30, 36 });
	throwrightAnim.PushBack({ 190, 245, 27, 37 });
	throwrightAnim.loop = true;
	throwrightAnim.speed = 0.1f;


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
				//fx = -1.0f;
			}
			if (position.DistanceTo(App->player->position) > 5 && position.DistanceTo(App->player->position) < 500)
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
				//fx = 1.0f;
			}
			if (position.DistanceTo(App->player->position) > 5 && position.DistanceTo(App->player->position) < 500)
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
