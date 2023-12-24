#include <iostream>

#include "DwarfOwnedStates.h"
#include "Dwarf.h"
#include "Locations.h"
#include "EntityNames.h"
#include "Auxiliary.h"

using std::cout;
using std::endl;

//------------------------DwarfsGlobalState methods----------------------
DwarfsGlobalState* DwarfsGlobalState::Instance(){

	static DwarfsGlobalState instance;

	return &instance;

}

void DwarfsGlobalState::Enter(Dwarf* dwarf){};//cout << GetNameOfEntity(dwarf->GetEntityID()) << ": DwarfsGlobalState->Enter()" << endl;}

void DwarfsGlobalState::Execute(Dwarf* dwarf){

	//cout << GetNameOfEntity(dwarf->GetEntityID()) << ": DwarfsGlobalState->Execute()" << endl;
	cout << GetNameOfEntity(dwarf->GetEntityID()) << ": Current number of gold coins is " << dwarf->GetCurrentNumberOfGoldCoins() << "." << endl;


	if(dwarf->DoesNeedASmoke() && dwarf->GetStateMachine()->IsInState(*ExploreDungeonDwarf::Instance())){
		dwarf->GetStateMachine()->ChangeState(GoToTheTobaccoShop::Instance());
		return;
	}

	if(dwarf->IsThirsty() && dwarf->GetStateMachine()->IsInState(*ExploreDungeonDwarf::Instance())){
		dwarf->GetStateMachine()->ChangeState(GoToThePubDwarf::Instance());
		return;
	}

	if(dwarf->IsDownAndOut() && dwarf->GetStateMachine()->IsInState(*ExploreDungeonDwarf::Instance())){
		dwarf->GetStateMachine()->ChangeState(DownAndOutDwarf::Instance());
		return;
	}

}

void DwarfsGlobalState::Exit(Dwarf* dwarf) {};//cout << GetNameOfEntity(dwarf->GetEntityID()) << ": DwarfsGlobalState->Exit()" << endl;}

bool DwarfsGlobalState::HandleMessage(Dwarf* dwarf, const Telegram& message){return false;}
//-----------------------------------------------------------------------

//----------------------ExploreDungeonDwarf methods----------------------
ExploreDungeonDwarf* ExploreDungeonDwarf::Instance(){

	static ExploreDungeonDwarf instance;

	return &instance;

}

void ExploreDungeonDwarf::Enter(Dwarf* dwarf){

	//cout << GetNameOfEntity(dwarf->GetEntityID()) << ": ExploreDungeonDwarf->Enter()" << endl;

	if(dwarf->GetLocation() != Location::dungeon){
		cout << GetNameOfEntity(dwarf->GetEntityID()) << ": Heading towards the dungeon!" << endl;
		dwarf->SetLocation(Location::dungeon);
	}

}

void ExploreDungeonDwarf::Execute(Dwarf* dwarf){

	//cout << GetNameOfEntity(dwarf->GetEntityID()) << ": ExploreDungeonDwarf->Execute()" << endl;
	cout << GetNameOfEntity(dwarf->GetEntityID()) << ": Current number of gold coins is " << dwarf->GetCurrentNumberOfGoldCoins() << "." << endl;

	double randomEvent = RandomFloat();

	if(randomEvent > 0.6f && randomEvent < 0.9f){
		dwarf->GetStateMachine()->ChangeState(BattleMonsterDwarf::Instance());
		return;
	}
	else if(randomEvent >= 0.9){
		dwarf->GetStateMachine()->ChangeState(OpenTreasureChestDwarf::Instance());
		return;
	}

	dwarf->IncreaseFatigue();
	cout << GetNameOfEntity(dwarf->GetEntityID()) << ": I sure am feeling the fatigue!" << endl;

	if(dwarf->IsFatigued())
		dwarf->GetStateMachine()->ChangeState(GoToTheInnDwarf::Instance());

}

void ExploreDungeonDwarf::Exit(Dwarf* dwarf){};//cout << GetNameOfEntity(dwarf->GetEntityID()) << ": ExploreDungeonDwarf->Exit()" << endl;}

