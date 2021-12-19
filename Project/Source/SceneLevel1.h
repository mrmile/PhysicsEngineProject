#ifndef __SCENE_LEVEL1_H__
#define __SCENE_LEVEL1_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class SceneLevel1 : public Module
{
public:
	//Constructor
	SceneLevel1(bool startEnabled);

	//Destructor
	~SceneLevel1();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	Update_Status Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	Update_Status PostUpdate() override;

	// Disables the player and the enemies
	bool CleanUp();

public:
	
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgTexture = nullptr;

	SDL_Texture* playerTurn = nullptr;
	SDL_Texture* enemyTurn = nullptr;

	SDL_Texture* youWin = nullptr;
	SDL_Texture* youloose = nullptr;

	SDL_Texture* level = nullptr;

	int bgTextureL1X = 0;
	int bgTextureL1X2 = 0;
	int bgTextureL1X3 = 0;

	int bgTextureL2X = 0;
	int bgTextureL2X2 = 0;
	int bgTextureL2X3 = 0;

	int bgTextureL3X = 0;
	int bgTextureL3X2 = 0;
	int bgTextureL3X3 = 0;

	int bgTextureL4X = 0;
	int bgTextureL4X2 = 0;
	int bgTextureL4X3 = 0;

	int TURN = 0;
	int turnDelay;
};

#endif