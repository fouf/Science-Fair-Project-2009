#ifndef Util_H
#define Util_H


#define FIMAGE_INIT 1 << 0
#define FAUDIO_INIT 1 << 1
#define FTTF_INIT 1 << 2
#define FMIXER_INIT 1 << 3
#pragma comment(lib, "SDLmain.lib")
#pragma comment(lib, "SDL.lib")
#pragma comment(lib, "SDL_image.lib")
#pragma comment(lib, "SDL_ttf.lib")
#pragma comment(lib, "SDL_mixer.lib")

#include "SDL_main.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <map>

#define GAME_NAME "SDL Platformer"
#define LOG_FILE "LogFile.txt"
#define WIDTH 800
#define HEIGHT 608

#define Tile_Height 32
#define Tile_Width 32
#define TilesHorizantal WIDTH / Tile_Width
#define TilesVertical HEIGHT / Tile_Height

#define MaxEnemies 15

struct Map_Info
{
	int sX, sY, maxX, maxY;
	unsigned int Tile[500][TilesVertical];
};
enum Tiles{
	TILE_TYPE_EMPTY = 0,
	TILE_TYPE_GROUND = 1,
	TILE_TYPE_TOPGROUND = 2,
	TILE_TYPE_BRICK = 3,
	TILE_TYPE_BLOCK = 4,
	TILE_TYPE_BRICKBLOCK = 5,
	TILE_TYPE_EMPTYBLOCK = 6,
	TILE_TYPE_FLAG = 7,
	TILE_TYPE_FLAGBOTTOM = 8,
	TILE_TYPE_FLAGTOP = 9
};

enum Collision{
	COLLISION_TOP = 0,
	COLLISION_LEFT = 1,
	COLLISION_RIGHT = 2,
	COLLISION_BOTTOM = 3,
	COLLISION_NONE = 4,
	COLLISION_SIDE = 5
};

#define Player_Width 16
#define Player_Height 28

enum PlayerState {Alive, Dead};

void Log(std::string LogMessage);
static std::ofstream filelog;
#endif