bool ExploreDungeonDwarf::HandleMessage(Dwarf* dwarf, const Telegram& message){return false;}
//-----------------------------------------------------------------------

//----------------------BattleMonsterDwarf methods-----------------------
BattleMonsterDwarf* BattleMonsterDwarf::Instance(){

	static BattleMonsterDwarf instance;

	return &instance;

}

void BattleMonsterDwarf::Enter(Dwarf* dwarf){};//cout << GetNameOfEntity(dwarf->GetEntityID()) << ": BattleMonsterDwarf->Enter()" << endl;}

void BattleMonsterDwarf::Execute(Dwarf* dwarf){

	//cout << GetNameOfEntity(dwarf->GetEntityID()) << ": BattleMonsterDwarf->Execute()" << endl;
	cout << GetNameOfEntity(dwarf->GetEntityID()) << ": Current number of gold coins is " << dwarf->GetCurrentNumberOfGoldCoins() << "." << endl;

	int monster = 7;

	while(monster > 0 && !dwarf->IsDead()){
		//Checks whether the dwarf's axe is in a usable state.
		if(dwarf->IsAxeInAUsableState()){
			cout << GetNameOfEntity(dwarf->GetEntityID()) << ": I'm going to attack with my axe!" << endl;
			dwarf->UseAxe(&monster);
		}
		//The axe is in poor condition, therefore use a melee attack.
		else{
			cout << GetNameOfEntity(dwarf->GetEntityID()) << ": I'm about to use a melee attack!" << endl;
			dwarf->UseMelee(&monster);
		}
		//Checks whether the monster has been defeated.
		if(monster <= 0)
			continue;
		//The monster attacks the dwarf.
		int monsterDamage = RandomIntegerInRange(2, 4);
		cout << GetNameOfEntity(dwarf->GetEntityID()) << ": Monster attacks, causes " << monsterDamage << " damage." << endl;
		dwarf->DecreaseHealthPoints(monsterDamage);
		cout << GetNameOfEntity(dwarf->GetEntityID()) << ": battle status: dwarf's HP - " << dwarf->GetHealthPoints() << " monster's HP - " << monster << "." << endl;
	}

	//Checks whether the dwarf won or lost the battle.
	if(dwarf->IsDead()){
		dwarf->GetStateMachine()->ChangeState(DieDwarf::Instance());
	}
	else{
		cout << GetNameOfEntity(dwarf->GetEntityID()) << ": I've defeated the wicked monster!!" << endl;
		dwarf->AddGoldCoins(2);
		dwarf->RestoreHealthPoints();
		dwarf->GetStateMachine()->RevertToPreviousState();
	}

}

void BattleMonsterDwarf::Exit(Dwarf* dwarf){};//cout << GetNameOfEntity(dwarf->GetEntityID()) << ": BattleMonsterDwarf->Exit()" << endl;}

bool BattleMonsterDwarf::HandleMessage(Dwarf* dwarf, const Telegram& message){return false;}
//-----------------------------------------------------------------------

//----------------------OpenTreasureChestDwarf methods-------------------
OpenTreasureChestDwarf* OpenTreasureChestDwarf::Instance(){

	static OpenTreasureChestDwarf instance;

	return &instance;

}

void OpenTreasureChestDwarf::Enter(Dwarf* dwarf){};//cout << GetNameOfEntity(dwarf->GetEntityID()) << ": OpenTreasureChestDwarf->Enter()" << endl;}

void OpenTreasureChestDwarf::Execute(Dwarf* dwarf){

	//cout << GetNameOfEntity(dwarf->GetEntityID()) << ": OpenTreasureChestDwarf->Execute()" << endl;
	cout << GetNameOfEntity(dwarf->GetEntityID()) << ": Current number of gold coins is " << dwarf->GetCurrentNumberOfGoldCoins() << "." << endl;
	cout << GetNameOfEntity(dwarf->GetEntityID()) << ": Oh lovely!! I found myself a treasure chest!" << endl;
	dwarf->AddGoldCoins(3);
	dwarf->GetStateMachine()->RevertToPreviousState();

}

