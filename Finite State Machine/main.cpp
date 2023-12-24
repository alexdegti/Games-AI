#include <time.h>
#include <fstream>
#include <utility>
#include <string>

#include "Elf.h"
#include "Centaur.h"
#include "Dwarf.h"
#include "EntityNames.h"
#include "EntityManager.h"
#include "MessageDispatcher.h"
#include "ConsoleUtils.h"

using std::cout;
using std::endl;

//A method that determines the richest entity once
//the game ends.
std::pair<std::string, BaseGameEntity*> DetermineTheRichestEntity(Elf* elf, Centaur* centaur, Dwarf* dwarf){

	std::pair<std::string, BaseGameEntity*> richestEntity = std::make_pair("null", nullptr);

	if(elf->GetCurrentNumberOfGoldCoins() > centaur->GetCurrentNumberOfGoldCoins() &&
	   elf->GetCurrentNumberOfGoldCoins() > dwarf->GetCurrentNumberOfGoldCoins())
	       richestEntity = std::make_pair("elf", elf);
	else if(centaur->GetCurrentNumberOfGoldCoins() > elf->GetCurrentNumberOfGoldCoins() &&
		    centaur->GetCurrentNumberOfGoldCoins() > dwarf->GetCurrentNumberOfGoldCoins())
			    richestEntity = std::make_pair("centaur", centaur);
	else if(dwarf->GetCurrentNumberOfGoldCoins() > elf->GetCurrentNumberOfGoldCoins() &&
		    dwarf->GetCurrentNumberOfGoldCoins() > centaur->GetCurrentNumberOfGoldCoins())
		        richestEntity = std::make_pair("dwarf", dwarf);
	
	return richestEntity;

}

//A method that determines the winning entity once
//the game ends.
std::pair<std::string, BaseGameEntity*> DetermineTheWinner(Elf* elf, Centaur* centaur, Dwarf* dwarf){

	std::pair<std::string, BaseGameEntity*> winner = std::make_pair("null", nullptr);

	if(!elf->IsInATerminalState() && centaur->IsInATerminalState() && dwarf->IsInATerminalState())
		winner = std::make_pair("elf", elf);
	else if(!centaur->IsInATerminalState() && elf->IsInATerminalState() && dwarf->IsInATerminalState())
		winner = std::make_pair("centaur", centaur);
	else if(!dwarf->IsInATerminalState() && elf->IsInATerminalState() && centaur->IsInATerminalState())
		winner = std::make_pair("dwarf", dwarf);
	else if(!elf->IsInATerminalState() && !centaur->IsInATerminalState() && dwarf->IsInATerminalState())
		 winner = elf->GetCurrentNumberOfGoldCoins() == centaur->GetCurrentNumberOfGoldCoins() ? std::make_pair("null", nullptr) :
			    ((elf->GetCurrentNumberOfGoldCoins() > centaur->GetCurrentNumberOfGoldCoins()) ? std::make_pair("elf", (BaseGameEntity*)elf) :
				std::make_pair("centaur", centaur));
	else if(!centaur->IsInATerminalState() && !dwarf->IsInATerminalState() && elf->IsInATerminalState())
		winner = centaur->GetCurrentNumberOfGoldCoins() == dwarf->GetCurrentNumberOfGoldCoins() ? std::make_pair("null", nullptr) :
			    (centaur->GetCurrentNumberOfGoldCoins() > dwarf->GetCurrentNumberOfGoldCoins() ? std::make_pair("centaur", (BaseGameEntity*)centaur) :
				std::make_pair("dwarf", dwarf));
	else if(!elf->IsInATerminalState() && !dwarf->IsInATerminalState() && centaur->IsInATerminalState())
		winner = elf->GetCurrentNumberOfGoldCoins() == dwarf->GetCurrentNumberOfGoldCoins() ? std::make_pair("null", nullptr) :
			    (elf->GetCurrentNumberOfGoldCoins() > dwarf->GetCurrentNumberOfGoldCoins() ? std::make_pair("elf", (BaseGameEntity*)elf) :
				std::make_pair("dwarf", dwarf));
	else if((elf->IsInATerminalState() && centaur->IsInATerminalState() && dwarf->IsInATerminalState()) ||
		    (!elf->IsInATerminalState() && !centaur->IsInATerminalState() && !dwarf->IsInATerminalState()))
		winner = DetermineTheRichestEntity(elf, centaur, dwarf);

	return winner;

}

//The main function.
int main(){

	//Seeds random number generator.
	srand((unsigned)time(nullptr));

	//Creates the elf, centaur and dwarf.
	Elf* elf = new Elf(entityElf);
	Centaur* centaur = new Centaur(entityCentaur);
	Dwarf* dwarf = new Dwarf(entityDwarf);

	//Adds the elf, centaur and dwarf to the entitiesMap data 
	//member of class EntityManager.
	Manager->AddEntity(elf);
	Manager->AddEntity(centaur);
	Manager->AddEntity(dwarf);

	for(int i = 0; i < 30; i++){
		elf->Update();
		centaur->Update();
		dwarf->Update();
		Dispatcher->DispatchDelayedMessage();
		Sleep(700);
	}

	std::pair<std::string, BaseGameEntity*> winner = DetermineTheWinner(elf, centaur, dwarf);
	BaseGameEntity* winnerPointer = winner.second;

	if(winnerPointer)
		winnerPointer->WinningGameMessage();
	else
		cout << "There is no winner!" << endl;

	delete elf;
	delete centaur;
	delete dwarf;

	PressAnyKeyToContinue();

	return 0;

}