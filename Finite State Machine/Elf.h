#ifndef ELF_H
#define ELF_H

#include <string>
#include <iostream>
#include <cassert>

#include "BaseGameEntity.h"
#include "StateMachine.h"
#include "Locations.h"
#include "ElfOwnedStates.h"
#include "Auxiliary.h"
#include "EntityNames.h"

using std::cout;
using std::endl;

//The maximal mana points the elf can have.
const int MAX_MANA_POINTS = 6;
//The threshold for intellectualStimulation data member. When
//reached, the elf has to stimulate her brain.
const int INTELLECTUAL_STIMULATION_THRESHOLD = 8;

//A class that represents the Elf character in the game.
class Elf : public BaseGameEntity{

private:
	//A pointer to the state machine of this class.
	StateMachine<Elf>* stateMachine;
	//Mana points gague.
	int manaPoints;
	//Intelectual stimulation gague.
	int intellectualStimulation;

public:
	//The constructor.
	Elf(int entityID): 
		manaPoints(MAX_MANA_POINTS),
		intellectualStimulation(0),
		BaseGameEntity(entityID){

			stateMachine = new StateMachine<Elf>(this);

			stateMachine->SetCurrentState(ExploreDungeonElf::Instance());
			stateMachine->SetGlobalState(ElfsGlobalState::Instance());

	}

	//The destructor.
	~Elf(){delete stateMachine;}
	//A method that performs updates.
	void Update() override;
	//A method that handles messages.
	virtual bool HandleMessage(const Telegram& message) override;
	//A getter method for the stateMachine data member.
	StateMachine<Elf>* GetStateMachine()const{return stateMachine;}

	//A method that check whether the elf has any mana points left.
	bool IsOutOfMana()const{return manaPoints <= 0;}
	//A getter method for the manaPoints data member.
	int GetManaPoints()const{return manaPoints;}
	//A method that restores the mana points to maximal value.
	void RestoreManaPoints(){manaPoints = MAX_MANA_POINTS;}

	//A method that uses a spell to attack an enemy.
	void UseSpell(int* enemy){

		int damage = RandomIntegerInRange(2, 4);
		*enemy -= damage;
		cout << GetNameOfEntity(this->GetEntityID()) << ": I've caused " << damage << " points of damage." << endl;
		manaPoints -= 2;

	}

	//A method that uses a melee move to attack an enemy.
	void UseMelee(int* enemy){

		int damage = RandomIntegerInRange(1, 3);
		*enemy -= damage;
		cout << GetNameOfEntity(this->GetEntityID()) << ": I've caused " << damage << " points of damage." << endl;

	}

	//A method that checks whether the intellectual stimulation gague is full.
	bool IsBored()const{return intellectualStimulation >= INTELLECTUAL_STIMULATION_THRESHOLD;}
	//A method that increases the intellectual stimulation gague.
	void IncreaseIntellectualStimulation(){intellectualStimulation += 1;}
	//A method that resets the intellectual stimulation gague.
	void DoSomethingMeaningful(){intellectualStimulation = 0;}
	
	//A method that checks whether the elf is in
	//one of the terminal states.
	bool IsInATerminalState(){

		return stateMachine->IsInState(*DieElf::Instance()) ||
			stateMachine->IsInState(*DieFromDehydrationElf::Instance()) ||
			stateMachine->IsInState(*DeadKnackeredElf::Instance()) ||
			stateMachine->IsInState(*DownAndOutElf::Instance());

	}

};

#endif