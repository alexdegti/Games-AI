#include <iostream>

#include "CentaurOwnedStates.h"
#include "Centaur.h"
#include "Locations.h"
#include "EntityNames.h"
#include "Auxiliary.h"

using std::cout;
using std::endl;

//-----------------------CentaursGlobalState methods---------------------
CentaursGlobalState* CentaursGlobalState::Instance(){

	static CentaursGlobalState instance;

	return &instance;

}

void CentaursGlobalState::Enter(Centaur* centaur){};//cout << GetNameOfEntity(centaur->GetEntityID()) << ": CentaursGlobalState->Enter()" << endl;}

void CentaursGlobalState::Execute(Centaur* centaur){

	//cout << GetNameOfEntity(centaur->GetEntityID()) << ": CentaursGlobalState->Execute()" << endl;
	cout << GetNameOfEntity(centaur->GetEntityID()) << ": Current number of gold coins is " << centaur->GetCurrentNumberOfGoldCoins() << "." << endl;

	if(centaur->DoesTailRequireBrooming() && centaur->GetStateMachine()->IsInState(*ExploreDungeonCentaur::Instance())){
		centaur->GetStateMachine()->ChangeState(GoToTheBeautySalon::Instance());
		return;
	}

	if(centaur->IsThirsty() && centaur->GetStateMachine()->IsInState(*ExploreDungeonCentaur::Instance())){
		centaur->GetStateMachine()->ChangeState(GoToThePubCentaur::Instance());
		return;
	}

	if(centaur->IsDownAndOut() && centaur->GetStateMachine()->IsInState(*ExploreDungeonCentaur::Instance())){
		centaur->GetStateMachine()->ChangeState(DownAndOutCentaur::Instance());
		return;
	}

}

void CentaursGlobalState::Exit(Centaur* centaur){};//cout << GetNameOfEntity(centaur->GetEntityID()) << ": CentaursGlobalState->Exit()" << endl;}

bool CentaursGlobalState::HandleMessage(Centaur* centaur, const Telegram& message){return false;}
//-----------------------------------------------------------------------

//---------------------ExploreDungeonCentaur methods---------------------
ExploreDungeonCentaur* ExploreDungeonCentaur::Instance(){

	static ExploreDungeonCentaur instance;

	return &instance;

}

void ExploreDungeonCentaur::Enter(Centaur* centaur){

	//cout << GetNameOfEntity(centaur->GetEntityID()) << ": ExploreDungeonCentaur->Enter()" << endl;

	if(centaur->GetLocation() != Location::dungeon){
		cout << GetNameOfEntity(centaur->GetEntityID()) << ": Heading towards the dungeon!" << endl;
		centaur->SetLocation(Location::dungeon);
	}

}

void ExploreDungeonCentaur::Execute(Centaur* centaur){

	//cout << GetNameOfEntity(centaur->GetEntityID()) << ": ExploreDungeonCentaur->Execute()" << endl;
	cout << GetNameOfEntity(centaur->GetEntityID()) << ": Current number of gold coins is " << centaur->GetCurrentNumberOfGoldCoins() << "." << endl;

	double randomEvent = RandomFloat();

	if(randomEvent > 0.6f && randomEvent < 0.9f){
		centaur->GetStateMachine()->ChangeState(BattleMonsterCentaur::Instance());
		return;
	}
	else if(randomEvent >= 0.9){
		centaur->GetStateMachine()->ChangeState(OpenTreasureChestCentaur::Instance());
		return;
	}

	centaur->IncreaseFatigue();
	cout << GetNameOfEntity(centaur->GetEntityID()) << ": I sure am feeling the fatigue!" << endl;

	if(centaur->IsFatigued())
		centaur->GetStateMachine()->ChangeState(GoToTheInnCentaur::Instance());

}

