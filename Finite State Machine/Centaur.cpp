#include "Centaur.h"
#include "ConsoleUtils.h"

void Centaur::Update(){

	SetTextColor(FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	IncreaseThirst();
	WorsenTailStatus();
	GetStateMachine()->Update();

}

bool Centaur::HandleMessage(const Telegram& message){return GetStateMachine()->HandleMessage(message);}