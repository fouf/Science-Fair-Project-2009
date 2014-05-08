#ifndef Enemy_H
#define Enemy_H
#include "GameObject.h"


class Enemy : public GameObject
{
public:
	Enemy();
	Enemy(std::string SpriteSheet, int x, int y, Map_Info* CurrentLevel); // Sprite sheet.
	~Enemy();
	//void UpdateVelocity(float DeltaTime);
	void Process(float DeltaTime);
	void Render(SDL_Surface* Screen);
	float xVel, yVel;

private:

	void UpdatePosition(float DeltaTime);
	void CheckCollisions(float DeltaTime);
	Map_Info* Level;


};
#endif