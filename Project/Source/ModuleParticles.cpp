#include "ModuleParticles.h"

#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		particles[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{

}

bool ModuleParticles::Start()
{
	LOG("Loading particles");
	texture = App->textures->Load("Assets/Sprites/particles.png");

	// Particle Examples
	explosionRed.anim.PushBack({274, 296, 33, 30});
	explosionRed.anim.PushBack({313, 296, 33, 30});
	explosionRed.anim.PushBack({346, 296, 33, 30});
	explosionRed.anim.PushBack({382, 296, 33, 30});
	explosionRed.anim.PushBack({419, 296, 33, 30});
	explosionRed.anim.PushBack({457, 296, 33, 30});
	explosionRed.anim.loop = false;
	explosionRed.anim.speed = 0.3f;

	explosionBlue.anim.PushBack({ 274, 296, 33, 30 });
	explosionBlue.anim.PushBack({ 313, 296, 33, 30 });
	explosionBlue.anim.PushBack({ 346, 296, 33, 30 });
	explosionBlue.anim.PushBack({ 382, 296, 33, 30 });
	explosionBlue.anim.PushBack({ 419, 296, 33, 30 });
	explosionBlue.anim.PushBack({ 457, 296, 33, 30 });
	explosionBlue.anim.loop = false;
	explosionBlue.anim.speed = 0.3f;

	shootLeft.anim.PushBack({ 232, 103, 16, 12 });
	shootLeft.anim.PushBack({ 249, 103, 16, 12 });
	shootLeft.speed.x = -3;
	shootLeft.anim.loop = true;
	shootLeft.anim.speed = 0.2f;

	shootRight.anim.PushBack({ 232, 103, 16, 12 });
	shootRight.anim.PushBack({ 249, 103, 16, 12 });
	shootRight.speed.x = 3;
	shootRight.anim.loop = true;
	shootRight.anim.speed = 0.2f;

	return true;
}

Update_Status ModuleParticles::PreUpdate()
{
	// Remove all particles scheduled for deletion
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (particles[i] != nullptr && particles[i]->pendingToDelete)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");

	// Delete all remaining active particles on application exit 
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(particles[i] != nullptr)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}

	return true;
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		
		if (particles[i] != nullptr && particles[i]->collider == c1)
		{
			if(c1->type == Collider::Type::PLAYER_SHOT) App->particles->AddParticle(App->particles->explosionRed, particles[i]->position.x + 20, particles[i]->position.y + 40, Collider::Type::NONE);
			if (c1->type == Collider::Type::ENEMY_SHOT) App->particles->AddParticle(App->particles->explosionBlue, particles[i]->position.x + 20, particles[i]->position.y + 40, Collider::Type::NONE);
			App->audio->PlayFx(App->player->explosionFx);
			particles[i]->pendingToDelete = true;
			particles[i]->collider->pendingToDelete = true;
			break;
		}
		
		
	}
}

Update_Status ModuleParticles::Update()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if(particle == nullptr)	continue;

		// Call particle Update. If it has reached its lifetime, destroy it
		if(particle->Update() == false)
		{
			particles[i]->SetToDelete();
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleParticles::PostUpdate()
{
	//Iterating all particle array and drawing any active particles
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if (particle != nullptr && particle->isAlive)
		{
			App->render->Blit(texture, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Particle* ModuleParticles::AddParticle(const Particle& particle, int x, int y, Collider::Type colliderType, uint delay)
{
	Particle* newParticle = nullptr;

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		//Finding an empty slot for a new particle
		if (particles[i] == nullptr)
		{
			newParticle = new Particle(particle);
			newParticle->frameCount = -(int)delay;			// We start the frameCount as the negative delay
			newParticle->position.x = x;						// so when frameCount reaches 0 the particle will be activated
			newParticle->position.y = y;

			//Adding the particle's collider
			if (colliderType != Collider::Type::NONE)
				newParticle->collider = App->collisions->AddCollider(newParticle->anim.GetCurrentFrame(), colliderType, this);

			particles[i] = newParticle;
			break;
		}
	}

	return newParticle;
}