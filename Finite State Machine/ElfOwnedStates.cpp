#include <iostream>

#include "ElfOwnedStates.h"
#include "Elf.h"
#include "Locations.h"
#include "EntityNames.h"
#include "Auxiliary.h"

using std::cout;
using std::endl;

//-------------------------ElfsGlobalState methods-----------------------
ElfsGlobalState* ElfsGlobalState::Instance(){

	static ElfsGlobalState instance;

	return &instance;

}

void ElfsGlobalState::Enter(Elf* elf){};//cout << GetNameOfEntity(elf->GetEntityID()) << ": ElfsGlobalState->Enter()" << endl;}

void ElfsGlobalState::Execute(Elf* elf){

	//cout << GetNameOfEntity(elf->GetEntityID()) << ": ElfsGlobalState->Execute()" << endl;
	cout << GetNameOfEntity(elf->GetEntityID()) << ": Current number of gold coins is " << elf->GetCurrentNumberOfGoldCoins() << "." << endl;

	if(elf->IsBored() && elf->GetStateMachine()->IsInState(*ExploreDungeonElf::Instance())){
		elf->GetStateMachine()->ChangeState(GoToTheLibrary::Instance());
		return;
	}

	if(elf->IsThirsty() && elf->GetStateMachine()->IsInState(*ExploreDungeonElf::Instance())){
		elf->GetStateMachine()->ChangeState(GoToThePubElf::Instance());
		return;
	}

	if(elf->IsDownAndOut() && elf->GetStateMachine()->IsInState(*ExploreDungeonElf::Instance())){
		elf->GetStateMachine()->ChangeState(DownAndOutElf::Instance());
		return;
	}

}

void ElfsGlobalState::Exit(Elf* elf){};//cout << GetNameOfEntity(elf->GetEntityID()) << ": ElfsGlobalState->Exit()" << endl;}

bool ElfsGlobalState::HandleMessage(Elf* elf, const Telegram& message){return false;}
//-----------------------------------------------------------------------

//------------------------ExploreDungeonElf methods----------------------
ExploreDungeonElf* ExploreDungeonElf::Instance(){

	static ExploreDungeonElf instance;

	return &instance;

}

void ExploreDungeonElf::Enter(Elf* elf){

	//cout << GetNameOfEntity(elf->GetEntityID()) << ": ExploreDungeonElf->Enter()" << endl;

	if(elf->GetLocation() != Location::dungeon){
		cout << GetNameOfEntity(elf->GetEntityID()) << ": Heading towards the dungeon!" << endl;
		elf->SetLocation(Location::dungeon);
	}

}

void ExploreDungeonElf::Execute(Elf* elf){

	//cout << GetNameOfEntity(elf->GetEntityID()) << ": ExploreDungeonElf->Execute()" << endl;
	cout << GetNameOfEntity(elf->GetEntityID()) << ": Current number of gold coins is " << elf->GetCurrentNumberOfGoldCoins() << "." << endl;

	double randomEvent = RandomFloat();

	if(randomEvent > 0.6f && randomEvent < 0.9f){
		elf->GetStateMachine()->ChangeState(BattleMonsterElf::Instance());
		return;
	}
	else if(randomEvent >= 0.9){
		elf->GetStateMachine()->ChangeState(OpenTreasureChestElf::Instance());
		return;
	}

	elf->IncreaseFatigue();
	cout << GetNameOfEntity(elf->GetEntityID()) << ": I sure am feeling the fatigue!" << endl;

	if(elf->IsFatigued())
		elf->GetStateMachine()->ChangeState(GoToTheInnElf::Instance());

}

void ExploreDungeonElf::Exit(Elf* elf){};//cout << GetNameOfEntity(elf->GetEntityID()) << ": ExploreDungeonElf->Exit()" << endl;}

bool ExploreDungeonElf::HandleMessage(Elf* elf, const Telegram& message){return false;}
//-----------------------------------------------------------------------

//-----------------------BattleMonsterElf methods------------------------
BattleMonsterElf* BattleMonsterElf::Instance(){

	static BattleMonsterElf instance;

	return &instance;

}

void BattleMonsterElf::Enter(Elf* elf){};//cout << GetNameOfEntity(elf->GetEntityID()) << ": BattleMonsterElf->Enter()" << endl;}

