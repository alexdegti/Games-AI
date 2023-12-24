#ifndef DWARF_OWNED_STATES_H
#define DWARF_OWNED_STATES_H

#include "State.h"

class Dwarf;
struct Telegram;

//The various states the dwarf can be in.

//A singleton class that represents the dwarf's global state.
class DwarfsGlobalState : public State<Dwarf>{

private:
	//Various constructors.
	DwarfsGlobalState(){}
	DwarfsGlobalState(const DwarfsGlobalState&);
	DwarfsGlobalState& operator=(const DwarfsGlobalState&);

public:
	//A getter method for the singleton instance of this class.
	static DwarfsGlobalState* Instance();
	//A method that is called upon entering the state.
	virtual void Enter(Dwarf*) override;
	//A method that is called during the execution of the state.
	virtual void Execute(Dwarf*) override;
	//A method that is called before exiting the state.
	virtual void Exit(Dwarf*) override;
	//A method that handles messages this state receives from other states.
	virtual bool HandleMessage(Dwarf*, const Telegram&) override;

};

//A singleton class that represents the ExploreDungeon state.
//In this state the dwarf explores the dungeon and either encounters a monster,
//or a treasure chest.
class ExploreDungeonDwarf : public State<Dwarf>{

private:
	//Various constructors.
	ExploreDungeonDwarf(){}
	ExploreDungeonDwarf(const ExploreDungeonDwarf&);
	ExploreDungeonDwarf& operator=(const ExploreDungeonDwarf&);

public:
	//A getter method for the singleton instance of this class.
	static ExploreDungeonDwarf* Instance();
	//A method that is called upon entering the state.
	virtual void Enter(Dwarf*) override;
	//A method that is called during the execution of the state.
	virtual void Execute(Dwarf*) override;
	//A method that is called before exiting the state.
	virtual void Exit(Dwarf*) override;
	//A method that handles messages this state receives from other states.
	virtual bool HandleMessage(Dwarf*, const Telegram&) override;

};

//A singleton class that represents the BattleMonster state.
//In this state the dwarf battles with a monster.
class BattleMonsterDwarf : public State<Dwarf>{

private:
	//Various constructors.
	BattleMonsterDwarf(){}
	BattleMonsterDwarf(const BattleMonsterDwarf&);
	BattleMonsterDwarf& operator=(const BattleMonsterDwarf&);

public:
	//A getter method for the singleton instance of this class.
	static BattleMonsterDwarf* Instance();
	//A method that is called upon entering the state.
	virtual void Enter(Dwarf*) override;
	//A method that is called during the execution of the state.
	virtual void Execute(Dwarf*) override;
	//A method that is called before exiting the state.
	virtual void Exit(Dwarf*) override;
	//A method that handles messages this state receives from other states.
	virtual bool HandleMessage(Dwarf*, const Telegram&) override;

};

//A singleton class that represents the OpenTreasureChest state.
//In this state the dwarf opens a treasure chest.
class OpenTreasureChestDwarf : public State<Dwarf>{

private:
	//Various constructors.
	OpenTreasureChestDwarf(){}
	OpenTreasureChestDwarf(const OpenTreasureChestDwarf&);
	OpenTreasureChestDwarf& operator=(const OpenTreasureChestDwarf&);

public:
	//A getter method for the singleton instance of this class.
	static OpenTreasureChestDwarf* Instance();
	//A method that is called upon entering the state.
	virtual void Enter(Dwarf*) override;
	//A method that is called during the execution of the state.
	virtual void Execute(Dwarf*) override;
	//A method that is called before exiting the state.
	virtual void Exit(Dwarf*) override;
	//A method that handles messages this state receives from other states.
	virtual bool HandleMessage(Dwarf*, const Telegram&) override;

};

//A singleton class that represents the Die state.
//In this state, the dwarf dies.
class DieDwarf : public State<Dwarf>{

private:
	//Various constructors.
	DieDwarf(){}
	DieDwarf(const DieDwarf&);
	DieDwarf& operator=(const DieDwarf&);

public:
	//A getter method for the singleton instance of this class.
	static DieDwarf* Instance();
	//A method that is called upon entering the state.
	virtual void Enter(Dwarf*) override;
	//A method that is called during the execution of the state.
	virtual void Execute(Dwarf*) override;
	//A method that is called before exiting the state.
	virtual void Exit(Dwarf*) override;
	//A method that handles messages this state receives from other states.
	virtual bool HandleMessage(Dwarf*, const Telegram&) override;

};

//A singleton class that represents the DieFromDehydration state.
//In this state, the dwarf dies from dehydration.
class DieFromDehydrationDwarf : public State<Dwarf>{

private:
	//Various constructors.
	DieFromDehydrationDwarf(){}
	DieFromDehydrationDwarf(const DieFromDehydrationDwarf&);
	DieFromDehydrationDwarf& operator=(const DieFromDehydrationDwarf&);

public:
	//A getter method for the singleton instance of this class.
	static DieFromDehydrationDwarf* Instance();
	//A method that is called upon entering the state.
	virtual void Enter(Dwarf*) override;
	//A method that is called during the execution of the state.
	virtual void Execute(Dwarf*) override;
	//A method that is called before exiting the state.
	virtual void Exit(Dwarf*) override;
	//A method that handles messages this state receives from other states.
	virtual bool HandleMessage(Dwarf*, const Telegram&) override;

};

