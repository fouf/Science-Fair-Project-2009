#ifndef Game_H
#define Game_H
#include "State.h"
#include "Image.h"
#include "Player.h"
#include "Enemy.h"
#include "Menu.h"
#include "Map.h"
#include "GameOver.h"
#define Levels 5
class Game : public State
{
public:

	Game();
	Game(map<string, GameObject*>& Objects);
	~Game();
	void Process(map<string, GameObject*>& Objects, float DeltaTime);
	bool Event(SDL_Event& Event);
	void ScrollBackground(float DeltaTime);
	int CurrentLevel;
private:
	int Channel, Channel2;
	Mix_Chunk *BGMusic;
	bool InitiateWorld(); // Loads up the background, the ground Level will be a 2D array.
	bool RandomizeWorld(); // Creates a random world (holes, blocks, stairs, ect)
	void CreateEnemies(map<string, GameObject*>& Objects);
	void ProcessEnemies(float DeltaTime);
	Player* OurPlayer;	// The player 
	Enemy* Baddie[MaxEnemies];
	Map* Level;			// The Level
	Image* Background;
};

#endif