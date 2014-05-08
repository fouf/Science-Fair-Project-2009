#ifndef Branding_H
#define Branding_H
#include "State.h"
#include "Menu.h"
class Branding : public State
{
public:
	Branding();
	Branding(map<string, GameObject*>& Objects);
	~Branding();
	void Process(map<string, GameObject*>& Objects, float Time);

private:
	Image* BrandingImage;

};
#endif