void BattleMonsterElf::Execute(Elf* elf){
	
	//cout << GetNameOfEntity(elf->GetEntityID()) << ": BattleMonsterElf->Execute()" << endl;
	cout << GetNameOfEntity(elf->GetEntityID()) << ": Current number of gold coins is " << elf->GetCurrentNumberOfGoldCoins() << "." << endl;

	int monster = 7;

	while(monster > 0 && !elf->IsDead()){
		//Checks whether the elf has enough MP to use a spell.
		if(elf->GetManaPoints() >= 2){
			cout << GetNameOfEntity(elf->GetEntityID()) << ": I'm about to cast an offensive spell!" << endl;
			elf->UseSpell(&monster);
		}
		//There is no enough mana points to use magic, therefore use a melee attack.
		else{
			cout << GetNameOfEntity(elf->GetEntityID()) << ": I'm about to use a melee attack!" << endl;
			elf->UseMelee(&monster);
		}
		//Checks whether the monster has been defeated.
		if(monster <= 0)
			continue;
		//The monster attacks the elf.
		int monsterDamage = RandomIntegerInRange(2, 4);
		cout << GetNameOfEntity(elf->GetEntityID()) << ": Monster attacks, causes " << monsterDamage << " damage." << endl;
		elf->DecreaseHealthPoints(monsterDamage);
		cout << GetNameOfEntity(elf->GetEntityID()) << ": battle status: elf's HP - " << elf->GetHealthPoints() << " monster's HP - " << monster << "." << endl;
	}
	
	//Checks whether the elf won or lost the battle.
	if(elf->IsDead())
		elf->GetStateMachine()->ChangeState(DieElf::Instance());
	else{
		cout << GetNameOfEntity(elf->GetEntityID()) << ": I've defeated the wicked monster!!" << endl;
		elf->AddGoldCoins(2);
		elf->RestoreHealthPoints();
		elf->GetStateMachine()->RevertToPreviousState();
	}

}

void BattleMonsterElf::Exit(Elf* elf){};//cout << GetNameOfEntity(elf->GetEntityID()) << ": BattleMonsterElf->Exit()" << endl;}

bool BattleMonsterElf::HandleMessage(Elf* elf, const Telegram& message){return false;}
//-----------------------------------------------------------------------

//-----------------------OpenTreasureChestElf methods--------------------
OpenTreasureChestElf* OpenTreasureChestElf::Instance(){

	static OpenTreasureChestElf instance;

	return &instance;

}

void OpenTreasureChestElf::Enter(Elf* elf){};//cout << GetNameOfEntity(elf->GetEntityID()) << ": OpenTreasureChestElf->Enter()" << endl;}

void OpenTreasureChestElf::Execute(Elf* elf){

	//cout << GetNameOfEntity(elf->GetEntityID()) << ": OpenTreasureChestElf->Execute()" << endl;
	cout << GetNameOfEntity(elf->GetEntityID()) << ": Current number of gold coins is " << elf->GetCurrentNumberOfGoldCoins() << "." << endl;
	cout << GetNameOfEntity(elf->GetEntityID()) << ": Oh, lovely!! I found myself a treasure chest!" << endl;
	elf->AddGoldCoins(3);
	elf->GetStateMachine()->RevertToPreviousState();

}

void OpenTreasureChestElf::Exit(Elf* elf){};//cout << GetNameOfEntity(elf->GetEntityID()) << ": OpenTreasureChestElf->Exit()" << endl;}

bool OpenTreasureChestElf::HandleMessage(Elf* elf, const Telegram& message){return false;}
//-----------------------------------------------------------------------

//-------------------------------DieElf methods--------------------------
DieElf* DieElf::Instance(){

	static DieElf instance;

	return &instance;

}

void DieElf::Enter(Elf* elf){

	//cout << GetNameOfEntity(elf->GetEntityID()) << ": DieElf->Enter()" << endl;

	if(elf->GetLocation() != Location::cemetery){
		cout << GetNameOfEntity(elf->GetEntityID()) << ": Oh no!! I'm dying!" << endl;
		elf->SetLocation(Location::cemetery);
	}

}

void DieElf::Execute(Elf* elf){

	//cout << GetNameOfEntity(elf->GetEntityID()) << ": DieElf->Execute()" << endl;
	cout << GetNameOfEntity(elf->GetEntityID()) << ": Current number of gold coins is " << elf->GetCurrentNumberOfGoldCoins() << "." << endl;
	cout << GetNameOfEntity(elf->GetEntityID()) << ": I'm dead!!" << endl;

}

