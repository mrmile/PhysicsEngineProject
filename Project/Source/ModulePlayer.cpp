#include "ModulePlayer.h"

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
#include "ModulePhysics.h"

#include <stdio.h>
#include <time.h>

ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled)
{
	// idle left
	idleLeftAnim.PushBack({ 0, 167, 28, 33 });
	idleLeftAnim.PushBack({ 27, 167, 28, 33 });
	idleLeftAnim.PushBack({ 54, 167, 28, 33 });
	idleLeftAnim.PushBack({ 82, 167, 28, 33 });
	idleLeftAnim.PushBack({ 109, 167, 27, 33 });
	idleLeftAnim.PushBack({ 135, 167, 28, 33 });
	idleLeftAnim.PushBack({ 162, 167, 28, 33 });
	idleLeftAnim.PushBack({ 189, 167, 28, 33 });
	idleLeftAnim.loop = true;
	idleLeftAnim.speed = 0.15f;

	// idle left
	idleRightAnim.PushBack({ 190, 207, 28, 33 });
	idleRightAnim.PushBack({ 163, 207, 28, 33 });
	idleRightAnim.PushBack({ 136, 207, 28, 33 });
	idleRightAnim.PushBack({ 108, 207, 28, 33 });
	idleRightAnim.PushBack({ 82, 207, 27, 33 });
	idleRightAnim.PushBack({ 55, 207, 28, 33 });
	idleRightAnim.PushBack({ 28, 207, 28, 33 });
	idleRightAnim.PushBack({ 1, 207, 28, 33 });
	idleRightAnim.loop = true;
	idleRightAnim.speed = 0.15f;

	// move left
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
}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("Assets/player.png");
	currentAnimation = &idleRightAnim;

	laserFx = App->audio->LoadFx("Assets/Fx/laser.wav");
	explosionFx = App->audio->LoadFx("Assets/Fx/explosion.wav");

	position.x = 830;
	position.y = 180;

	destroyed = false;

	collider = App->collisions->AddCollider({ position.x + 6, position.y + 6, 19, 27 }, Collider::Type::PLAYER, this);

	// TODO 0: Notice how a font is loaded and the meaning of all its arguments 
	//char lookupTable[] = { "!  ,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz" };
	//scoreFont = App->fonts->Load("Assets/Fonts/rtype_font.png", "! @,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz", 1);

	// TODO 4: Try loading "rtype_font3.png" that has two rows to test if all calculations are correct
	char lookupTable[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };
	scoreFont = App->fonts->Load("Assets/Fonts/rtype_font3.png", lookupTable, 2);

	PlayerLookingPosition = 2;

	playerTimer = 0;
	playerIdleAnimationTimer = 0;

	x = 0.0f;
	y = 0.0f;
	vx = 0.0f;
	vy = 0.0f;
	ax = 0.0f; //
	ay = 0.0f; //
	Fx = 0.0f;
	Fy = 0.0f;
	dt = 0.0f; //


	mass = 0.0f;
	surface = 0.0f;
	cd = 0.0f;

	forceTimerX = 0.0f;

	//srand(time(NULL));

	return ret;
}

Update_Status ModulePlayer::Update()
{
	// Moving the player with the camera scroll
	//App->player->position.x += 1;

	playerTimer++;


	if (App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_REPEAT)
	{
		if (currentAnimation != &leftAnim)
		{
			leftAnim.Reset();
			currentAnimation = &leftAnim;
		}
		speed_F = 1;
		//position.x -= speed;
		//App->render->camera.x -= 3;

		/*
		if (speedX < 10) speedX = App->modulePhysics->ApplyForce(5.6f, playerMass, forceTimerX);
		position.x -= speedX;
		App->render->camera.x -= speedX * SCREEN_SIZE;
		*/
		//forceTimerX++;
		if (dt < 1)dt = dt + 0.016f;

		ax = -0.2f;

		PlayerLookingPosition = 1;
	}

	if (App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_REPEAT)
	{
		if (currentAnimation != &rightAnim)
		{
			rightAnim.Reset();
			currentAnimation = &rightAnim;
		}
		speed_F = 1;
		//position.x += speed;
		//App->render->camera.x += 3;

		/*
		if (speedX < 10) speedX = App->modulePhysics->ApplyForce(5.6f, playerMass, forceTimerX);
		position.x += speedX;
		App->render->camera.x += speedX * SCREEN_SIZE;
		*/
		//forceTimerX++;
		if (dt < 1.5f)dt = dt + 0.016f;

		ax = 0.2f;

		PlayerLookingPosition = 2;
	}

	if (App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_DOWN)
	{
		dt = 0.25;
		vx = 0;
	}
	if (App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_DOWN)
	{
		dt = 0.5;
		vx = 0;
	}
	

	// If no up/down movement detected, set the current animation back to idle
	if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_IDLE)
	{
		playerIdleAnimationTimer++;
		speed_F = 0;
		//vx = 0;
		//vy = 0;

		
		if (dt >= 0) dt = dt - 0.016f;
		if (dt <= 0)
		{
			dt = 0;
			vx = 0;
		}
		

		switch (PlayerLookingPosition)
		{
		case 1:
			if (currentAnimation != &idleLeftAnim)
			{
				idleLeftAnim.Reset();
				currentAnimation = &idleLeftAnim;
			}

			break;
		case 2:
			if (currentAnimation != &idleRightAnim)
			{
				idleRightAnim.Reset();
				currentAnimation = &idleRightAnim;
			}

			break;
		}
	}

	/*
	if ((PlayerLookingPosition == 1) && (position.x < App->render->camera.x / SCREEN_SIZE + 190))
	{
		App->render->camera.x -= 5;
	}
	if ((PlayerLookingPosition == 2) && (position.x > App->render->camera.x / SCREEN_SIZE + 140))
	{
		App->render->camera.x += 5;
	}
	*/

	/*
	if (App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_REPEAT)
	{

		if (App->render->camera.x / SCREEN_SIZE + App->render->camera.w + speed < 1242)
		{

			if (position.x + 70 > App->render->camera.x / SCREEN_SIZE + App->render->camera.w - horizontalMargin)
			{
				App->render->camera.x += speed + (SCREEN_SIZE - 1);
			}

		}

	}
	if (App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_REPEAT)
	{


		if (App->render->camera.x / SCREEN_SIZE - App->render->camera.w - speed < 1242)
		{

			if (position.x - 285 < App->render->camera.x / SCREEN_SIZE - App->render->camera.w + horizontalMargin)
			{
				App->render->camera.x -= speed + (SCREEN_SIZE - 1);
			}

		}
	}
	*/

	collider->SetPos(position.x + 6, position.y + 6);

	currentAnimation->Update();

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModulePlayer::PostUpdate()
{
	if (!destroyed)
	{
		
	}

	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	App->render->Blit(texture, position.x, position.y, &rect);

	// Draw UI (score) --------------------------------------
	//sprintf_s(scoreText, 10, "%7d", score);

	// TODO 3: Blit the text of the score in at the bottom of the screen
	//App->fonts->BlitText(58, 248, scoreFont, scoreText);

	//App->fonts->BlitText(150, 248, scoreFont, "this is just a font test message");

	return Update_Status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	// Example
	/*
	if (c1->type == Collider::Type::PLAYER_SHOT && c2->type == Collider::Type::ENEMY)
	{
		score += 23;
	}
	*/

	//Example
	if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::PLANT)
	{
		plantCollision = true;
	}
	else
	{
		plantCollision = false;
	}
}