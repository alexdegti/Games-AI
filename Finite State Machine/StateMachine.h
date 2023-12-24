#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <cassert>
#include <string>

#include "State.h"
#include "Telegram.h"

//A class that represents a finite state machine.
template <class EntityType>

class StateMachine{

private:
	//A pointer to EntityType that represents the owner of this finite state machine.
	EntityType* owner;
	//A pointer to State<EntityType> that represents the current state of this finite state machine.
	State<EntityType>* currentState;
	//A pointer to State<EntityType> that represents the previous state of this finite state machine.
	State<EntityType>* previousState;
	//A pointer to State<EntityType> that represents the global state of this finite state machine.
	State<EntityType>* globalState;

public:
	//A constructor that takes the owner of this finite state machine as an argument.
	StateMachine(EntityType* owner): 
		owner(owner),
		currentState(NULL),
		previousState(NULL),
		globalState(NULL){}

	//A destructor.
	virtual ~StateMachine(){}
	//A setter method for the currentState data member.
	void SetCurrentState(State<EntityType>* newCurrentState){currentState = newCurrentState;}
	//A setter method for the previousState data member.
	void SetPreviousState(State<EntityType>* newPreviousState){previousState = newPreviousState;}
	//A setter method for the globalState data member.
	void SetGlobalState(State<EntityType>* newGlobalState){globalState = newGlobalState;}

	//A method that updates this finite state machine.
	void Update() const{

		//Check whether global state exists, if so, call its Execute method.
		if(globalState)
			globalState->Execute(owner);
		//Check whether current state exists, if so, call its Execute method.
		if(currentState)
			currentState->Execute(owner);

	}

	//A method that handles messages.
	bool HandleMessage(const Telegram& message) const{

		bool output = false;
		
		//Check whether current state exists, and can it handle the message.
		if(currentState && currentState->HandleMessage(owner, message))
			output = true;
		//Check whether global state exists, and can it handle the message.
		else if(globalState && globalState->HandleMessage(owner, message))
			output = true;

		return output;

	}

	//A method that changes the state of this finite state machine.
	void ChangeState(State<EntityType>* newState){

		//Verify that the newState argument is not NULL.
		assert(newState && "<StateMachine::ChangeState>: Trying to assign NULL to current state.");

		//Set previous state to current state.
		previousState = currentState;
		//Call the Exit method of currentState.
		currentState->Exit(owner);
		//Set current state to the newState argument.
		currentState = newState;
		//Call the Enter method of the new currentState. 
		currentState->Enter(owner);

	}

	//A method that reverts back to the previous state of this finite state machine.
	void RevertToPreviousState(){currentState = previousState;}
	//A method that confirms whether this finite state machine is in a given state argument.
	bool IsInState(const State<EntityType>& state){return typeid(*currentState) == typeid(state) ? true : false;}
	//A getter method for the currentState data member.
	State<EntityType>* GetCurrentState() const{return currentState;}
	//A getter method for the previousState data member.
	State<EntityType>* GetPreviousState() const{return previousState;}
	//A getter method for the globalState data member.
	State<EntityType>* GetGlobalState() const{return globalState;}

	//A method that returns a string representation of the currentState data member.
	std::string GetNameOfCurrentState() const{

		std::string stateName(typeid(*currentState).name());

		if(stateName.size() > 5)
			stateName.erase(0, 6);

		return stateName;

	}

};

#endif