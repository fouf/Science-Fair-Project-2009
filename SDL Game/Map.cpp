#include "Map.h"
Map::Map()
{

}

Map::~Map()
{
	delete TopGround;
	delete Ground;
	delete Block;
	delete Brick;
	delete EmptyBlock;
	delete FlagPole;
	delete FlagPoleBottom;
	delete FlagPoleTop;
}
void Map::InitializeMap(const char* FileName)
{
	int tilenumber = 0, y = 0;
	unsigned int i = 0;
	ifstream MapFile(FileName);
	if(!MapFile.is_open())
	{
		Log(std::string("Failed to open ") + FileName);
	}
	string line = "";
	getline(MapFile, line, '\n');
	for(unsigned int j = 0; j < line.length(); j++)
	{
		for(int l = 0; l < TilesVertical; l++)
		{
			map.Tile[j][l] = 0;
		}
	}
	if(MapFile.good())
	{
		while(getline(MapFile, line, '\n') && y < TilesVertical)
		{
			printf("%s\n", line);
			if(line.length() > 0)
			{
				map.maxX = line.length() * Tile_Width;
			}
			for(i = 0; i < line.length(); i++)
			{
				stringstream LineStream;
				LineStream << line[i];
				LineStream >> tilenumber;
				
				map.Tile[i][y] = tilenumber;
				LineStream.str("");
			}
			y++;
		}
		map.maxY = TilesVertical * Tile_Height;
		map.sX = 0;
		map.sY = 0;
		MapFile.close();
		TopGround = new Image("Images/ss_gt.png", 0, 0);
		Ground = new Image("Images/ss_gb.png", 0, 0);
		Block = new Image("Images/ss_cb.png", 0, 0);
		Brick = new Image("Images/ss_brick.png", 0, 0);
		EmptyBlock = new Image("Images/ss_cbh.png", 0, 0);
		FlagPole = new Image("Images/ss_fp.png", 0, 0);
		FlagPoleTop = new Image("Images/ss_fpt.png", 0, 0);
		FlagPoleBottom = new Image("Images/ss_fpb.png", 0, 0);
	}
}


void Map::DrawMap(SDL_Surface* Screen)
{
    int x, y, mapX, x1, x2;

	mapX = map.sX / Tile_Width;
	x1 = (map.sX % Tile_Width) * -1;
	x2 = x1 + WIDTH + (x1 == 0 ? 0 : Tile_Width);
	for(y = 0; y < TilesVertical; y++)
	{
		mapX = map.sX / Tile_Width;
		for(x = x1; x < x2; x += Tile_Width)
		{
				if(map.Tile[mapX][y] == TILE_TYPE_GROUND)
				{
					Ground->cX = x;
					Ground->cY = y * Tile_Height;
					Ground->Render(Screen);
				}else if(map.Tile[mapX][y] == TILE_TYPE_TOPGROUND)
				{
					TopGround->cX = x;
					TopGround->cY = y * Tile_Height;
					TopGround->Render(Screen);
				}else if(map.Tile[mapX][y] == TILE_TYPE_BRICK || map.Tile[mapX][y] == TILE_TYPE_BRICKBLOCK)
				{
					Brick->cX = x;
					Brick->cY = y * Tile_Height;
					Brick->Render(Screen);
				}else if(map.Tile[mapX][y] == TILE_TYPE_BLOCK)
				{
					Block->cX = x;
					Block->cY = y * Tile_Height;
					Block->Render(Screen);
				}else if(map.Tile[mapX][y] == TILE_TYPE_EMPTYBLOCK)
				{
					EmptyBlock->cX = x;
					EmptyBlock->cY = y * Tile_Height;
					EmptyBlock->Render(Screen);
				}else if(map.Tile[mapX][y] == TILE_TYPE_FLAG)
				{
					FlagPole->cX = x;
					FlagPole->cY = y * Tile_Height;
					FlagPole->Render(Screen);
				}else if(map.Tile[mapX][y] == TILE_TYPE_FLAGTOP)
				{
					FlagPoleTop->cX = x;
					FlagPoleTop->cY = y * Tile_Height;
					FlagPoleTop->Render(Screen);
				}else if(map.Tile[mapX][y] == TILE_TYPE_FLAGBOTTOM)
				{
					FlagPoleBottom->cX = x;
					FlagPoleBottom->cY = y * Tile_Height;
					FlagPoleBottom->Render(Screen);
				}
			mapX++;
		}
	}
}
void Map::Update(Player* GamePlayer, float DeltaTime) //Follows Player Around
{
    map.sX = GamePlayer->cX - (WIDTH / 2);
    
    if (map.sX < 0)
    {
        map.sX = 0;
    }
    else if(map.sX + WIDTH >= map.maxX)
    {
        map.sX = map.maxX - WIDTH;
    }

}
void Map::Render(SDL_Surface* Screen)
{
	DrawMap(Screen);
}