void ExploreDungeonCentaur::Exit(Centaur* centaur){};//cout << GetNameOfEntity(centaur->GetEntityID()) << ": ExploreDungeonCentaur->Exit()" << endl;}

bool ExploreDungeonCentaur::HandleMessage(Centaur* centaur, const Telegram& message){return false;}
//-----------------------------------------------------------------------

//---------------------BattleMonsterCentaur methods----------------------
BattleMonsterCentaur* BattleMonsterCentaur::Instance(){

	static BattleMonsterCentaur instance;

	return &instance;

}

void BattleMonsterCentaur::Enter(Centaur* centaur){};//cout << GetNameOfEntity(centaur->GetEntityID()) << ": BattleMonsterCentaur->Enter()" << endl;}

void BattleMonsterCentaur::Execute(Centaur* centaur){

	//cout << GetNameOfEntity(centaur->GetEntityID()) << ": BattleMonsterCentaur->Execute()" << endl;
	cout << GetNameOfEntity(centaur->GetEntityID()) << ": Current number of gold coins is " << centaur->GetCurrentNumberOfGoldCoins() << "." << endl;

	int monster = 7;

	while(monster > 0 && !centaur->IsDead()){
		//Checks whether the centaur has enough arrows left.
		if(centaur->HasArrowsLeft()){
			cout << GetNameOfEntity(centaur->GetEntityID()) << ": I'm going to attack using my bow!" << endl;
			centaur->UseBow(&monster);
		}
		//There aren't enough arrows left to use the bow, therefore use a melee attack.
		else{
			cout << GetNameOfEntity(centaur->GetEntityID()) << ": I'm about to use a melee attack!" << endl;
			centaur->UseMelee(&monster);
		}
		//Checks whether the monster has been defeated.
		if(monster <= 0)
			continue;
		//The monster attacks the centaur.
		int monsterDamage = RandomIntegerInRange(2, 4);
		cout << GetNameOfEntity(centaur->GetEntityID()) << ": Monster attacks, causes " << monsterDamage << " damage." << endl;
		centaur->DecreaseHealthPoints(monsterDamage);
		cout << GetNameOfEntity(centaur->GetEntityID()) << ": battle status: centaur's HP - " << centaur->GetHealthPoints() << " monster's HP - " << monster << "." << endl;
	}
	
	//Checks whether the centaur won or lost the battle.
	if(centaur->IsDead())
		centaur->GetStateMachine()->ChangeState(DieCentaur::Instance());
	else{
		cout << GetNameOfEntity(centaur->GetEntityID()) << ": I've defeated the wicked monster!!" << endl;
		centaur->AddGoldCoins(2);
		centaur->RestoreHealthPoints();
		centaur->GetStateMachine()->RevertToPreviousState();
	}

}

void BattleMonsterCentaur::Exit(Centaur* centaur){};//cout << GetNameOfEntity(centaur->GetEntityID()) << ": BattleMonsterCentaur->Exit()" << endl;}

bool BattleMonsterCentaur::HandleMessage(Centaur* elf, const Telegram& message){return false;}
//-----------------------------------------------------------------------

//---------------------OpenTreasureChestCentaur methods------------------
OpenTreasureChestCentaur* OpenTreasureChestCentaur::Instance(){

	static OpenTreasureChestCentaur instance;

	return &instance;

}

void OpenTreasureChestCentaur::Enter(Centaur* centaur){};//cout << GetNameOfEntity(centaur->GetEntityID()) << ": OpenTreasureChestCentaur->Enter()" << endl;}

void OpenTreasureChestCentaur::Execute(Centaur* centaur){

	//cout << GetNameOfEntity(centaur->GetEntityID()) << ": OpenTreasureChestCentaur->Execute()" << endl;
	cout << GetNameOfEntity(centaur->GetEntityID()) << ": Current number of gold coins is " << centaur->GetCurrentNumberOfGoldCoins() << "." << endl;
	cout << GetNameOfEntity(centaur->GetEntityID()) << ": Oh lovely!! I found myself a treasure chest!" << endl;
	centaur->AddGoldCoins(3);
	centaur->GetStateMachine()->RevertToPreviousState();

}

