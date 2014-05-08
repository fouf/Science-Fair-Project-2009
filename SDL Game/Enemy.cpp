#include "Enemy.h"

Enemy::Enemy()
{
	Surface = NULL;
}
Enemy::~Enemy()
{
	
}
Enemy::Enemy(std::string Enemy, int x, int y, Map_Info *CurrentLevel)
{
	cX = x;
	cY = y;
	yVel = xVel = 0.0f;
	Surface = Load_Image(Enemy);
	Level = CurrentLevel;
}
void Enemy::CheckCollisions(float DeltaTime)
{
int i, x1, x2, y1, y2;
	i = (Surface->h > Tile_Height) ? Tile_Height : Surface->h;

	// Checking Horizantal Movement First!
	for(;;)
	{
		x1 = int((cX + (xVel * DeltaTime)) / Tile_Width); // Left Side of new position!
		x2 = int((cX + (xVel * DeltaTime) + Surface->w - 1) / Tile_Width); // Right Side of new position!

		y1 = cY / Tile_Height; // Top of new position!
		y2 = (cY + i - 1) / Tile_Height; // Bottom of new position!
		if(x1 >= 0 && x2 < Level->maxX && y1 >= 0 && y2 < Level->maxY) // If we are in the bounds of the map
		{
			if(xVel > 0)	// We are moving right ->
			{
				if((Level->Tile[x2][y1] != TILE_TYPE_EMPTY) || (Level->Tile[x2][y2] != TILE_TYPE_EMPTY)) // If we run into a block
				{
					cX = x2 * Tile_Width;
					cX -= Surface->w + 1;
					xVel = -200.0f;
				}
			}
			else if(xVel < 0)  // We are moving left <---
			{
				if((Level->Tile[x1][y1] != TILE_TYPE_EMPTY) || (Level->Tile[x1][y2] != TILE_TYPE_EMPTY))
				{
					cX = (x1 + 1) * Tile_Width;
					xVel = 200.0f;
				}
			}
		}

		if(i == Surface->h)
		{
			break;
		}
		
		i += Tile_Height;

		if(i > Surface->h)
		{
			i = Surface->h;
		}
	}
	// Testing Vertical Movement

	i = (Surface->w > Tile_Width) ? Tile_Width : Surface->w;

	for(;;)
	{
		x1 = cX / Tile_Width;
		x2 = (cX + i) / Tile_Width;

		y1 = int((cY + (yVel * DeltaTime)) / Tile_Height);
		y2 = int((cY + (yVel * DeltaTime) + Surface->h) / Tile_Height);

		if(x1 >= 0 && x2 < Level->maxX && y1 >= 0 && y2 < Level->maxY)
		{
			if(yVel > 0) // We are going down
			{
				if((Level->Tile[x1][y2] != TILE_TYPE_EMPTY) || (Level->Tile[x2][y2] != TILE_TYPE_EMPTY))
				{
					cY = y2 * Tile_Height;
					cY -= Surface->h;
					yVel = 0.0f;
				}
			}
			else if(yVel < 0) // We are going up
			{
				if((Level->Tile[x1][y1] != TILE_TYPE_EMPTY) || (Level->Tile[x2][y1] != TILE_TYPE_EMPTY))
				{
					cY = (y1 + 1) * Tile_Height;
					yVel = 0.0f;
				}
				}
		}

		if(i == Surface->w)
		{
			break;
		}
		i += Tile_Height;

		if(i > Surface->w)
		{
			i = Surface->w;
		}
	}
	
}

void Enemy::UpdatePosition(float DeltaTime)
{
	if(xVel == 0)
	{
		xVel = 200.0f;
	}
	int GravityInfluence = (3*9.81);
	yVel += GravityInfluence;
	cX += xVel * DeltaTime;
	cY += yVel * DeltaTime;
    if(cX < 0)
    {
        cX = 0;
		xVel = 200.0f;
    }
    else if(cX + Surface->w >= Level->maxX)
    {
        cX = Level->maxX - Surface->w - 1;
		xVel = -200.0f;
    }
	if(cY < 0)
	{
		cY = 0;
	}

}
void Enemy::Process(float DeltaTime)
{
	UpdatePosition(DeltaTime);
	CheckCollisions(DeltaTime);

}

void Enemy::Render(SDL_Surface* Screen)
{
	Apply_Surface(cX - Level->sX, cY, Surface, Screen, NULL);
}