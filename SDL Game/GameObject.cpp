#include "GameObject.h"

GameObject::GameObject()
{
	cX = 0;
	cY = 0;
	bVisible = true;
}
GameObject::~GameObject()
{

}

bool GameObject::isVisible()
{
	return bVisible;
}
void GameObject::setVisible(bool bVisibility)
{
	bVisible = bVisibility;
}

void GameObject::Render(SDL_Surface* Screen)
{
	Apply_Surface(cX, cY, Surface, Screen, NULL);
}

void GameObject::Apply_Surface(int x, int y, SDL_Surface* Source, SDL_Surface* Destination, SDL_Rect* Clip)
{
	SDL_Rect Offset;
	Offset.x = x;
	Offset.y = y;
	Offset.h = 0;
	Offset.w = 0;
	//Blit the surface
	if((SDL_BlitSurface(Source, Clip, Destination, &Offset) == -1))
	{
		Log(std::string("SDL_BlitSurface failed to blit, ") + SDL_GetError());
	}
}
SDL_Surface* GameObject::Load_Image(std::string Filename)
{
	SDL_Surface* Loaded_Image = NULL;
	SDL_Surface* Optimized_Image = NULL;
	Loaded_Image = IMG_Load(Filename.c_str());
	SDL_RWops *Test;
	Test = SDL_RWFromFile(Filename.c_str(), "rb");
	if(IMG_isPNG(Test) || IMG_isJPG(Test))
	{
		if(Loaded_Image != NULL)
		{
			Optimized_Image = SDL_DisplayFormat(Loaded_Image);
			SDL_FreeSurface(Loaded_Image);
			if(Optimized_Image != NULL)
			{
				Uint32 Color_Key = SDL_MapRGB(Optimized_Image->format, 0xFF, 0, 0xFF);
				SDL_SetColorKey(Optimized_Image, SDL_SRCCOLORKEY, Color_Key);
			}
		}
		return Optimized_Image;
	}
	return Loaded_Image;
}
int GameObject::Check_Collision(SDL_Rect A, SDL_Rect B)
{
	int leftA, leftB, rightA, rightB, bottomA, bottomB, topA, topB, centerAY, centerBY;
	leftA = A.x;
	rightA = A.x + A.w;
	topA = A.y;
	bottomA = A.y + A.h;
	leftB = B.x;
	rightB = B.x + B.w;
	topB = B.y;
	bottomB = B.y + B.h;
	centerAY = A.h / 2;
	centerBY = B.h / 2;
	if(bottomA <= topB)
	{
		return COLLISION_NONE; 
	}
	if(topA >= bottomB){
		return COLLISION_NONE;
	}
	if(rightA <= leftB)
	{ 
		return COLLISION_NONE;
	}
	if(leftA >= rightB)
	{
		return COLLISION_NONE;
	}

	if(topB <= topA && topB != topA)
	{
		return COLLISION_TOP;
	}
	else if(leftB + 15 <= rightA)
	{
		return COLLISION_RIGHT;
	}
	else if(rightB + 15 <= leftA)
	{
		return COLLISION_LEFT;
	}else if(topA <= bottomB)
	{
		return COLLISION_BOTTOM;
	}
	return COLLISION_NONE;
}