void OpenTreasureChestCentaur::Exit(Centaur* centaur){};//cout << GetNameOfEntity(centaur->GetEntityID()) << ": OpenTreasureChestCentaur->Exit()" << endl;}

bool OpenTreasureChestCentaur::HandleMessage(Centaur* centaur, const Telegram& message){return false;}
//-----------------------------------------------------------------------

//-----------------------------DieCentaur methods------------------------
DieCentaur* DieCentaur::Instance(){

	static DieCentaur instance;

	return &instance;

}

void DieCentaur::Enter(Centaur* centaur){

	//cout << GetNameOfEntity(centaur->GetEntityID()) << ": DieCentaur->Enter()" << endl;

	if(centaur->GetLocation() != Location::cemetery){
		cout << GetNameOfEntity(centaur->GetEntityID()) << ": Oh no!! I'm dying!" << endl;
		centaur->SetLocation(Location::cemetery);
	}

}

void DieCentaur::Execute(Centaur* centaur){

	//cout << GetNameOfEntity(centaur->GetEntityID()) << ": DieCentaur->Execute()" << endl;
	cout << GetNameOfEntity(centaur->GetEntityID()) << ": Current number of gold coins is " << centaur->GetCurrentNumberOfGoldCoins() << "." << endl;
	cout << GetNameOfEntity(centaur->GetEntityID()) << ": I'm dead!!" << endl;

}

void DieCentaur::Exit(Centaur* centaur){};//cout << GetNameOfEntity(centaur->GetEntityID()) << ": DieCentaur->Exit()" << endl;}

bool DieCentaur::HandleMessage(Centaur* centaur, const Telegram& message){return false;}
//-----------------------------------------------------------------------

//----------------------DieFromDehydrationCentaur methods----------------
DieFromDehydrationCentaur* DieFromDehydrationCentaur::Instance(){

	static DieFromDehydrationCentaur instance;

	return &instance;

}

void DieFromDehydrationCentaur::Enter(Centaur* centaur){

	//cout << GetNameOfEntity(centaur->GetEntityID()) << ": DieFromDehydrationCentaur->Enter()" << endl;

	if(centaur->GetLocation() != Location::cemetery){
		cout << GetNameOfEntity(centaur->GetEntityID()) << ": Oh no!! I'm dying!" << endl;
		centaur->SetLocation(Location::cemetery);
	}

}

void DieFromDehydrationCentaur::Execute(Centaur* centaur){

	//cout << GetNameOfEntity(centaur->GetEntityID()) << ": DieFromDehydrationCentaur->Execute()" << endl;
	cout << GetNameOfEntity(centaur->GetEntityID()) << ": Current number of gold coins is " << centaur->GetCurrentNumberOfGoldCoins() << "." << endl;
	cout << GetNameOfEntity(centaur->GetEntityID()) << ": I'm dead!!" << endl;

}

void DieFromDehydrationCentaur::Exit(Centaur* centaur){};//cout << GetNameOfEntity(centaur->GetEntityID()) << ": DieFromDehydrationCentaur->Exit()" << endl;}

bool DieFromDehydrationCentaur::HandleMessage(Centaur* centaur, const Telegram& message){return false;}
//-----------------------------------------------------------------------

//-----------------------DeadKnackeredCentaur methods--------------------
DeadKnackeredCentaur* DeadKnackeredCentaur::Instance(){

	static DeadKnackeredCentaur instance;

	return &instance;

}

void DeadKnackeredCentaur::Enter(Centaur* centaur){

	//cout << GetNameOfEntity(centaur->GetEntityID()) << ": DeadKnackeredCentaur->Enter()" << endl;

	if(centaur->GetLocation() != Location::cemetery){
		cout << GetNameOfEntity(centaur->GetEntityID()) << ": Oh no!! I'm dying from exhaustion!" << endl;
		centaur->SetLocation(Location::cemetery);
	}

}

