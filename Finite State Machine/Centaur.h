#ifndef CENTAUR_H
#define CENTAUR_H

#include <string>
#include <iostream>
#include <cassert>

#include "BaseGameEntity.h"
#include "StateMachine.h"
#include "Locations.h"
#include "CentaurOwnedStates.h"
#include "Auxiliary.h"
#include "EntityNames.h"

using std::cout;
using std::endl;

//The maximal amount of arrows the centaur can carry.
const int MAXIMAL_ARROWS_CAPACITY = 6;
//The threshold for the tailStatus data member. When reached, the
//centaur has to broom his tail. (He is a self conscious creature...)
const int TAIL_CONDITION_THRESHOLD = 8;

class Centaur : public BaseGameEntity{

private:
	//A pointer to the state machine of this class.
	StateMachine<Centaur>* stateMachine;
	//The current number of arrows the centaur has.
	int arrowsLeft;
	//The tail's condition gague.
	int tailCondition;
	
public:
	//The constructor.
	Centaur(int entityID):
		arrowsLeft(MAXIMAL_ARROWS_CAPACITY),
		tailCondition(0),
		BaseGameEntity(entityID){

			stateMachine = new StateMachine<Centaur>(this);

			stateMachine->SetCurrentState(ExploreDungeonCentaur::Instance());
			stateMachine->SetGlobalState(CentaursGlobalState::Instance());

		}

	//The destructor.
	~Centaur(){delete stateMachine;}
	//A method that performs updates.
	void Update();
	//A method that handles messages.
	virtual bool HandleMessage(const Telegram& message);
	//A getter method for the stateMachine data member.
	StateMachine<Centaur>* GetStateMachine()const{return stateMachine;}

	//A getter method for the arrowsLeft data member.
	int GetArrowsLeft()const{return arrowsLeft;}
	//A method that checks whether there are any arrows left.
	bool HasArrowsLeft()const{return arrowsLeft > 0;}
	//A method that restocks the arrows the centaur carries.
	void RestockArrows(){arrowsLeft = MAXIMAL_ARROWS_CAPACITY;}

	//A method that uses the bow to attack an enemy.
	void UseBow(int* enemy){

		int damage = RandomIntegerInRange(2, 4);
		*enemy -= damage;
		cout << GetNameOfEntity(this->GetEntityID()) << ": I've caused " << damage << " points of damage." << endl;
		arrowsLeft -= 2;

	}

	//A method that uses a melee move to attack an enemy.
	void UseMelee(int* enemy){

		int damage = RandomIntegerInRange(1, 3);
		*enemy -= damage;
		cout << GetNameOfEntity(this->GetEntityID()) << ": I've caused " << damage << " points of damage." << endl;

	}

	//A method that checks whether the centaur's tail requires brooming.
	bool DoesTailRequireBrooming()const{return tailCondition >= TAIL_CONDITION_THRESHOLD;}
	//A method that grooms the centaur's tail.
	void GroomTail(){tailCondition = 0;}
	//A method that worsens the centaur's tail status.
	void WorsenTailStatus(){tailCondition += 1;}

	//A method that checks whether the centaur is in
	//one of the terminal states.
	bool IsInATerminalState(){

		return stateMachine->IsInState(*DieCentaur::Instance()) ||
			stateMachine->IsInState(*DieFromDehydrationCentaur::Instance()) ||
			stateMachine->IsInState(*DeadKnackeredCentaur::Instance()) ||
			stateMachine->IsInState(*DownAndOutCentaur::Instance());

	}

};

#endif