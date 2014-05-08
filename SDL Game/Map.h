#ifndef Map_H
#define Map_H
#include "Image.h"
#include "Font.h"
#include "Player.h"
#include <iostream>
#include <fstream>
using namespace std;

class Map : public GameObject
{
public:
	Map();
	~Map();

	void InitializeMap(const char* FileName); // Loads a map
	void TileDraw(SDL_Surface* Screen, int tile_number, int x, int y);
	void DrawMap(SDL_Surface* Screen);
	void Render(SDL_Surface* Screen);
	void Update(Player* GamePlayer, float DeltaTime);
	
	Map_Info map;
	
	Image* TopGround;
	Image* Ground;
	Image* Block;
	Image* Brick;
	Image* EmptyBlock;
	Image* FlagPole;
	Image* FlagPoleBottom;
	Image* FlagPoleTop;
	Font* LevelName;
private:

};

#endif