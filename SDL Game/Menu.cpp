#include "Menu.h"
#include "Game.h"
static int counter = 1;
static int change = 0;
Menu::Menu()
{

}
Menu::Menu(map<string, GameObject*>& Objects)
{
	Objects["Title"] = new Font("FahmonNormal.ttf", 56, GAME_NAME + string(" Menu"), ((WIDTH / 2) - 50), HEIGHT / 10);
	Objects["Title"]->cX = (WIDTH / 2) - (Objects["Title"]->Surface->w / 2);
	Title = static_cast<Font*>(Objects["Title"]);

	Objects["Menu1"] = new Font("Fahmon.ttf", 52, "Start", ((WIDTH / 2) - 50), HEIGHT / 3);
	Objects["Menu1"]->cX = (WIDTH / 2) - (Objects["Menu1"]->Surface->w / 2);
	Menu1 = static_cast<Font*>(Objects["Menu1"]);

	Objects["Menu2"] = new Font("Fahmon.ttf", 52, "Options", ((WIDTH / 2) - 50), int(HEIGHT / 2.5));
	Objects["Menu2"]->cX = (WIDTH / 2) - (Objects["Menu2"]->Surface->w / 2);
	Menu2 = static_cast<Font*>(Objects["Menu2"]);

	Objects["Menu3"] = new Font("Fahmon.ttf", 52, "Exit", ((WIDTH / 2) - 50), HEIGHT / 2);
	Objects["Menu3"]->cX = (WIDTH / 2) - (Objects["Menu3"]->Surface->w / 2);
	Menu3 = static_cast<Font*>(Objects["Menu3"]);

	// Play menu music
	BGMusic = Mix_LoadWAV("Music/MainMenu.wav");
	if(BGMusic == NULL) {
		Log(string("Unable to load WAV file, ") + Mix_GetError());
	}
	Channel = Mix_PlayChannel(1, BGMusic, -1);
	if(Channel == -1) {
		Log(string("Unable to play WAV file, ") + Mix_GetError());
	}
}

Menu::~Menu()
{
	change = 0;
	counter = 1;
	Mix_Pause(Channel);
	Mix_FreeChunk(BGMusic);
	delete Menu1;
	delete Menu2;
	delete Menu3;
	delete Title;
}

void Menu::Process(map<string, GameObject*>& Objects, float DeltaTime)
{
	if(counter == 1){
		Menu1->TextColor.r = 255;   Menu1->TextColor.b = 0;	  Menu1->TextColor.g = 0;
		Menu2->TextColor.b = 255;	Menu2->TextColor.g = 255; Menu2->TextColor.r = 255;
		Menu3->TextColor.b = 255;	Menu3->TextColor.g = 255; Menu3->TextColor.r = 255;
	}else if(counter == 2)
	{
		Menu2->TextColor.r = 255;	Menu2->TextColor.b = 0;   Menu2->TextColor.g = 0;
		Menu1->TextColor.b = 255;	Menu1->TextColor.g = 255; Menu1->TextColor.r = 255;
		Menu3->TextColor.b = 255;	Menu3->TextColor.g = 255; Menu3->TextColor.r = 255;

	}else{
		Menu3->TextColor.r = 255;   Menu3->TextColor.b = 0;	  Menu3->TextColor.g = 0;
		Menu2->TextColor.b = 255;	Menu2->TextColor.g = 255; Menu2->TextColor.r = 255;
		Menu1->TextColor.b = 255;	Menu1->TextColor.g = 255; Menu1->TextColor.r = 255;
	}
	if(change == 1)
	{//Game
		Objects.clear();
		ChangeState(new Game(Objects));
	}
	else if(change == 2)
	{//Options
		Objects.clear();
		// Change state options
	}
}

bool Menu::Event(SDL_Event& Event){
		while(SDL_PollEvent(&Event)){
		if(Event.type == SDL_KEYDOWN){
			switch(Event.key.keysym.sym){
			case SDLK_UP:
				counter -= 2;

				if(counter < 1)
				{
					counter = 1;
				}

			break;

			case SDLK_DOWN:
				counter += 2;

				if(counter > 3)
				{
					counter = 3;
				}
			break;

			case SDLK_RETURN:
				if(counter == 1)
				{
					change = 1;					
				}
				if(counter == 2)
				{
					change = 2;				
				}
				if(counter == 3)
				{	
					return true;
				}
			break;

			default:
			break;
			}
		}
		if(Event.type == SDL_QUIT)
		{
			return true;
		}
		if(Event.active.gain == 0)
		{
			SDL_Delay(50);
		}
	return false;
	
	}
	return false;
}