void DeadKnackeredCentaur::Execute(Centaur* centaur){

	//cout << GetNameOfEntity(centaur->GetEntityID()) << ": DeadKnackeredCentaur->Execute()" << endl;
	cout << GetNameOfEntity(centaur->GetEntityID()) << ": Current number of gold coins is " << centaur->GetCurrentNumberOfGoldCoins() << "." << endl;
	cout << GetNameOfEntity(centaur->GetEntityID()) << ": I'm dead!!" << endl;

}

void DeadKnackeredCentaur::Exit(Centaur* centaur){};//cout << GetNameOfEntity(centaur->GetEntityID()) << ": DeadKnackeredCentaur->Exit()" << endl;}

bool DeadKnackeredCentaur::HandleMessage(Centaur* centaur, const Telegram& message){return false;}
//-----------------------------------------------------------------------

//----------------------DownAndOutCentaur methods------------------------
DownAndOutCentaur* DownAndOutCentaur::Instance(){

	static DownAndOutCentaur instance;

	return &instance;

}

void DownAndOutCentaur::Enter(Centaur* centaur){

	//cout << GetNameOfEntity(centaur->GetEntityID()) << ": DownAndOutCentaur->Enter()" << endl;

	if(centaur->GetLocation() != Location::coldStreets){
		cout << GetNameOfEntity(centaur->GetEntityID()) << ": Guess I have to roam the streets now..." << endl;
		centaur->SetLocation(Location::coldStreets);
	}

}

void DownAndOutCentaur::Execute(Centaur* centaur){

	//cout << GetNameOfEntity(centaur->GetEntityID()) << ": DownAndOutCentaur->Execute()" << endl;
	cout << GetNameOfEntity(centaur->GetEntityID()) << ": Current number of gold coins is " << centaur->GetCurrentNumberOfGoldCoins() << "." << endl;
	cout << GetNameOfEntity(centaur->GetEntityID()) << ": I'm broke, thus it's game over for me!" << endl;

}

void DownAndOutCentaur::Exit(Centaur* centaur){};//cout << GetNameOfEntity(centaur->GetEntityID()) << ": DownAndOutCentaur->Exit()" << endl;}

bool DownAndOutCentaur::HandleMessage(Centaur* centaur, const Telegram& message){return false;}
//-----------------------------------------------------------------------

//----------------------GoToThePubCentaur methods------------------------
GoToThePubCentaur* GoToThePubCentaur::Instance(){

	static GoToThePubCentaur instance;

	return &instance;

}

void GoToThePubCentaur::Enter(Centaur* centaur){

	//cout << GetNameOfEntity(centaur->GetEntityID()) << ": GoToThePubCentaur->Enter()" << endl;

	if(centaur->GetLocation() != Location::pub){
		cout << GetNameOfEntity(centaur->GetEntityID()) << ": I better go to the pub and get a drink!" << endl;
		centaur->SetLocation(Location::pub);
	}

}

void GoToThePubCentaur::Execute(Centaur* centaur){

	//cout << GetNameOfEntity(centaur->GetEntityID()) << ": GoToThePubCentaur->Execute()" << endl;
	cout << GetNameOfEntity(centaur->GetEntityID()) << ": Current number of gold coins is " << centaur->GetCurrentNumberOfGoldCoins() << "." << endl;
	
	//Checks whether the centaur should play a round of poker.
	if(centaur->GetCurrentNumberOfGoldCoins() >= 5 && !centaur->HasPlayedAGameOfPoker()){
		cout << GetNameOfEntity(centaur->GetEntityID()) << ": I'm feeling lucky, prehaps I should give poker a try!" << endl;
		centaur->GetStateMachine()->ChangeState(PlayPokerCentaur::Instance());
		return;
	}

	//Updates the hasPlayedAGameOfPoker flag.
	if(centaur->HasPlayedAGameOfPoker())
		centaur->AlterHasPlayedAGameOfPokerFlag();

	//Checks whether the centaur has sufficient funds to buy a drink.
	if(centaur->GetCurrentNumberOfGoldCoins() >= 2){
		centaur->ReduceGoldCoins(2);
		centaur->GetStateMachine()->ChangeState(GrabADrinkCentaur::Instance());
	}
	else
		centaur->GetStateMachine()->ChangeState(DieFromDehydrationCentaur::Instance());

}