void DieElf::Exit(Elf* elf){};//cout << GetNameOfEntity(elf->GetEntityID()) << ": DieElf->Exit()" << endl;}

bool DieElf::HandleMessage(Elf* elf, const Telegram& message){return false;}
//-----------------------------------------------------------------------

//-----------------------DieFromDehydrationElf methods-------------------
DieFromDehydrationElf* DieFromDehydrationElf::Instance(){

	static DieFromDehydrationElf instance;

	return &instance;

}

void DieFromDehydrationElf::Enter(Elf* elf){

	//cout << GetNameOfEntity(elf->GetEntityID()) << ": DieFromDehydrationElf->Enter()" << endl;

	if(elf->GetLocation() != Location::cemetery){
		cout << GetNameOfEntity(elf->GetEntityID()) << ": Oh no!! I'm dying from dehydration!" << endl;
		elf->SetLocation(Location::cemetery);
	}

}

void DieFromDehydrationElf::Execute(Elf* elf){

	//cout << GetNameOfEntity(elf->GetEntityID()) << ": DieFromDehydrationElf->Execute()" << endl;
	cout << GetNameOfEntity(elf->GetEntityID()) << ": Current number of gold coins is " << elf->GetCurrentNumberOfGoldCoins() << "." << endl;
	cout << GetNameOfEntity(elf->GetEntityID()) << ": I'm dead!!" << endl;

}

void DieFromDehydrationElf::Exit(Elf* elf){};//cout << GetNameOfEntity(elf->GetEntityID()) << ": DieFromDehydrationElf->Exit()" << endl;}

bool DieFromDehydrationElf::HandleMessage(Elf* elf, const Telegram& message){return false;}
//-----------------------------------------------------------------------

//-------------------------DeadKnackeredElf methods----------------------
DeadKnackeredElf* DeadKnackeredElf::Instance(){

	static DeadKnackeredElf instance;

	return &instance;

}

void DeadKnackeredElf::Enter(Elf* elf){

	//cout << GetNameOfEntity(elf->GetEntityID()) << ": DeadKnackeredElf->Enter()" << endl;

	if(elf->GetLocation() != Location::cemetery){
		cout << GetNameOfEntity(elf->GetEntityID()) << ": Oh no!! I'm dying from exhaustion!" << endl;
		elf->SetLocation(Location::cemetery);
	}

}

void DeadKnackeredElf::Execute(Elf* elf){

	//cout << GetNameOfEntity(elf->GetEntityID()) << ": DeadKnackeredElf->Execute()" << endl;
	cout << GetNameOfEntity(elf->GetEntityID()) << ": Current number of gold coins is " << elf->GetCurrentNumberOfGoldCoins() << "." << endl;
	cout << GetNameOfEntity(elf->GetEntityID()) << ": I'm dead!!" << endl;

}

void DeadKnackeredElf::Exit(Elf* elf){};//cout << GetNameOfEntity(elf->GetEntityID()) << ": DeadKnackeredElf->Exit()" << endl;}

bool DeadKnackeredElf::HandleMessage(Elf* elf, const Telegram& message){return false;}
//-----------------------------------------------------------------------

//------------------------DownAndOutElf methods--------------------------
DownAndOutElf* DownAndOutElf::Instance(){

	static DownAndOutElf instance;

	return &instance;

}

void DownAndOutElf::Enter(Elf* elf){

	//cout << GetNameOfEntity(elf->GetEntityID()) << ": DownAndOutElf->Enter()" << endl;

	if(elf->GetLocation() != Location::coldStreets){
		cout << GetNameOfEntity(elf->GetEntityID()) << ": Guess I have to roam the streets now..." << endl;
		elf->SetLocation(Location::coldStreets);
	}

}

void DownAndOutElf::Execute(Elf* elf){

	//cout << GetNameOfEntity(elf->GetEntityID()) << ": DownAndOutElf->Execute()" << endl;
	cout << GetNameOfEntity(elf->GetEntityID()) << ": Current number of gold coins is " << elf->GetCurrentNumberOfGoldCoins() << "." << endl;
	cout << GetNameOfEntity(elf->GetEntityID()) << ": I'm broke, thus it's game over for me!" << endl;

}

