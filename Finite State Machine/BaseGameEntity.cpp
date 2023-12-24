#include <cassert>

#include "BaseGameEntity.h"

using std::cout;
using std::endl;

//Initialise the static data member nextValidID.
int BaseGameEntity::nextValidID = 0;

void BaseGameEntity::SetID(int id){

	assert((id >= nextValidID) && "<BaseGameEntity::SetID>: Received invalid id.");

	entityID = id;
	nextValidID = id + 1;

}