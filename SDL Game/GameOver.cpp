#include "GameOver.h"

Gameover::Gameover()
{
}

Gameover::Gameover(map<string, GameObject*>& Objects)
{
	Objects["Message"] = new Font("FahmonNormal.ttf", 32, "Game Over", 400, 100);
	Message = static_cast<Font*>(Objects["Message"]);
	Message->cX = (WIDTH / 2) - (Message->Surface->w / 2);

	Objects["ToMenu"] = new Font("FahmonNormal.ttf", 32, "Hit Enter to return menu", 400, 300);
	ToMenu = static_cast<Font*>(Objects["Message"]);
	ToMenu->cX = (WIDTH / 2) - (ToMenu->Surface->w / 2);
	ToMenu->TextColor.r = 255;

	BGMusic = Mix_LoadWAV("Music/GameOver.wav");
	if(BGMusic == NULL) {
		Log(string("Unable to load WAV file, ") + Mix_GetError());
	}
	Channel = Mix_PlayChannel(-1, BGMusic, 0);
	if(Channel == -1) {
		Log(string("Unable to play WAV file, ") + Mix_GetError());
	}
	toMenu = 0;
}
Gameover::~Gameover()
{
	Mix_Pause(Channel);
	Mix_FreeChunk(BGMusic);
}
void Gameover::Process(map<string, GameObject*>& Objects, float DeltaTime)
{
	if(toMenu == 1)
	{
		Objects.clear();
		ChangeState(new Menu(Objects));
	}
}

bool Gameover::Event(SDL_Event& Event)
{
	while(SDL_PollEvent(&Event)){
		if(Event.type == SDL_KEYDOWN){
			switch(Event.key.keysym.sym){
				case SDLK_RETURN:
					toMenu = 1;
				break;
			}
		}
	}
	return false;
}