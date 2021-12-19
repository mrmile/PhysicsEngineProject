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
	texture = App->textures->Load("Assets/RedCharacter_MIXED.png"); // mirar el spritesheet en el que pone MIXED

	// Particle Examples

	// unfinished
	explosionRed.anim.PushBack({2, 287, 43, 90});
	explosionRed.anim.PushBack({45, 287, 54, 90 });
	explosionRed.anim.PushBack({99, 287, 52, 90 });
	explosionRed.anim.PushBack({151, 287, 54, 90 });
	explosionRed.anim.PushBack({205, 287, 54, 90 });
	explosionRed.anim.PushBack({259, 287, 52, 90 });
	explosionRed.anim.PushBack({311, 287, 54, 90 });
	explosionRed.anim.PushBack({ 701, 380, 54, 90 });
	explosionRed.anim.PushBack({ 388, 380, 54, 90 });
	explosionRed.anim.PushBack({ 388, 380, 54, 90 });
	explosionRed.anim.PushBack({ 388, 380, 54, 90 });
	explosionRed.anim.PushBack({ 388, 380, 54, 90 });
	explosionRed.anim.PushBack({ 388, 380, 54, 90 });
	explosionRed.anim.PushBack({ 388, 380, 54, 90 });
	explosionRed.anim.PushBack({ 388, 380, 54, 90 });
	explosionRed.anim.PushBack({ 388, 380, 54, 90 });
	explosionRed.anim.PushBack({ 388, 290, 54, 90 });
	explosionRed.anim.PushBack({ 388, 290, 54, 90 });
	explosionRed.anim.PushBack({ 388, 290, 54, 90 });
	explosionRed.anim.PushBack({ 388, 290, 54, 90 });
	explosionRed.anim.loop = false;
	explosionRed.anim.speed = 0.3f;
	explosionRed.lifetime = 25;

	// finished
	explosionBlue.anim.PushBack({ 704, 286, 48, 90 });
	explosionBlue.anim.PushBack({ 656, 286, 54, 90 });
	explosionBlue.anim.PushBack({ 601, 286, 52, 90 });
	explosionBlue.anim.PushBack({ 547, 286, 54, 90 });
	explosionBlue.anim.PushBack({ 494, 286, 54, 90 });
	explosionBlue.anim.PushBack({ 440, 286, 52, 90 });
	explosionBlue.anim.PushBack({ 388, 290, 54, 90 });
	explosionBlue.anim.PushBack({ 701, 380, 54, 90 });
	// unfinished
	explosionBlue.anim.PushBack({ 388, 380, 54, 90 });
	explosionBlue.anim.PushBack({ 388, 380, 54, 90 });
	explosionBlue.anim.PushBack({ 388, 380, 54, 90 });
	explosionBlue.anim.PushBack({ 388, 380, 54, 90 });
	explosionBlue.anim.PushBack({ 388, 380, 54, 90 });
	explosionBlue.anim.PushBack({ 388, 380, 54, 90 });
	explosionBlue.anim.PushBack({ 388, 380, 54, 90 });
	explosionBlue.anim.PushBack({ 388, 380, 54, 90 });
	explosionBlue.anim.PushBack({ 388, 290, 54, 90 });
	explosionBlue.anim.PushBack({ 388, 290, 54, 90 });
	explosionBlue.anim.PushBack({ 388, 290, 54, 90 });
	explosionBlue.anim.PushBack({ 388, 290, 54, 90 });
	explosionBlue.anim.loop = false;
	explosionBlue.anim.speed = 0.3f;
	explosionBlue.lifetime = 25;

	shootLeft.anim.PushBack({ 527, 225, 20, 18 });
	shootLeft.speed.x = -3;
	shootLeft.anim.loop = true;
	shootLeft.anim.speed = 0.2f;

	shootRight.anim.PushBack({ 527, 225, 20, 18 });
	shootRight.speed.x = 3;
	shootRight.anim.loop = true;
	shootRight.anim.speed = 0.2f;

	shootLeftPlayer.anim.PushBack({ 136, 230, 20, 18 });
	shootLeftPlayer.speed.x = -3;
	shootLeftPlayer.anim.loop = true;
	shootLeftPlayer.anim.speed = 0.2f;

	shootRightPlayer.anim.PushBack({ 136, 230, 20, 18 });
	shootRightPlayer.speed.x = 3;
	shootRightPlayer.anim.loop = true;
	shootRightPlayer.anim.speed = 0.2f;

	

	

	
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
		
		if (particles[i] != nullptr && c1->type != Collider::Type::EXPLOSION)
		{
			if(c1->type == Collider::Type::PLAYER_SHOT) App->particles->AddParticle(App->particles->explosionRed, particles[i]->position.x , particles[i]->position.y-80 , Collider::Type::EXPLOSION);
			if (c1->type == Collider::Type::ENEMY_SHOT) App->particles->AddParticle(App->particles->explosionBlue, particles[i]->position.x , particles[i]->position.y-80, Collider::Type::EXPLOSION);
			particles[i]->pendingToDelete = true;
			particles[i]->collider->pendingToDelete = true;
			break;
		}
		if (particles[i] != nullptr &&  c1->type == Collider::Type::EXPLOSION)
		{
			App->audio->PlayFx(App->player->explosionFx);
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