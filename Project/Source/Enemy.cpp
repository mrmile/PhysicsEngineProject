#include "Enemy.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "SceneLevel1.h"
#include "ModulePlayer.h"

Enemy::Enemy(int x, int y) : position(x, y)
{
	spawnPos = position;
}

Enemy::~Enemy()
{
	if (collider != nullptr)
		collider->pendingToDelete = true;
}

const Collider* Enemy::GetCollider() const
{
	return collider;
}

void Enemy::Update()
{
	if (currentAnim != nullptr)
		currentAnim->Update();

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);
}

void Enemy::Draw()
{
	if (currentAnim != nullptr)
		App->render->Blit(texture, position.x, position.y, &(currentAnim->GetCurrentFrame()));

	SDL_Rect Equad;
	Equad = { 280, 10, EnemyHp, 10 };

	SDL_Rect Equad2;
	Equad2 = { 280, 10, 100, 10 };

	SDL_Rect Ebgquad;
	Ebgquad = { 278, 8, 104, 14 };
	App->render->DrawQuad(Ebgquad, 0, 0, 165, 255, 0.0f, true);
	App->render->DrawQuad(Equad2, 200, 200, 200, 255, 0.0f, true);
	//app->render->DrawRectangle(bgquad, 255, 255, 255, 165, true, true);
	if (EnemyHp >= 100)
	{
		EnemyHp = 100;
		App->render->DrawQuad(Equad, 0, 255, 0, 255, 0.0f, true);
	}
	else if (EnemyHp > 50)
	{
		App->render->DrawQuad(Equad, 120, 255, 0, 255, 0.0f, true);
	}
	else if (EnemyHp > 20 && EnemyHp <= 50)
	{
		App->render->DrawQuad(Equad, 255, 255, 0, 255, 0.0f, true);
	}
	else
	{
		if ((enemy1FPS / 5) % 2 == 0)
		{
			App->render->DrawQuad(Equad, 255, 0, 0, 255, 0.0f, true);
		}
		else
		{
			App->render->DrawQuad(Equad, 255, 150, 0, 255, 0.0f, true);
		}

	}
}

void Enemy::OnCollision(Collider* collider)
{
	if (collider->type == Collider::Type::PLAYER_SHOT)
	{
		EnemyHp -= 10;
		if (EnemyHp < 0) EnemyHp = 0;

		//if (enemyHP != 0) app->audio->PlayFx(damaged);

		if (EnemyHp <= 0)
		{
			App->particles->AddParticle(App->particles->explosion, position.x, position.y);
			//invincibleDelay = 121;
			EnemyHp = 0;
			App->audio->PlayFx(App->player->winMusicFx);
			destroyed = true;

			App->render->Blit(App->sceneLevel_1->youWin, 100, 50, NULL);
			App->sceneLevel_1->destroyedDelay++;

		}
		else
		{
			destroyed = false;
			App->sceneLevel_1->destroyedDelay = 0;
		}
	}
	if (collider->type == Collider::Type::WALL)
	{
		position.y = 227;
		
			
		vy = 0.0;
		ay = 0.0;
		fy = 0.0;

		touchingGround = true;
	}
	
}

void Enemy::SetToDelete()
{
	pendingToDelete = true;
	if (collider != nullptr)
		collider->pendingToDelete = true;
}