void DownAndOutElf::Exit(Elf* elf){};//cout << GetNameOfEntity(elf->GetEntityID()) << ": DownAndOutElf->Exit()" << endl;}

bool DownAndOutElf::HandleMessage(Elf* elf, const Telegram& message){return false;}
//-----------------------------------------------------------------------

//------------------------GoToThePubElf methods--------------------------
GoToThePubElf* GoToThePubElf::Instance(){

	static GoToThePubElf instance;

	return &instance;

}

void GoToThePubElf::Enter(Elf* elf){

	//cout << GetNameOfEntity(elf->GetEntityID()) << ": GoToThePubElf->Enter()" << endl;

	if(elf->GetLocation() != Location::pub){
		cout << GetNameOfEntity(elf->GetEntityID()) << ": I better go to the pub and grab a drink!" << endl;
		elf->SetLocation(Location::pub);
	}

}

void GoToThePubElf::Execute(Elf* elf){

	//cout << GetNameOfEntity(elf->GetEntityID()) << ": GoToThePubElf->Execute()" << endl;
	cout << GetNameOfEntity(elf->GetEntityID()) << ": Current number of gold coins is " << elf->GetCurrentNumberOfGoldCoins() << "." << endl;

	//Checks whether the elf should play a round of poker.
	if(elf->GetCurrentNumberOfGoldCoins() >= 5 && !elf->HasPlayedAGameOfPoker()){
		cout << GetNameOfEntity(elf->GetEntityID()) << ": I'm feeling lucky, prehaps I should give poker a try!" << endl;
		elf->GetStateMachine()->ChangeState(PlayPokerElf::Instance());
		return;
	}

	//Updates the hasPlayedAGameOfPoker flag.
	if(elf->HasPlayedAGameOfPoker())
		elf->AlterHasPlayedAGameOfPokerFlag();
    
	//Checks whether the elf has sufficient funds to buy a drink.
	if(elf->GetCurrentNumberOfGoldCoins() >= 2){
		elf->ReduceGoldCoins(2);
		elf->GetStateMachine()->ChangeState(GrabADrinkElf::Instance());
	}
	else
		elf->GetStateMachine()->ChangeState(DieFromDehydrationElf::Instance());

}

void GoToThePubElf::Exit(Elf* elf){};//cout << GetNameOfEntity(elf->GetEntityID()) << ": GoToThePubElf->Exit()" << endl;}

bool GoToThePubElf::HandleMessage(Elf* elf, const Telegram& message){return false;}
//-----------------------------------------------------------------------

//------------------------GrabADrinkElf methods--------------------------
GrabADrinkElf* GrabADrinkElf::Instance(){

	static GrabADrinkElf instance;

	return &instance;

}

void GrabADrinkElf::Enter(Elf* elf){};//cout << GetNameOfEntity(elf->GetEntityID()) << ": GrabADrinkElf->Enter()" << endl;}

void GrabADrinkElf::Execute(Elf* elf){

	//cout << GetNameOfEntity(elf->GetEntityID()) << ": GrabADrinkElf->Execute()" << endl;
	cout << GetNameOfEntity(elf->GetEntityID()) << ": Current number of gold coins is " << elf->GetCurrentNumberOfGoldCoins() << "." << endl;
	elf->QuenchThirst();
	cout << GetNameOfEntity(elf->GetEntityID()) << ": Ahhh, that was some fine liquid!" << endl;
	elf->GetStateMachine()->ChangeState(ExploreDungeonElf::Instance());

}

void GrabADrinkElf::Exit(Elf* elf){};//cout << GetNameOfEntity(elf->GetEntityID()) << ": GrabADrinkElf->Exit()" << endl;}

bool GrabADrinkElf::HandleMessage(Elf* elf, const Telegram& message){return false;}
//-----------------------------------------------------------------------

//-------------------------PlayPokerElf methods--------------------------
PlayPokerElf* PlayPokerElf::Instance(){

	static PlayPokerElf instance;

	return &instance;

}

void PlayPokerElf::Enter(Elf* elf){};//cout << GetNameOfEntity(elf->GetEntityID()) << ": PlayPokerElf->Enter()" << endl;}

