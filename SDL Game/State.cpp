#include "State.h"
extern State* CurrentState;
State::State()
{

}

State::~State(){
}

void State::Process(map<string, GameObject*>& Objects, float DeltaTime)
{

}

void State::ChangeState(State* NewState)
{
	delete CurrentState;
	CurrentState = NewState;
}

bool State::Event(SDL_Event &Event)
{
	while(SDL_PollEvent(&Event)){
		if(Event.type == SDL_QUIT)
		{
			return true;
		}
		if(Event.active.gain == 0)
		{
			SDL_Delay(50);
		}
	}
	return false;
}