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
}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	/*aimingPower = 0;
	aimingAngle = 0;
	aimingPoint = 0;*/

	texture = App->textures->Load("Assets/RedCharacter.png");
	currentAnimation = &idleRightAnim;

	shoot = App->audio->LoadFx("Assets/shoot.wav");
	hit = App->audio->LoadFx("Assets/hit.wav");
	dead = App->audio->LoadFx("Assets/dead.wav");
	explosionFx = App->audio->LoadFx("Assets/explosion.wav");
	winMusicFx = App->audio->LoadFx("Assets/win.wav");
	looseMusicFx = App->audio->LoadFx("Assets/loose.wav");

	position.x = 0;
	position.y = 0;

	destroyed = false;

	collider = App->collisions->AddCollider({ position.x + 10, position.y + 6, 16, 30 }, Collider::Type::PLAYER, this);

	// TODO 0: Notice how a font is loaded and the meaning of all its arguments 
	//char lookupTable[] = { "!  ,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz" };
	//scoreFont = App->fonts->Load("Assets/Fonts/rtype_font.png", "! @,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz", 1);

	// TODO 4: Try loading "rtype_font3.png" that has two rows to test if all calculations are correct
	char lookupTable[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };
	scoreFont = App->fonts->Load("Assets/rtype_font3.png", lookupTable, 2);

	PlayerLookingPosition = 2;

	playerTimer = 0;
	playerIdleAnimationTimer = 0;

	x = 0.0f;
	y = 0.0f;
	vx = 0.0f;
	vy = 0.0f;
	ax = 0.0f; //
	ay = 0.0f; //
	fx = 0.0f;
	fy = 0.0f;
	dt = 0.0f; //


	mass = 10.0f;
	surface = 2.0f;
	cd = 0.4f;
	cl = 1.2f;

	forceTimerX = 0.0f;

	playerHP = 100;
	playerFPS = 0;

	//srand(time(NULL));

	return ret;
}

