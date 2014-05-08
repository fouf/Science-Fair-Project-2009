#include "SDLWindow.h"
#include "State.h"
#include "GameObject.h"
#include "Util.h"
#include "Game.h"
State* CurrentState;

int main(int argc, char** argv)
{
	SDLWindow SDLGame;
	if(SDLGame.Create(WIDTH, HEIGHT, 16, SDL_DOUBLEBUF | SDL_SWSURFACE | SDL_ANYFORMAT, FIMAGE_INIT | FTTF_INIT | FMIXER_INIT))
	{
		CurrentState = new Branding(SDLGame.GameObjects);
		//CurrentState = new Game(SDLGame.GameObjects);
		for(;;)
		{
			if(SDLGame.Tick(SDLGame.GameObjects))
				break;
		}
	}
	Log("Quit successfully");
	return 0;
}