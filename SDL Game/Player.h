#ifndef Player_H
#define Player_H
#include "GameObject.h"
#include "Font.h"
#define StartingLives 3

#define JumpForce	200
#define JumpSpeed	50
#define MaxJumpVel	550
#define MaxFallSpeed 350

#define MaxRunSpeed 400
#define RunSpeed	200

#define GravityMultiplier 3

#define PLAYER_STANDLEFT -1
#define PLAYER_STANDRIGHT 0
#define PLAYER_LEFT 1
#define PLAYER_RIGHT 2
#define PLAYER_JUMPLEFT 3
#define PLAYER_JUMPRIGHT 4
#define PLAYER_CROUCHRIGHT 5
#define PLAYER_CROUCHLEFT 6
using namespace std;
class Player : public GameObject
{
public:
	Player();
	Player(std::string SpriteSheet, int x, int y, Map_Info* CurrentLevel); // Sprite sheet.
	~Player();
	bool HandleEvents(SDL_Event& Event);
	void Render(SDL_Surface* Screen);
	bool Process(float DeltaTime);
	void ManageAnimation(float DeltaTime);
	PlayerState CurrentState;
	SDL_Rect ClipsWalkingRight[3];
	SDL_Rect ClipsWalkingLeft[3];

	SDL_Rect ClipsStandingRight;
	SDL_Rect ClipsStandingLeft;

	SDL_Rect ClipsJumpingRight;
	SDL_Rect ClipsJumpingLeft;

	SDL_Rect ClipsCrouchingRight;
	SDL_Rect ClipsCrouchingLeft;
	unsigned int Frame;
	int Status, Lives;
	float xVel, yVel;

private:
	int Channel;
	Mix_Chunk *BGMusic;

	void UpdatePosition(float DeltaTime);
	void UpdateVelocity(float DeltaTime);
	bool CheckCollisions(float DeltaTime);
	int Score, Coins;
	bool InAir, Accelerate, LeftDown, RightDown, JumpBoost, Direction, Crouch;
	Map_Info* Level;
	Font* TextScore;
	Font* TextCoins;
	Font* TextLives;

};
#endif