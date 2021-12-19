#include "InteractiveObj.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"

InteractiveObject::InteractiveObject(int x, int y) : position(x, y)
{
	spawnPos = position;
}

InteractiveObject::~InteractiveObject()
{
	if (collider != nullptr)
		collider->pendingToDelete = true;
}

const Collider* InteractiveObject::GetCollider() const
{
	return collider;
}

void InteractiveObject::Update()
{
	if (currentAnim != nullptr)
		currentAnim->Update();

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);
}

void InteractiveObject::Draw()
{
	if (currentAnim != nullptr)
		App->render->Blit(texture, position.x, position.y, &(currentAnim->GetCurrentFrame()), 1.0f, true, angle, rotCenter.x, rotCenter.y);
}

void InteractiveObject::OnCollision(Collider* collider)
{
	//App->particles->AddParticle(App->particles->explosion, position.x, position.y);
	App->audio->PlayFx(destroyedFx);

	//SetToDelete();
}

void InteractiveObject::SetToDelete()
{
	pendingToDelete = true;
	if (collider != nullptr)
		collider->pendingToDelete = true;
}