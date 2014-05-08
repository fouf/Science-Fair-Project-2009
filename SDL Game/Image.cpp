#include "Image.h"
Image::Image()
{
	Surface = NULL;
}
Image::Image(std::string File, int x, int y)
{
	cX = x;
	cY = y;
	bVisible = true;
	Surface = Load_Image(File);
}
Image::~Image()
{
	SDL_FreeSurface(Surface);
}