#ifndef STATE_H
#define STATE_H

struct Telegram;

//An abstract class that represents an agent's state.
template <class EntityType>
class State{

public:
	//A destructor.
	virtual ~State(){};
	//A pure virtual function that is called when first entering the state.
	virtual void Enter(EntityType*) = 0;
	//A pure virtual function that performs the 'normal' update of the state.
	virtual void Execute(EntityType*) = 0;
	//A pure virtual function that is called upon changing into another state.
	virtual void Exit(EntityType*) = 0;
	//A pure virtual function that handles messages recevied whilst in the state.
	virtual bool HandleMessage(EntityType*, const Telegram&) = 0;

};

#endif