#ifndef CRUDE_TIMER_H
#define CRUDE_TIMER_H

//This library must be included.
#pragma comment(lib, "winmm.lib")
#include <windows.h>

//A macro that accesses the instance of this singleton class.
#define Clock CrudeTimer::Instance()

//A class that represents the clock in the game.
class CrudeTimer{

private:
	//The time at which the clock was first initialised.
	double startTime;

	//Various constructors.
	//Default constructor that initialises startTime data member.
	CrudeTimer(){startTime = timeGetTime() * 0.001f;}
	CrudeTimer(const CrudeTimer&);
	CrudeTimer& operator=(const CrudeTimer&);

public:
	//A getter method for the instance of this singleton class.
	static CrudeTimer* Instance();
	//A method that returns the current time in the game.
	double GetCurrentTime(){return (timeGetTime() * 0.001f) - startTime;}

};

CrudeTimer* CrudeTimer::Instance(){

	static CrudeTimer instance;

	return &instance;

}

#endif 