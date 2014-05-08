#include "Branding.h"

Branding::Branding()
{
	BrandingImage = NULL;
}
Branding::Branding(map<string, GameObject*>& Objects)
{
	// Load up start-up music.. play it end it!
	Objects["Branding"] = new Image("Images/branding.png", ((WIDTH / 2) - 50), (HEIGHT / 2));
	Objects["Branding"]->cX = (WIDTH / 2) - (Objects["Branding"]->Surface->w / 2);
	Objects["Branding"]->cY = (HEIGHT / 2) - (Objects["Branding"]->Surface->h / 2);
	BrandingImage = static_cast<Image*>(Objects["Branding"]);
}

Branding::~Branding()
{
	delete BrandingImage;
}

void Branding::Process(map<string, GameObject*>& Objects, float DeltaTime)
{
	static float alpha = 0;
	if(alpha < 255)
	{
		alpha += 85.0f * DeltaTime;
		SDL_SetAlpha(BrandingImage->Surface, SDL_SRCALPHA, Uint8(alpha));
	}
	else
	{
		SDL_Delay(500);
		Objects.clear();
		ChangeState(new Menu(Objects));
	}
}