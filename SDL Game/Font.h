#ifndef Font_H
#define Font_H
#include "GameObject.h"
class Font : public GameObject
{
public:
	Font();
	Font(std::string FontName, int FontSize, std::string Text, int x, int y);
	~Font();
	void Render(SDL_Surface *Screen);

	SDL_Color TextColor;
	SDL_Color Color;
	TTF_Font *font;
	std::string sText;
	std::string cText;
};
#endif