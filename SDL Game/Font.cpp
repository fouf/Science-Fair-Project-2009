#include "Font.h"


Font::Font(std::string FontName, int FontSize, std::string Text, int x, int y)
{
	font = NULL;
	sText = Text;
	cX = x;
	cY = y;
	font = TTF_OpenFont(FontName.c_str(), FontSize);
	TextColor.r = 255;
	TextColor.b = 255;
	TextColor.g = 255;
	if(!font)
	{
		Log(std::string("Font failed to load, ") + TTF_GetError());
	}
	cText = sText;
	Color = TextColor;	
	Surface = TTF_RenderText_Solid(font, sText.c_str(), TextColor);
}
Font::~Font()
{
	SDL_FreeSurface(Surface);
}
void Font::Render(SDL_Surface *Screen)
{
	if(cText != sText || Color.r != TextColor.r || Color.g != TextColor.g || Color.b != TextColor.b)
	{
		cText = "";
		cText = sText;
		Color = TextColor;
		Surface = TTF_RenderText_Solid(font, sText.c_str(), TextColor);
	}
	Apply_Surface(cX, cY, Surface, Screen, NULL);
}