void PlayPokerElf::Execute(Elf* elf){

	//cout << GetNameOfEntity(elf->GetEntityID()) << ": PlayPokerElf->Execute()" << endl;
	cout << GetNameOfEntity(elf->GetEntityID()) << ": Current number of gold coins iis " << elf->GetCurrentNumberOfGoldCoins() << "." << endl;

	double gameResult = RandomFloat();

	if(gameResult > 0.6f){
		elf->AddGoldCoins(2);
		cout << GetNameOfEntity(elf->GetEntityID()) << ": I've won the poker game!" << endl;
	}
	else{
		elf->ReduceGoldCoins(1);
		cout << GetNameOfEntity(elf->GetEntityID()) << ": I've lost the poker game!" << endl;
	}

	elf->AlterHasPlayedAGameOfPokerFlag();
	elf->GetStateMachine()->RevertToPreviousState();

}

void PlayPokerElf::Exit(Elf* elf){};//cout << GetNameOfEntity(elf->GetEntityID()) << ": PlayPokerElf->Exit()" << endl;}

bool PlayPokerElf::HandleMessage(Elf* elf, const Telegram& message){return false;}
//-----------------------------------------------------------------------

//-------------------------GoToTheInnElf methods-------------------------
GoToTheInnElf* GoToTheInnElf::Instance(){

	static GoToTheInnElf instance;

	return &instance;

}

void GoToTheInnElf::Enter(Elf* elf){

	//cout << GetNameOfEntity(elf->GetEntityID()) << ": GoToTheInnElf->Enter()" << endl;
	
	if(elf->GetLocation() != Location::inn){
		cout << GetNameOfEntity(elf->GetEntityID()) << ": I'm so tired! Heading towards the inn." << endl;
		elf->SetLocation(Location::inn);
	}

}

void GoToTheInnElf::Execute(Elf* elf){

	//cout << GetNameOfEntity(elf->GetEntityID()) << ": GoToTheInnElf->Execute()" << endl;
	cout << GetNameOfEntity(elf->GetEntityID()) << ": Current number of gold coins is " << elf->GetCurrentNumberOfGoldCoins() << "." << endl;

	if(elf->GetCurrentNumberOfGoldCoins() < 3)
		elf->GetStateMachine()->ChangeState(DeadKnackeredElf::Instance());
	else{
		elf->ReduceGoldCoins(3);
		elf->RestoreManaPoints();
		elf->Sleep();
		cout << GetNameOfEntity(elf->GetEntityID()) << ": Aaaa!! Such a lovely sleep..." << endl;
		cout << GetNameOfEntity(elf->GetEntityID()) << ": Going back to the dungeon for more exploring!" << endl;
		elf->GetStateMachine()->RevertToPreviousState();
	}
	
}

void GoToTheInnElf::Exit(Elf* elf){};//cout << GetNameOfEntity(elf->GetEntityID()) << ": GoToTheInnElf->Exit()" << endl;}

bool GoToTheInnElf::HandleMessage(Elf* elf, const Telegram& message){return false;}
//-----------------------------------------------------------------------

//-------------------------GoToTheLibrary methods------------------------
GoToTheLibrary* GoToTheLibrary::Instance(){

	static GoToTheLibrary instance;

	return &instance;

}

void GoToTheLibrary::Enter(Elf* elf){

	cout << GetNameOfEntity(elf->GetEntityID()) << ": GoToTheLibrary->Enter()" << endl;

	if(elf->GetLocation() != Location::library){
		cout << GetNameOfEntity(elf->GetEntityID()) << ": Going to the library." << endl;
		elf->SetLocation(Location::library);
	}

}

void GoToTheLibrary::Execute(Elf* elf){

	//cout << GetNameOfEntity(elf->GetEntityID()) << ": GoToTheLibrary->Execute()" << endl;
	cout << GetNameOfEntity(elf->GetEntityID()) << ": Current number of gold coins is " << elf->GetCurrentNumberOfGoldCoins() << "." << endl;
	cout << GetNameOfEntity(elf->GetEntityID()) << ": I'm so bored! Got to do something interesting!!" << endl;
	elf->ReduceGoldCoins(2);
	elf->DoSomethingMeaningful();
	elf->GetStateMachine()->RevertToPreviousState();

}

void GoToTheLibrary::Exit(Elf* elf){};//cout << GetNameOfEntity(elf->GetEntityID()) << ": GoToTheLibrary->Exit()" << endl;}

bool GoToTheLibrary::HandleMessage(Elf* elf, const Telegram& message){return false;}
//-----------------------------------------------------------------------