//A singleton class that represents the DeadKnackered state.
//In this state, the dwarf dies from exhaustion.
class DeadKnackeredDwarf : public State<Dwarf>{

private:
	//Various constructors.
	DeadKnackeredDwarf(){}
	DeadKnackeredDwarf(const DeadKnackeredDwarf&);
	DeadKnackeredDwarf& operator=(const DeadKnackeredDwarf&);

public:
	//A getter method for the singleton instance of this class.
	static DeadKnackeredDwarf* Instance();
	//A method that is called upon entering the state.
	virtual void Enter(Dwarf*) override;
	//A method that is called during the execution of the state.
	virtual void Execute(Dwarf*) override;
	//A method that is called before exiting the state.
	virtual void Exit(Dwarf*) override;
	//A method that handles messages this state receives from other states.
	virtual bool HandleMessage(Dwarf*, const Telegram&) override;

};

//A singleton class that represents the DownAndOut state.
//In this state, the dwarf is broke, and the game is over.
class DownAndOutDwarf : public State<Dwarf>{

private:
	//Various constructors.
	DownAndOutDwarf(){}
	DownAndOutDwarf(const DownAndOutDwarf&);
	DownAndOutDwarf& operator=(const DownAndOutDwarf&);

public:
	//A getter method for the singleton instance of this class.
	static DownAndOutDwarf* Instance();
	//A method that is called upon entering the state.
	virtual void Enter(Dwarf*) override;
	//A method that is called during the execution of the state.
	virtual void Execute(Dwarf*) override;
	//A method that is called before exiting the state.
	virtual void Exit(Dwarf*) override;
	//A method that handles messages this state receives from other states.
	virtual bool HandleMessage(Dwarf*, const Telegram&) override;

};

//A singleton class that represents the GoToThePub state.
//In this state, the dwarf goes to the pub with the intention
//of grabbing a drink.
class GoToThePubDwarf : public State<Dwarf>{

private:
	//Various constructor.
	GoToThePubDwarf(){}
	GoToThePubDwarf(const GoToThePubDwarf&);
	GoToThePubDwarf& operator=(const GoToThePubDwarf&);

public:
	//A getter method for the singleton instance of this class.
	static GoToThePubDwarf* Instance();
	//A method that is called upon entering the state.
	virtual void Enter(Dwarf*) override;
	//A method that is called during the execution of the state.
	virtual void Execute(Dwarf*) override;
	//A method that is called before exiting the state.
	virtual void Exit(Dwarf*) override;
	//A method that handles messages this state receives from other states.
	virtual bool HandleMessage(Dwarf*, const Telegram&) override;

};

//A singleton class that represents the GrabADrink state.
//In this state, the dwarf goes to the pub to get some booze.
class GrabADrinkDwarf : public State<Dwarf>{

private:
	//Various constructos.
	GrabADrinkDwarf(){}
	GrabADrinkDwarf(const GrabADrinkDwarf&);
	GrabADrinkDwarf& operator=(const GrabADrinkDwarf&);

public:
	//A getter method for the singleton instance of this class.
	static GrabADrinkDwarf* Instance();
	//A method that is called upon entering the state.
	virtual void Enter(Dwarf*) override;
	//A method that is called during the execution of the state.
	virtual void Execute(Dwarf*) override;
	//A method that is called before exiting the state.
	virtual void Exit(Dwarf*) override;
	//A method that handles messages this state receives from other states.
	virtual bool HandleMessage(Dwarf*, const Telegram&) override;

};

//A singleton class that represents the PlayPoker state.
//In this state, the dwarf goes to the pub to play some poker.
class PlayPokerDwarf : public State<Dwarf>{

private:
	//Various constructos.
	PlayPokerDwarf(){}
	PlayPokerDwarf(const PlayPokerDwarf&);
	PlayPokerDwarf& operator=(const PlayPokerDwarf&);

public:
	//A getter method for the singleton instance of this class.
	static PlayPokerDwarf* Instance();
	//A method that is called upon entering the state.
	virtual void Enter(Dwarf*) override;
	//A method that is called during the execution of the state.
	virtual void Execute(Dwarf*) override;
	//A method that is called before exiting the state.
	virtual void Exit(Dwarf*) override;
	//A method that handles messages this state receives from other states.
	virtual bool HandleMessage(Dwarf*, const Telegram&) override;

};

//A singleton class that represents the GoToTheInn state.
//In this state, the dwarf goes to the inn to get some respite.
class GoToTheInnDwarf : public State<Dwarf>{

private:
	//Various constructos.
	GoToTheInnDwarf(){}
	GoToTheInnDwarf(const GoToTheInnDwarf&);
	GoToTheInnDwarf& operator=(const GoToTheInnDwarf&);

public:
	//A getter method for the singleton instance of this class.
	static GoToTheInnDwarf* Instance();
	//A method that is called upon entering the state.
	virtual void Enter(Dwarf*) override;
	//A method that is called during the execution of the state.
	virtual void Execute(Dwarf*) override;
	//A method that is called before exiting the state.
	virtual void Exit(Dwarf*) override;
	//A method that handles messages this state receives from other states.
	virtual bool HandleMessage(Dwarf*, const Telegram&) override;

};

//A singleton class that represents the GoToTheTobaccoShop state.
//In this state, the dwarf goes to the tobacco shop to get a
//fine cigar.
class GoToTheTobaccoShop : public State<Dwarf>{

private:
	//Various constructos.
	GoToTheTobaccoShop(){};
	GoToTheTobaccoShop(const GoToTheTobaccoShop&);
	GoToTheTobaccoShop& operator=(const GoToTheTobaccoShop&);

public:
	//A getter method for the singleton instance of this class.
	static GoToTheTobaccoShop* Instance();
	//A method that is called upon entering the state.
	virtual void Enter(Dwarf*) override;
	//A method that is called during the execution of the state.
	virtual void Execute(Dwarf*) override;
	//A method that is called before exiting the state.
	virtual void Exit(Dwarf*) override;
	//A method that handles messages this state receives from other states.
	virtual bool HandleMessage(Dwarf*, const Telegram&) override;

};

#endif