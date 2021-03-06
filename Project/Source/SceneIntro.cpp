#include "SceneIntro.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"

SceneIntro::SceneIntro(bool startEnabled) : Module(startEnabled)
{

}

SceneIntro::~SceneIntro()
{

}

// Load assets
bool SceneIntro::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Background.png");
	startButton = App->textures->Load("Assets/startButton3.png");
	title = App->textures->Load("Assets/title.png");

	startFx = App->audio->LoadFx("Assets/bonus.wav");


	//App->audio->PlayMusic("Assets/Music/introTitle.ogg", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	delay = 0;

	return ret;
}

Update_Status SceneIntro::Update()
{
	if (App->input->keys[SDL_SCANCODE_RETURN] == Key_State::KEY_DOWN)
	{
		App->audio->PlayFx(startFx);
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 90);
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneIntro::PostUpdate()
{
	delay++;
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	App->render->Blit(title, 25, 0, NULL);

	if ((delay / 30) % 2 == 0)
	{
		App->render->Blit(startButton, 65, 150, NULL, 1.0f);
	}

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneIntro::CleanUp()
{
	App->textures->Unload(bgTexture);
	App->textures->Unload(startButton);

	return true;
}