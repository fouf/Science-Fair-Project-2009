#ifndef Gameover_H
#define Gameover_H
#include "State.h"
#include "Menu.h"
class Gameover : public State
{
public:
	Gameover();
	Gameover(map<string, GameObject*>& Objects);
	~Gameover();
	void Process(map<string, GameObject*>& Objects, float DeltaTime);
	bool Event(SDL_Event& Event);

private:
	Font* Message;
	Font* ToMenu;
	int Channel, toMenu;
	Mix_Chunk *BGMusic;
};
#endif