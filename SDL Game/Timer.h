#ifndef Timer_H
#define Timer_H
#include "SDL.h"

class Timer
{
public:
	Timer();
	~Timer();
	void start();
	void stop();
	void pause();
	void unpause();
	float  get_ticks();
	bool is_started();
	bool is_paused();
private:
	float startTicks;
	float pausedTicks;
	bool paused;
	bool started;
};

#endif