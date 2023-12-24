#ifndef BASE_GAME_ENTITY_H
#define BASE_GAME_ENTITY_H

#include <string>

#include "Telegram.h"
#include "State.h"
#include "Locations.h"
#include "EntityNames.h"

using std::cout;
using std::endl;

//The threshold for the fatigue data member. When reached, the base
//game entity becomes exhausted and has to refresh.
const int FATIGUE_THRESHOLD = 7;
//The threshold for thirst level data member. When reached, the base 
//game entity has to grab a drink.
const int THIRST_THRESHOLD = 9;

//An abstract class that represents a basic game entity.
class BaseGameEntity{

private:
	//Entity's ID.
	int entityID;
	//Next valid ID to be assigned to a new entity.
	static int nextValidID;
	//Current location.
	Location location;
	//Number of gold coins currently on the base game entity.
	int currentNumberOfGoldCoins;
	//Fatigue gague.
	int fatigue;
	//Thirst gague.
	int thirst;
	//Health points.
	int healthPoints;
	//A flag that indicates whether the base  game entity 
	//has played a round of poker.
	bool hasPlayedAGameOfPoker;

	//A method that sets the entityID data member.
	void SetID(int id);

public:
	//Constructor.
	BaseGameEntity(int entityID) : location(Location::dungeon),
		currentNumberOfGoldCoins(10),
		fatigue(0),
		thirst(0),
		healthPoints(10),
		hasPlayedAGameOfPoker(false){
			SetID(entityID);
		}

	//A destructor.
	virtual ~BaseGameEntity(){};
	//A pure virtual function that performs updates.
	virtual void Update() = 0;
	//A pure virtual function that handles messages.
	virtual bool HandleMessage(const Telegram& message) = 0;
	//A getter method for the entityID data member.
	int GetEntityID()const{return entityID;}

	//A getter method for the location data member.
	Location GetLocation()const{return location;}
	//A setter method for the location data member.
	void SetLocation(Location newLocation){location = newLocation;}

	//A getter method for the currentNumberOfGoldCoins data member.
	int GetCurrentNumberOfGoldCoins()const{return currentNumberOfGoldCoins;}
	//A method that adds gold coins to the current number of gold 
	//coins the base game entity carries.
	void AddGoldCoins(int goldCoinsToAdd){currentNumberOfGoldCoins += goldCoinsToAdd;}
	//A method that reduces gold coins from the current number of 
	//gold coins the base game entity carries.
	void ReduceGoldCoins(int goldCoinsToReduce){currentNumberOfGoldCoins -= goldCoinsToReduce;}
	//A method that checks whether the base game entity has a negative 
	//number of gold coins, and therefore is down and out.
	bool IsDownAndOut()const{return currentNumberOfGoldCoins < 0;}

	//A method that checks whether the fatigue gague is full.
	bool IsFatigued()const{return fatigue >= FATIGUE_THRESHOLD;}
	//A method that increases the fatigue gague.
	void IncreaseFatigue(){fatigue += 1;}
	//A method that resets the fatigue gague.
	void Sleep(){fatigue = 0;}

	//A method that checks whether the thirst gague is full.
	bool IsThirsty()const{return thirst >= THIRST_THRESHOLD;}
	//A method that increases the thirst gague.
	void IncreaseThirst(){thirst += 1;}
	//A method that resets the thirst gague.
	void QuenchThirst(){thirst = 0;}

	//A getter method for the healtPoints data member.
	int GetHealthPoints()const{return healthPoints;}
	//A method that checks whether the base game entity is dead.
	bool IsDead()const{return healthPoints <= 0;}
	//A method that reduces the base game entity's health points.
	void DecreaseHealthPoints(int damage){healthPoints -= damage;}
	//A method that restores the base game entity's health points.
	void RestoreHealthPoints(){healthPoints = 10;}

	//A getter method for the hasPlayedAGameOfPoker data member.
	bool HasPlayedAGameOfPoker()const{return hasPlayedAGameOfPoker;}
	//A method that changes the value of the hasPlayedAGameOfPoker 
	//data member.
	void AlterHasPlayedAGameOfPokerFlag(){hasPlayedAGameOfPoker = !hasPlayedAGameOfPoker;}

	//A method that prints a message to the screen upon 
	//winning the game.
	void WinningGameMessage(){
		cout << GetNameOfEntity(this->GetEntityID()) << ": I won the game, and amassed "
			<< this->GetCurrentNumberOfGoldCoins() << " gold coins!" << endl;
	}

};

#endif