#ifndef Image_H
#define Image_H
#include "GameObject.h"
class Image : public GameObject
{
public:
	Image();
	Image(std::string File, int x, int y);
	~Image();
};
#endif