void OpenTreasureChestDwarf::Exit(Dwarf* dwarf){};//cout << GetNameOfEntity(dwarf->GetEntityID()) << ": OpenTreasureChestDwarf->Exit()" << endl;}

bool OpenTreasureChestDwarf::HandleMessage(Dwarf* dwarf, const Telegram& message){return false;}
//-----------------------------------------------------------------------

//------------------------------DieDwarf methods-------------------------
DieDwarf* DieDwarf::Instance(){

	static DieDwarf instance;

	return &instance;

}

void DieDwarf::Enter(Dwarf* dwarf){

	//cout << GetNameOfEntity(dwarf->GetEntityID()) << ": DieDwarf->Enter()" << endl;

	if(dwarf->GetLocation() != Location::cemetery){
		cout << GetNameOfEntity(dwarf->GetEntityID()) << ": Oh no!! I'm dying!" << endl;
		dwarf->SetLocation(Location::cemetery);
	}

}

void DieDwarf::Execute(Dwarf* dwarf){

	//cout << GetNameOfEntity(dwarf->GetEntityID()) << ": DieDwarf->Execute()" << endl;
	cout << GetNameOfEntity(dwarf->GetEntityID()) << ": Current number of gold coins is " << dwarf->GetCurrentNumberOfGoldCoins() << "." << endl;
	cout << GetNameOfEntity(dwarf->GetEntityID()) << ": I'm dead!!" << endl;

}

void DieDwarf::Exit(Dwarf* dwarf){};//cout << GetNameOfEntity(dwarf->GetEntityID()) << ": DieDwarf->Exit()" << endl;}

bool DieDwarf::HandleMessage(Dwarf* dwarf, const Telegram& message){return false;}
//-----------------------------------------------------------------------

//----------------------DieFromDehydrationDwarf methods------------------
DieFromDehydrationDwarf* DieFromDehydrationDwarf::Instance(){

	static DieFromDehydrationDwarf instance;

	return &instance;

}

void DieFromDehydrationDwarf::Enter(Dwarf* dwarf){

	//cout << GetNameOfEntity(dwarf->GetEntityID()) << ": DieFromDehydrationDwarf->Enter()" << endl;

	if(dwarf->GetLocation() != Location::cemetery){
		cout << GetNameOfEntity(dwarf->GetEntityID()) << ": Oh no!! I'm dying!" << endl;
		dwarf->SetLocation(Location::cemetery);
	}

}

void DieFromDehydrationDwarf::Execute(Dwarf* dwarf){

	//cout << GetNameOfEntity(dwarf->GetEntityID()) << ": DieFromDehydrationDwarf->Execute()" << endl;
	cout << GetNameOfEntity(dwarf->GetEntityID()) << ": Current number of gold coins is " << dwarf->GetCurrentNumberOfGoldCoins() << "." << endl;
	cout << GetNameOfEntity(dwarf->GetEntityID()) << ": I'm dead!!" << endl;

}

void DieFromDehydrationDwarf::Exit(Dwarf* dwarf){};//cout << GetNameOfEntity(dwarf->GetEntityID()) << ": DieFromDehydrationDwarf->Exit()" << endl;}

bool DieFromDehydrationDwarf::HandleMessage(Dwarf* dwarf, const Telegram& message){return false;}
//-----------------------------------------------------------------------

//------------------------DeadKnackeredDwarf methods---------------------
DeadKnackeredDwarf* DeadKnackeredDwarf::Instance(){

	static DeadKnackeredDwarf instance;

	return &instance;

}

void DeadKnackeredDwarf::Enter(Dwarf* dwarf){

	//cout << GetNameOfEntity(dwarf->GetEntityID()) << ": DeadKnackeredDwarf->Enter()" << endl;

	if(dwarf->GetLocation() != Location::cemetery){
		cout << GetNameOfEntity(dwarf->GetEntityID()) << ": Oh no!! I'm dying from exhaustion!" << endl;
		dwarf->SetLocation(Location::cemetery);
	}

}

