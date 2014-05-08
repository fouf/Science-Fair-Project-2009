#ifndef Menu_H
#define Menu_H
#include "State.h"
class Menu : public State
{
public:
	Menu();
	Menu(map<string, GameObject*>& Objects);
	~Menu();
	void Process(map<string, GameObject*>& Objects, float DeltaTime);
	bool Event(SDL_Event& Event);

private:
	Font* Title;
	Font* Menu1;
	Font* Menu2;
	Font* Menu3;
	int Channel;
	Mix_Chunk *BGMusic;
};
#endif