Update_Status ModulePlayer::Update()
{
	// Moving the player with the camera scroll
	//App->player->position.x += 1;

	playerTimer++;
	playerFPS++;

	/*GetCursorPos(cursorPosition);*/

	collider->SetPos(position.x + 10, position.y + 6);
	if (App->input->keys[SDL_SCANCODE_F2] == Key_State::KEY_DOWN) App->sceneLevel_1->TURN = 1;
	if (App->input->keys[SDL_SCANCODE_F3] == Key_State::KEY_DOWN) App->sceneLevel_1->TURN = 2;

	if (App->sceneLevel_1->TURN == 1 && destroyed == false)
	{
		if (App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_REPEAT)
		{
			if (position.y >= 227)
			{
				if (currentAnimation != &leftAnim)
				{
					leftAnim.Reset();
					currentAnimation = &leftAnim;
				}
			}
			if (position.y < 227)
			{
				if (currentAnimation != &jumpleftAnim)
				{
					jumpleftAnim.Reset();
					currentAnimation = &jumpleftAnim;
				}
			}
			speed_F = 1;
			//position.x--;
			App->player->fx = -1.0f;

			PlayerLookingPosition = 1;
		}
		//else if (App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_UP)App->player->fx = 0.0f;

		if (App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_REPEAT)
		{
			
			if (position.y >= 227)
			{
				if (currentAnimation != &rightAnim)
				{
					rightAnim.Reset();
					currentAnimation = &rightAnim;
				}
			}
			if (position.y < 227)
			{
				if (currentAnimation != &jumprightAnim)
				{
					jumprightAnim.Reset();
					currentAnimation = &jumprightAnim;
				}
			}
			speed_F = 1;
			//position.x++;
			App->player->fx = 1.0f;

			PlayerLookingPosition = 2;
		}
		//else if (App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_UP)App->player->fx = 0.0f;

		if (App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_REPEAT && position.y >= 227)
		{
			if (App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_IDLE
				&& App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_IDLE)
			{
				//App->player->fx = 0.0f;
				ax = 0;
				//vx = 0;
				//if (fx == 0) vx = 0;
			}

			if (PlayerLookingPosition == 1)
			{
				if (currentAnimation != &jumpleftAnim)
				{
					jumpleftAnim.Reset();
					currentAnimation = &jumpleftAnim;
				}
			}
			if (PlayerLookingPosition == 2)
			{
				if (currentAnimation != &jumprightAnim)
				{
					jumprightAnim.Reset();
					currentAnimation = &jumprightAnim;
				}
			}
			speed_F = 1;
			//position.x++;
			App->player->fy = -1.2f;

		}
		//else if (App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_UP)App->player->fy = 0.0f;

		if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
		{
			App->audio->PlayFx(shoot);
			if (PlayerLookingPosition == 1)
			{
				

				/*aimingPower = sqrt(pow(position.x - cursorPosition->x, 2) + pow(position.y - cursorPosition->y, 2));
				aimingAngle = asin((position.y - cursorPosition->y) / aimingPower) * 180/3.14;
				aimingPoint = cursorPosition->x + cursorPosition->y;*/

				App->particles->AddParticle(App->particles->shootLeftPlayer, position.x + 10, position.y, Collider::Type::PLAYER_SHOT);
			}


			if (PlayerLookingPosition == 2) App->particles->AddParticle(App->particles->shootRightPlayer, position.x + 10, position.y, Collider::Type::PLAYER_SHOT);
		}

		// If no up/down movement detected, set the current animation back to idle
		if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_IDLE
			&& App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_IDLE
			&& App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_IDLE
			&& App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_IDLE)
		{
			playerIdleAnimationTimer++;
			speed_F = 0;
			App->player->fx = 0.0f;

			switch (PlayerLookingPosition)
			{
			case 1:
				if (currentAnimation != &idleRightAnim)
				{
					idleRightAnim.Reset();
					currentAnimation = &idleRightAnim;
				}

				break;
			case 2:
				if (currentAnimation != &idleLeftAnim)
				{
					idleLeftAnim.Reset();
					currentAnimation = &idleLeftAnim;
				}

				break;
			}
		}

		if (App->input->keys[SDL_SCANCODE_LSHIFT] == Key_State::KEY_DOWN)
		{
			
			if (throwCounter < 10)
			{
				throwCounter++;
			}
		}

		if (App->input->keys[SDL_SCANCODE_LCTRL] == Key_State::KEY_DOWN)
		{
			if (throwCounter > 0)
			{
				throwCounter--;
			}	
		}

		if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
		{
			App->sceneLevel_1->TURN = 2;
		}

		/*
		if (vx < 0 && position.y >= 227 && App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_IDLE)
		{
			//App->player->vx = 0.0;
			//App->player->ax = 0.0;
			if (vx != 0)App->player->fx = 1.0f;
			if (vx == 0)App->player->fx = 0.0;
		}
		if (App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_IDLE && vx > 0 && position.y >= 227)
		{
			//App->player->vx = 0.0;
			//App->player->ax = 0.0;
			if (vx != 0)App->player->fx = -1.0f;
			if (vx == 0)App->player->fx = 0.0;
		}
		if (App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_IDLE
			&& App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_IDLE)
		{
			App->player->fx = 0.0;
		}
		*/
		// Ff = c*m*g;
		/*
		if (PlayerLookingPosition == 1 && position.y >= 227)
		{
			//App->player->vx = 0.0;
			//App->player->ax = 0.0;
			if (vx != 0)App->player->fx = 1.0f;
			if (vx == 0)App->player->fx = 0.0;
		}
		if (PlayerLookingPosition == 2 && position.y >= 227)
		{
			//App->player->vx = 0.0;
			//App->player->ax = 0.0;
			if (vx != 0)App->player->fx = -1.0f;
			if (vx == 0)App->player->fx = 0.0;
		}
		*/

		//if (vx == 0 && position.y >= 227) App->player->fx = 0.0;
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

		currentAnimation->Update();
		App->sceneLevel_1->turnDelay = 0;

		//return Update_Status::UPDATE_CONTINUE;
	}
	else
	{
		App->sceneLevel_1->turnDelay++;
		speed_F = 0;
		App->player->fx = 0.0f;
		//currentAnimation = &idleLeftAnim;
	}

	if (App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_IDLE)
	{
		if (vx < 0)
		{
			fx = App->modulePhysics->DragForceLeft(vx);
		}
		if (vx > 0)
		{
			fx = App->modulePhysics->DragForceRight(vx);
		}
	}
	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModulePlayer::PostUpdate()
{
	if (!destroyed)
	{
		
	}

	if (position.y >= 228) position.y = 228;

	if (position.x >= 365) position.x = 365;
	if (position.x <= -15) position.x = -15;

	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	App->render->Blit(texture, position.x + 5, position.y, &rect);

	SDL_Rect quad;
	quad = { 5, 10, playerHP, 10 };

	SDL_Rect quad2;
	quad2 = { 5, 10, 100, 10 };

	SDL_Rect bgquad;
	bgquad = { 3, 8, 104, 14 };
	App->render->DrawQuad(bgquad, 165, 0, 0, 255, 0.0f, true);
	App->render->DrawQuad(quad2, 200, 200, 200, 255, 0.0f, true);
	//app->render->DrawRectangle(bgquad, 255, 255, 255, 165, true, true);
	if (playerHP >= 100)
	{
		playerHP = 100;
		App->render->DrawQuad(quad, 0, 255, 0, 255, 0.0f, true);
	}
	else if (playerHP > 50)
	{
		App->render->DrawQuad(quad, 120, 255, 0, 255, 0.0f, true);
	}
	else if (playerHP > 20 && playerHP <= 50)
	{
		App->render->DrawQuad(quad, 255, 255, 0, 255, 0.0f, true);
	}
	else
	{
		if ((playerFPS / 5) % 2 == 0)
		{
			App->render->DrawQuad(quad, 255, 0, 0, 255, 0.0f, true);
		}
		else
		{
			App->render->DrawQuad(quad, 255, 150, 0, 255, 0.0f, true);
		}

	}

	if(destroyed == true) App->sceneLevel_1->destroyedDelay++;

	// Draw UI (score) --------------------------------------
	sprintf_s(scoreText, 10, "%7d", throwCounter *30);

	// TODO 3: Blit the text of the score in at the bottom of the screen
	App->fonts->BlitText(-30, 40, scoreFont, scoreText);

	//App->fonts->BlitText(0, 0, scoreFont, "this is just a font test message");

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

	if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::WALL)
	{
		position.y = 227;

		if (App->input->keys[SDL_SCANCODE_UP] != Key_State::KEY_DOWN)
		{
			App->player->vy = 0.0;
			App->player->ay = 0.0;
			App->player->fy = 0.0;
		}

		App->player->touchingGround = true;
	}
	else
	{
		App->player->touchingGround = false;
	}

	if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::ENEMY_SHOT)
	{
		playerHP -= 15;
		if (playerHP < 0) playerHP = 0;
		
		if (playerHP != 0) App->audio->PlayFx(hit);

		if (playerHP <= 0)
		{
			//invincibleDelay = 121;
			playerHP = 0;
			//App->audio->PlayFx(dead);
			App->audio->PlayFx(App->player->looseMusicFx);
			App->render->Blit(App->sceneLevel_1->youloose, 100, 50, NULL);
			destroyed = true;
			if (currentAnimation != &deadAnim)
			{
				deadAnim.Reset();
				currentAnimation = &deadAnim;
			}
		}
		else
		{
			destroyed = false;
			App->sceneLevel_1->destroyedDelay = 0;
		}
	}
}