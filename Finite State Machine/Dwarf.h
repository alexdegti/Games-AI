#ifndef DWARF_H
#define DWARF_H
	
#include <string>
#include <iostream>
#include <cassert>

#include "BaseGameEntity.h"
#include "StateMachine.h"
#include "Locations.h"
#include "DwarfOwnedStates.h"
#include "Auxiliary.h"
#include "EntityNames.h"

using std::cout;
using std::endl;

const int TOBACCO_NEED_THRESHOLD = 8;
const int AXE_PERFECT_SHAPE = 6;

class Dwarf : public BaseGameEntity{

private:
	//A pointer to the state machine of this class.
	StateMachine<Dwarf>* stateMachine;
	int axeShape;
	int tobaccoNeed;

public:

	//The constructor.
	Dwarf(int entityID): 
		axeShape(5),
		tobaccoNeed(0),
		BaseGameEntity(entityID){

			stateMachine = new StateMachine<Dwarf>(this);

			stateMachine->SetCurrentState(ExploreDungeonDwarf::Instance());
			stateMachine->SetGlobalState(DwarfsGlobalState::Instance());

		}

	//The destructor.
	~Dwarf(){delete stateMachine;}
	//A method that performs updates.
	void Update();
	//A method that handles messages.
	virtual bool HandleMessage(const Telegram& message);
	//A getter method for the stateMachine data member.
	StateMachine<Dwarf>* GetStateMachine()const{return stateMachine;}

	//A method that checks whether the axe is in a
	//usable state.
	bool IsAxeInAUsableState()const{return axeShape > 0;}
	//A method that repairs the axe.
	void RepairAxe(){axeShape = AXE_PERFECT_SHAPE;}

	//A method that uses the axe to attack an enemy.
	void UseAxe(int* enemy){

		int damage = RandomIntegerInRange(2, 4);
		*enemy -= damage;
		cout << GetNameOfEntity(this->GetEntityID()) << ": I've caused " << damage << " points of damage." << endl;
		axeShape -= 2;

	}

	//A method that uses a melee move to attack an enemy.
	void UseMelee(int* enemy){

		int damage = RandomIntegerInRange(1, 3);
		*enemy -= damage;
		cout << GetNameOfEntity(this->GetEntityID()) << ": I've caused " << damage << " points of damage." << endl;

	}

	//A method that increases the tobaccoNeed data member.
	void IncreaseTobaccoNeed(){tobaccoNeed += 1;}
	//A method that resets the tobaccoNeed data member.
	void SmokeCigar(){tobaccoNeed = 0;}
	//A method that checks whether the tobaccoNeed data
	//member reached it's maximal value.
	bool DoesNeedASmoke()const{return tobaccoNeed == TOBACCO_NEED_THRESHOLD;}

	//A method that checks whether the dwarf is in
	//one of the terminal states.
	bool IsInATerminalState(){

		return stateMachine->IsInState(*DieDwarf::Instance()) ||
			stateMachine->IsInState(*DieFromDehydrationDwarf::Instance()) ||
			stateMachine->IsInState(*DeadKnackeredDwarf::Instance()) ||
			stateMachine->IsInState(*DownAndOutDwarf::Instance());

	}
	
};

#endif