void DeadKnackeredDwarf::Execute(Dwarf* dwarf){

	//cout << GetNameOfEntity(dwarf->GetEntityID()) << ": DeadKnackeredDwarf->Execute()" << endl;
	cout << GetNameOfEntity(dwarf->GetEntityID()) << ": Current number of gold coins is " << dwarf->GetCurrentNumberOfGoldCoins() << "." << endl;
	cout << GetNameOfEntity(dwarf->GetEntityID()) << ": I'm dead!!" << endl;

}

void DeadKnackeredDwarf::Exit(Dwarf* dwarf){};//cout << GetNameOfEntity(dwarf->GetEntityID()) << ": DeadKnackeredDwarf->Exit()" << endl;}

bool DeadKnackeredDwarf::HandleMessage(Dwarf* dwarf, const Telegram& message){return false;}
//-----------------------------------------------------------------------

//-----------------------DownAndOutDwarf methods-------------------------
DownAndOutDwarf* DownAndOutDwarf::Instance(){

	static DownAndOutDwarf instance;

	return &instance;

}

void DownAndOutDwarf::Enter(Dwarf* dwarf){

	//cout << GetNameOfEntity(dwarf->GetEntityID()) << ": DownAndOutDwarf->Enter()" << endl;

	if(dwarf->GetLocation() != Location::coldStreets){
		cout << GetNameOfEntity(dwarf->GetEntityID()) << ": Guess I have to roam the streets now..." << endl;
		dwarf->SetLocation(Location::coldStreets);
	}

}

void DownAndOutDwarf::Execute(Dwarf* dwarf){

	//cout << GetNameOfEntity(dwarf->GetEntityID()) << ": DownAndOutDwarf->Execute()" << endl;
	cout << GetNameOfEntity(dwarf->GetEntityID()) << ": Current number of gold coins is " << dwarf->GetCurrentNumberOfGoldCoins() << "." << endl;
	cout << GetNameOfEntity(dwarf->GetEntityID()) << ": I'm broke, thus it's game over for me!" << endl;

}

void DownAndOutDwarf::Exit(Dwarf* dwarf){};//cout << GetNameOfEntity(dwarf->GetEntityID()) << ": DownAndOutDwarf->Exit()" << endl;}

bool DownAndOutDwarf::HandleMessage(Dwarf* dwarf, const Telegram& message){return false;}
//-----------------------------------------------------------------------

//-----------------------GoToThePubDwarf methods-------------------------
GoToThePubDwarf* GoToThePubDwarf::Instance(){

	static GoToThePubDwarf instance;

	return &instance;

}

void GoToThePubDwarf::Enter(Dwarf* dwarf){

	//cout << GetNameOfEntity(dwarf->GetEntityID()) << ": GoToThePubDwarf->Enter()" << endl;

	if(dwarf->GetLocation() != Location::pub){
		cout << GetNameOfEntity(dwarf->GetEntityID()) << ": I better go to the pub and grab a drink!" << endl;
		dwarf->SetLocation(Location::pub);
	}

}

void GoToThePubDwarf::Execute(Dwarf* dwarf){

	//cout << GetNameOfEntity(dwarf->GetEntityID()) << ": GoToThePubDwarf->Execute()" << endl;
	cout << GetNameOfEntity(dwarf->GetEntityID()) << ": Current number of gold coins is " << dwarf->GetCurrentNumberOfGoldCoins() << "." << endl;
	
	//Checks whether the dwarf should play a round of poker.
	if(dwarf->GetCurrentNumberOfGoldCoins() >= 5 && !dwarf->HasPlayedAGameOfPoker()){
		cout << GetNameOfEntity(dwarf->GetEntityID()) << ": I'm feeling lucky, prehaps I should give poker a try!" << endl;
		dwarf->GetStateMachine()->ChangeState(PlayPokerDwarf::Instance());
		return;
	}

	//Updates the hasPlayedAGameOfPoker flag.
	if(dwarf->HasPlayedAGameOfPoker())
		dwarf->AlterHasPlayedAGameOfPokerFlag();

	//Checks whether the dwarf has sufficient funds to buy a drink.
	if(dwarf->GetCurrentNumberOfGoldCoins() >= 2){
		dwarf->ReduceGoldCoins(2);
		dwarf->GetStateMachine()->ChangeState(GrabADrinkDwarf::Instance());
	}
	else
		dwarf->GetStateMachine()->ChangeState(DieFromDehydrationDwarf::Instance());

}

