#ifndef __MODULE_PLAYER_H__
#define __MODULE_PLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;

class ModulePlayer : public Module
{
public:
	// Constructor
	ModulePlayer(bool startEnabled);

	// Destructor
	~ModulePlayer();

	// Called when the module is activated
	// Loads the necessary textures for the player
	bool Start() override;

	// Called at the middle of the application loop
	// Processes new input and handles player movement
	Update_Status Update() override;

	// Called at the end of the application loop
	// Performs the render call of the player sprite
	Update_Status PostUpdate() override;

	// Collision callback, called when the player intersects with another collider
	void OnCollision(Collider* c1, Collider* c2) override;

public:
	// Position of the player in the map
	iPoint position;

	// The speed in which we move the player (pixels per frame)
	int speed_F = 1;

	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* texture = nullptr;
	
	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentAnimation = nullptr;

	// A set of animations
	Animation idleRightAnim;
	Animation idleLeftAnim;

	Animation rightAnim;
	Animation leftAnim;

	Animation jumpAnim;
	Animation jumpleftAnim;
	Animation jumprightAnim;

	Animation dieleftAnim;
	Animation dierightAnim;
	Animation deadAnim;

	Animation throwleftAnim;
	Animation throwrightAnim;

	// The player's collider
	Collider* collider = nullptr;

	// A flag to detect when the player has been destroyed
	bool destroyed = false;

	// Sound effects indices
	uint shoot = 0;
	uint hit = 0;
	uint dead = 0;
	uint explosionFx = 0;
	uint winMusicFx = 0;
	uint looseMusicFx = 0;

	// Font score index
	uint score = 10;
	int scoreFont = -1;
	char scoreText[10] = { "\0" };

	int PlayerLookingPosition;

	int playerTimer;
	int playerIdleAnimationTimer;

	//Margin of movement
	int horizontalMargin = 45;

	//Collision bools
	bool plantCollision;

	float dt;

	double x;
	double y;

	// Velocity
	double vx;
	double vy;

	// Acceleration
	double ax;
	double ay;

	// Force (total) applied to the ball
	double fx;
	double fy;

	//friction force on x axis
	double ffx = 0;

	// Mass
	double mass;

	// Aerodynamics stuff
	double surface; // Effective wet surface
	double cl; // Lift coefficient
	double cd; // Drag coefficient

	// Has physics enabled?
	bool physics_enabled = true;

	bool touchingGround = false;

	int playerHP;
	int playerFPS;

	float forceTimerX;

	int throwCounter;

	/*float aimingPower;
	float aimingAngle;
	float aimingPoint;
	LPPOINT cursorPosition;*/

};

#endif //!__MODULE_PLAYER_H__