void GoToThePubCentaur::Exit(Centaur* centaur){};//cout << GetNameOfEntity(centaur->GetEntityID()) << ": GoToThePubCentaur->Exit()" << endl;}

bool GoToThePubCentaur::HandleMessage(Centaur* centaur, const Telegram& message){return false;}
//-----------------------------------------------------------------------

//----------------------GrabADrinkCentaur methods------------------------
GrabADrinkCentaur* GrabADrinkCentaur::Instance(){

	static GrabADrinkCentaur instance;

	return &instance;

}

void GrabADrinkCentaur::Enter(Centaur* centaur){};//cout << GetNameOfEntity(centaur->GetEntityID()) << ": GrabADrinkCentaur->Enter()" << endl;}

void GrabADrinkCentaur::Execute(Centaur* centaur){

	//cout << GetNameOfEntity(centaur->GetEntityID()) << ": GrabADrinkCentaur->Execute()" << endl;
	cout << GetNameOfEntity(centaur->GetEntityID()) << ": Current number of gold coins is " << centaur->GetCurrentNumberOfGoldCoins() << "." << endl;
	centaur->QuenchThirst();
	cout << GetNameOfEntity(centaur->GetEntityID()) << ": Ahhh, that was some fine liquid!" << endl;
	centaur->GetStateMachine()->ChangeState(ExploreDungeonCentaur::Instance());

}

void GrabADrinkCentaur::Exit(Centaur* centaur){};//cout << GetNameOfEntity(centaur->GetEntityID()) << ": GrabADrinkCentaur->Exit()" << endl;}

bool GrabADrinkCentaur::HandleMessage(Centaur* centaur, const Telegram& message){return false;}
//-----------------------------------------------------------------------

//-----------------------PlayPokerCentaur methods------------------------
PlayPokerCentaur* PlayPokerCentaur::Instance(){

	static PlayPokerCentaur instance;

	return &instance;

}

void PlayPokerCentaur::Enter(Centaur* centaur){};//cout << GetNameOfEntity(centaur->GetEntityID()) << ": PlayPokerCentaur->Enter()" << endl;}

void PlayPokerCentaur::Execute(Centaur* centaur){

	//cout << GetNameOfEntity(centaur->GetEntityID()) << ": PlayPokerCentaur->Execute()" << endl;
	cout << GetNameOfEntity(centaur->GetEntityID()) << ": Current number of gold coins is " << centaur->GetCurrentNumberOfGoldCoins() << "." << endl;

	double gameResult = RandomFloat();

	if(gameResult > 0.6f){
		centaur->AddGoldCoins(2);
		cout << GetNameOfEntity(centaur->GetEntityID()) << ": I've won the poker game!" << endl;
	}
	else{
		centaur->ReduceGoldCoins(1);
		cout << GetNameOfEntity(centaur->GetEntityID()) << ": I've lost the poker game!" << endl;
	}

	centaur->AlterHasPlayedAGameOfPokerFlag();
	centaur->GetStateMachine()->RevertToPreviousState();

}

void PlayPokerCentaur::Exit(Centaur* centaur){};//cout << GetNameOfEntity(centaur->GetEntityID()) << ": PlayPokerCentaur->Exit()" << endl;}