void GoToThePubDwarf::Exit(Dwarf* dwarf){};//cout << GetNameOfEntity(dwarf->GetEntityID()) << ": GoToThePubDwarf->Exit()" << endl;}

bool GoToThePubDwarf::HandleMessage(Dwarf* dwarf, const Telegram& message){return false;}
//-----------------------------------------------------------------------

//-----------------------GrabADrinkDwarf methods-------------------------
GrabADrinkDwarf* GrabADrinkDwarf::Instance(){

	static GrabADrinkDwarf instance;

	return &instance;

}

void GrabADrinkDwarf::Enter(Dwarf* dwarf){};//cout << GetNameOfEntity(dwarf->GetEntityID()) << ": GrabADrinkDwarf->Enter()" << endl;}

void GrabADrinkDwarf::Execute(Dwarf* dwarf){

	//cout << GetNameOfEntity(dwarf->GetEntityID()) << ": GrabADrinkDwarf->Execute()" << endl;
	cout << GetNameOfEntity(dwarf->GetEntityID()) << ": Current number of gold coins is " << dwarf->GetCurrentNumberOfGoldCoins() << "." << endl;
	dwarf->QuenchThirst();
	cout << GetNameOfEntity(dwarf->GetEntityID()) << ": Ahhh, that was some fine liquid!" << endl;
	dwarf->GetStateMachine()->ChangeState(ExploreDungeonDwarf::Instance());

}

void GrabADrinkDwarf::Exit(Dwarf* dwarf){};//cout << GetNameOfEntity(dwarf->GetEntityID()) << ": GrabADrinkDwarf->Exit()" << endl;}

bool GrabADrinkDwarf::HandleMessage(Dwarf* dwarf, const Telegram& message){return false;}
//-----------------------------------------------------------------------

//------------------------PlayPokerDwarf methods-------------------------
PlayPokerDwarf* PlayPokerDwarf::Instance(){

	static PlayPokerDwarf instance;

	return &instance;

}

void PlayPokerDwarf::Enter(Dwarf* dwarf){};//cout << GetNameOfEntity(dwarf->GetEntityID()) << ": PlayPokerDwarf->Enter()" << endl;}

void PlayPokerDwarf::Execute(Dwarf* dwarf){

	//cout << GetNameOfEntity(dwarf->GetEntityID()) << ": PlayPokerDwarf->Execute()" << endl;
	cout << GetNameOfEntity(dwarf->GetEntityID()) << ": Current number of gold coins is " << dwarf->GetCurrentNumberOfGoldCoins() << "." << endl;

	double gameResult = RandomFloat();

	if(gameResult > 0.6f){
		dwarf->AddGoldCoins(2);
		cout << GetNameOfEntity(dwarf->GetEntityID()) << ": I've won the poker game!" << endl;
	}
	else{
		dwarf->ReduceGoldCoins(1);
		cout << GetNameOfEntity(dwarf->GetEntityID()) << ": I've lost the poker game!" << endl;
	}

	dwarf->AlterHasPlayedAGameOfPokerFlag();
	dwarf->GetStateMachine()->RevertToPreviousState();

}

void PlayPokerDwarf::Exit(Dwarf* dwarf){};//cout << GetNameOfEntity(dwarf->GetEntityID()) << ": PlayPokerDwarf->Exit()" << endl;}

