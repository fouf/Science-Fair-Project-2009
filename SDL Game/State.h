#ifndef State_H
#define State_H

#include <map>
#include "Font.h"
#include "Image.h"

using namespace std;

class State{
public:
	State();
	virtual ~State();

	virtual void Process(map<string, GameObject*>& Objects, float DeltaTime);
	virtual bool Event(SDL_Event& Event);
	void ChangeState(State* NewState);
private:
	
};

#endif