#include "Elf.h"
#include "ConsoleUtils.h"

void Elf::Update(){

	SetTextColor(FOREGROUND_RED| FOREGROUND_BLUE| FOREGROUND_INTENSITY);
	IncreaseThirst();
	IncreaseIntellectualStimulation();
	GetStateMachine()->Update();

}

bool Elf::HandleMessage(const Telegram& message){return GetStateMachine()->HandleMessage(message);}