bool PlayPokerCentaur::HandleMessage(Centaur* centaur, const Telegram& message){return false;}
//-----------------------------------------------------------------------

//---------------------------GoToTheInn methods--------------------------
GoToTheInnCentaur* GoToTheInnCentaur::Instance(){

	static GoToTheInnCentaur instance;

	return &instance;

}

void GoToTheInnCentaur::Enter(Centaur* centaur){

	//cout << GetNameOfEntity(centaur->GetEntityID()) << ": GoToTheInnCentaur->Enter()" << endl;

	if(centaur->GetLocation() != Location::inn){
		cout << GetNameOfEntity(centaur->GetEntityID()) << ": I'm so tired! Heading towards the inn." << endl;
		centaur->SetLocation(Location::inn);
	}

}

void GoToTheInnCentaur::Execute(Centaur* centaur){

	//cout << GetNameOfEntity(centaur->GetEntityID()) << ": GoToTheInnCentaur->Execute()" << endl;
	cout << GetNameOfEntity(centaur->GetEntityID()) << ": Current number of gold coins is " << centaur->GetCurrentNumberOfGoldCoins() << "." << endl;
	cout << GetNameOfEntity(centaur->GetEntityID()) << ": It's a good opportunity to restock my arrows!" << endl;

	if(centaur->GetCurrentNumberOfGoldCoins() < 3)
		centaur->GetStateMachine()->ChangeState(DeadKnackeredCentaur::Instance());
	else{
		centaur->ReduceGoldCoins(3);
		centaur->RestockArrows();
		centaur->Sleep();
		cout << GetNameOfEntity(centaur->GetEntityID()) << ": Aaaa!! Such a lovely sleep..." << endl;
		cout << GetNameOfEntity(centaur->GetEntityID()) << ": Going back to the dungeon for more exploring!" << endl;
		centaur->GetStateMachine()->RevertToPreviousState();
	}

}

void GoToTheInnCentaur::Exit(Centaur* centaur){};//cout << GetNameOfEntity(centaur->GetEntityID()) << ": GoToTheInnCentaur->Exit()" << endl;}

bool GoToTheInnCentaur::HandleMessage(Centaur* centaur, const Telegram& message){return false;}
//-----------------------------------------------------------------------

//-----------------------GoToTheBeautySalon methods----------------------
GoToTheBeautySalon* GoToTheBeautySalon::Instance(){

	static GoToTheBeautySalon instance;

	return &instance;

}

void GoToTheBeautySalon::Enter(Centaur* centaur){

	//cout << GetNameOfEntity(centaur->GetEntityID()) << ": GoToTheBeautySalon->Enter()" << endl;

	if(centaur->GetLocation() != Location::beautySalon){
		cout << GetNameOfEntity(centaur->GetEntityID()) << ": My poor tail! I must tend to it immediately." << endl;
		centaur->SetLocation(Location::beautySalon);
	}

}

void GoToTheBeautySalon::Execute(Centaur* centaur){

	//cout << GetNameOfEntity(centaur->GetEntityID()) << ": GoToTheBeautySalon->Execute()" << endl;
	cout << GetNameOfEntity(centaur->GetEntityID()) << ": Current number of gold coins is " << centaur->GetCurrentNumberOfGoldCoins() << "." << endl;

	centaur->ReduceGoldCoins(2);
	centaur->GroomTail();
	cout << GetNameOfEntity(centaur->GetEntityID()) << ": Now that my tail is shiny once again, I can go back to adventuring!" << endl;
	centaur->GetStateMachine()->RevertToPreviousState();

}

void GoToTheBeautySalon::Exit(Centaur* centaur){};//cout << GetNameOfEntity(centaur->GetEntityID()) << ": GoToTheBeautySalon->Exit()" << endl;}

bool GoToTheBeautySalon::HandleMessage(Centaur* centaur, const Telegram& message){return false;}
//-----------------------------------------------------------------------