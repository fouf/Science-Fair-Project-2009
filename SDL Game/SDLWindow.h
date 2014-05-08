#ifndef SDLWindow_H
#define SDLWindow_H

#include "Branding.h"
#include "Timer.h"

using namespace std;
class SDLWindow{

public:
	SDLWindow();
	~SDLWindow();

	bool Create(int Width, int Height, int Bpp, Uint32 Flags, int InitFlags);
	bool Tick(map<string, GameObject*>& GameObjects);
	
	void Shutdown();

	std::map<string, GameObject*> GameObjects;
	
	Timer GameTimer;
	Timer Update;

	bool UpdateTime;
	float Frames;
	float PreviousTime;
	SDL_Surface *Screen;
	Font* FrameRate;
private:
	void StopSDL();
	SDL_Event SDLEvent;
};

#endif