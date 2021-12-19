#include "Enemy_BrownShip.h"

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

Enemy_BrownShip::Enemy_BrownShip(int x, int y) : Enemy(x, y)
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
	idleRightAnim.PushBack({ 717, 0, 31, 39 });
	idleRightAnim.PushBack({ 687, 0, 30, 39 });
	idleRightAnim.PushBack({ 658, 0, 30, 39 });
	idleRightAnim.loop = true;
	idleRightAnim.speed = 0.1f;

	// Move left
	leftAnim.PushBack({ 1, 7, 28, 33 });
	leftAnim.PushBack({ 28, 7, 28, 33 });
	leftAnim.PushBack({ 55, 7, 28, 33 });
	leftAnim.PushBack({ 82, 7, 28, 33 });
	leftAnim.PushBack({ 109, 7, 28, 33 });
	leftAnim.PushBack({ 136, 7, 28, 33 });
	leftAnim.PushBack({ 163, 7, 28, 33 });
	leftAnim.PushBack({ 190, 7, 28, 33 });
	leftAnim.PushBack({ 217, 7, 28, 33 });
	leftAnim.PushBack({ 244, 7, 28, 33 });
	leftAnim.loop = true;
	leftAnim.speed = 0.3f;

	// Move right
	rightAnim.PushBack({ 244, 47, 28, 33 });
	rightAnim.PushBack({ 217, 47, 28, 33 });
	rightAnim.PushBack({ 190, 47, 28, 33 });
	rightAnim.PushBack({ 163, 47, 28, 33 });
	rightAnim.PushBack({ 136, 47, 28, 33 });
	rightAnim.PushBack({ 109, 47, 28, 33 });
	rightAnim.PushBack({ 82, 47, 28, 33 });
	rightAnim.PushBack({ 55, 47, 28, 33 });
	rightAnim.PushBack({ 28, 47, 28, 33 });
	rightAnim.PushBack({ 1, 47, 28, 33 });
	rightAnim.loop = true;
	rightAnim.speed = 0.3f;

	// jump
	jumpAnim.PushBack({ 717, 0, 31, 39 });
	jumpAnim.PushBack({ 687, 0, 30, 39 });
	jumpAnim.PushBack({ 658, 0, 30, 39 });
	jumpAnim.loop = true;
	jumpAnim.speed = 0.1f;

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

void Enemy_BrownShip::Update()
{
	Enemy_Counter++;
	enemy1FPS++;
	collider->SetPos(position.x+10, position.y+6);
	currentAnim = &idleRightAnim;
	if (App->sceneLevel_1->TURN == 2)
	{
		//ADD TURN THINGS HERE
	}
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	if (EnemyHp == 0)
	{
		SetToDelete();
	}

	Enemy::Update();
}