bool PlayPokerDwarf::HandleMessage(Dwarf* dwarf, const Telegram& message){return false;}
//-----------------------------------------------------------------------

//------------------------GoToTheInnDwarf methods------------------------
GoToTheInnDwarf* GoToTheInnDwarf::Instance(){

	static GoToTheInnDwarf instance;

	return &instance;

}

void GoToTheInnDwarf::Enter(Dwarf* dwarf){

	//cout << GetNameOfEntity(dwarf->GetEntityID()) << ": GoToTheInnDwarf->Enter()" << endl;

	if(dwarf->GetLocation() != Location::inn){
		cout << GetNameOfEntity(dwarf->GetEntityID()) << ": I'm so tired! Heading towards the inn." << endl;
		dwarf->SetLocation(Location::inn);
	}

}

void GoToTheInnDwarf::Execute(Dwarf* dwarf){

	//cout << GetNameOfEntity(dwarf->GetEntityID()) << ": GoToTheInnDwarf->Execute()" << endl;
	cout << GetNameOfEntity(dwarf->GetEntityID()) << ": Current number of gold coins is " << dwarf->GetCurrentNumberOfGoldCoins() << "." << endl;
	cout << GetNameOfEntity(dwarf->GetEntityID()) << ": It's a good opportunity to repair my axe!" << endl;

	if(dwarf->GetCurrentNumberOfGoldCoins() < 3)
		dwarf->GetStateMachine()->ChangeState(DeadKnackeredDwarf::Instance());
	else{
		dwarf->ReduceGoldCoins(3);
		dwarf->RepairAxe();
		dwarf->Sleep();
		cout << GetNameOfEntity(dwarf->GetEntityID()) << ": Aaaa!! Such a lovely sleep..." << endl;
		cout << GetNameOfEntity(dwarf->GetEntityID()) << ": Going back to the dungeon for more exploring!" << endl;
		dwarf->GetStateMachine()->RevertToPreviousState();
	}

}

void GoToTheInnDwarf::Exit(Dwarf* dwarf){};//cout << GetNameOfEntity(dwarf->GetEntityID()) << ": GoToTheInnDwarf->Exit()" << endl;}

bool GoToTheInnDwarf::HandleMessage(Dwarf* dwarf, const Telegram& message){return false;}
//-----------------------------------------------------------------------

//-----------------------GoToTheTobaccoShop methods----------------------
GoToTheTobaccoShop* GoToTheTobaccoShop::Instance(){

	static GoToTheTobaccoShop instance;

	return &instance;

}

void GoToTheTobaccoShop::Enter(Dwarf* dwarf){

	//cout << GetNameOfEntity(dwarf->GetEntityID()) << ": GoToTheTobaccoShop->Enter()" << endl;

	if(dwarf->GetLocation() != Location::tobaccoShop){
		cout << GetNameOfEntity(dwarf->GetEntityID()) << ": I really could use a cigar right now." << endl;
		dwarf->SetLocation(Location::tobaccoShop);
	}

}

void GoToTheTobaccoShop::Execute(Dwarf* dwarf){

	//cout << GetNameOfEntity(dwarf->GetEntityID()) << ": GoToTheTobaccoShop->Execute()" << endl;
	cout << GetNameOfEntity(dwarf->GetEntityID()) << ": Current number of gold coins is " << dwarf->GetCurrentNumberOfGoldCoins() << "." << endl;

	dwarf->ReduceGoldCoins(2);
	dwarf->SmokeCigar();
	cout << GetNameOfEntity(dwarf->GetEntityID()) << ": Now that I had my smoke, I can go back to adventuring!" << endl;
	dwarf->GetStateMachine()->RevertToPreviousState();

}

void GoToTheTobaccoShop::Exit(Dwarf* dwarf){};//cout << GetNameOfEntity(dwarf->GetEntityID()) << ": GoToTheTobaccoShop->Exit()" << endl;}

bool GoToTheTobaccoShop::HandleMessage(Dwarf* dwarf, const Telegram& message){return false;}
//-----------------------------------------------------------------------