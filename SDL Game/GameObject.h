#ifndef GameObject_H
#define GameObject_H
#include "Util.h"
class GameObject{
public:
	GameObject();
	~GameObject();
	virtual void Render(SDL_Surface* Screen);

	bool isVisible();
	void setVisible(bool bVisibility);
	bool bVisible;

	int cX, cY;

	SDL_Surface *Surface;

	void Apply_Surface(int x, int y, SDL_Surface* Source, SDL_Surface* Destination, SDL_Rect* Clip);
	SDL_Surface *Load_Image(std::string Filename);
	static int Check_Collision(SDL_Rect A, SDL_Rect B);
};

#endif