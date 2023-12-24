#include "Dwarf.h"
#include "ConsoleUtils.h"

void Dwarf::Update(){

	SetTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	IncreaseThirst();
	IncreaseTobaccoNeed();
	GetStateMachine()->Update();

}

bool Dwarf::HandleMessage(const Telegram& message){return GetStateMachine()->HandleMessage(message);}