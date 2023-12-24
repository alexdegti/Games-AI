#ifndef CENTAUR_OWNED_STATES
#define CENTAUR_OWNED_STATES

#include "State.h"

class Centaur;
struct Telegram;

//The various states the centaur can be in.

//A singleton class that represents the centaur's global state.
class CentaursGlobalState : public State<Centaur>{

private:
	//Various constructors.
	CentaursGlobalState(){}
	CentaursGlobalState(const CentaursGlobalState&);
	CentaursGlobalState& operator=(const CentaursGlobalState&);

public:
	//A getter method for the singleton instance of this class.
	static CentaursGlobalState* Instance();
	//A method that is called upon entering the state.
	virtual void Enter(Centaur*) override;
	//A method that is called during the execution of the state.
	virtual void Execute(Centaur*) override;
	//A method that is called before exiting the state.
	virtual void Exit(Centaur*) override;
	//A method that handles messages this state receives from other states.
	virtual bool HandleMessage(Centaur*, const Telegram&) override;

};

//A singleton class that represents the ExploreDungeoCentaur state.
//In this state the centaur explores the dungeon and either encounters a monster,
//or a treasure chest.
class ExploreDungeonCentaur : public State<Centaur>{

private:
	//Various constructors.
	ExploreDungeonCentaur(){}
	ExploreDungeonCentaur(const ExploreDungeonCentaur&);
	ExploreDungeonCentaur& operator=(const ExploreDungeonCentaur&);

public:
	//A getter method for the singleton instance of this class.
	static ExploreDungeonCentaur* Instance();
	//A method that is called upon entering the state.
	virtual void Enter(Centaur*) override;
	//A method that is called during the execution of the state.
	virtual void Execute(Centaur*) override;
	//A method that is called before exiting the state.
	virtual void Exit(Centaur*) override;
	//A method that handles messages this state receives from other states.
	virtual bool HandleMessage(Centaur*, const Telegram&) override;

};

//A singleton class that represents the BattleMonsterCentaur state.
//In this state the centaur battles with a monster.
class BattleMonsterCentaur : public State<Centaur>{

private:
	//Various constructors.
	BattleMonsterCentaur(){}
	BattleMonsterCentaur(const BattleMonsterCentaur&);
	BattleMonsterCentaur& operator=(const BattleMonsterCentaur&);

public:
	//A getter method for the singleton instance of this class.
	static BattleMonsterCentaur* Instance();
	//A method that is called upon entering the state.
	virtual void Enter(Centaur*) override;
	//A method that is called during the execution of the state.
	virtual void Execute(Centaur*) override;
	//A method that is called before exiting the state.
	virtual void Exit(Centaur*) override;
	//A method that handles messages this state receives from other states.
	virtual bool HandleMessage(Centaur*, const Telegram&) override;

};

//A singleton class that represents the OpenTreasureChest state.
//In this state the centaur opens a treasure chest.
class OpenTreasureChestCentaur : public State<Centaur>{

private:
	//Various constructors.
	OpenTreasureChestCentaur(){}
	OpenTreasureChestCentaur(const OpenTreasureChestCentaur&);
	OpenTreasureChestCentaur& operator=(const OpenTreasureChestCentaur&);

public:
	//A getter method for the singleton instance of this class.
	static OpenTreasureChestCentaur* Instance();
	//A method that is called upon entering the state.
	virtual void Enter(Centaur*) override;
	//A method that is called during the execution of the state.
	virtual void Execute(Centaur*) override;
	//A method that is called before exiting the state.
	virtual void Exit(Centaur*) override;
	//A method that handles messages this state receives from other states.
	virtual bool HandleMessage(Centaur*, const Telegram&) override;

};

//A singleton class that represents the Die state.
//In this state, the centaur dies.
class DieCentaur : public State<Centaur>{

private:
	//Various constructors.
	DieCentaur(){}
	DieCentaur(const DieCentaur&);
	DieCentaur& operator=(const DieCentaur&);

public:
	//A getter method for the singleton instance of this class.
	static DieCentaur* Instance();
	//A method that is called upon entering the state.
	virtual void Enter(Centaur*) override;
	//A method that is called during the execution of the state.
	virtual void Execute(Centaur*) override;
	//A method that is called before exiting the state.
	virtual void Exit(Centaur*) override;
	//A method that handles messages this state receives from other states.
	virtual bool HandleMessage(Centaur*, const Telegram&) override;

};

//A singleton class that represents the DieFromDehydration state.
//In this state, the centaur dies from dehydration.
class DieFromDehydrationCentaur : public State<Centaur>{

private:
	//Various constructors.
	DieFromDehydrationCentaur(){}
	DieFromDehydrationCentaur(const DieFromDehydrationCentaur&);
	DieFromDehydrationCentaur& operator=(const DieFromDehydrationCentaur&);

public:
	//A getter method for the singleton instance of this class.
	static DieFromDehydrationCentaur* Instance();
	//A method that is called upon entering the state.
	virtual void Enter(Centaur*) override;
	//A method that is called during the execution of the state.
	virtual void Execute(Centaur*) override;
	//A method that is called before exiting the state.
	virtual void Exit(Centaur*) override;
	//A method that handles messages this state receives from other states.
	virtual bool HandleMessage(Centaur*, const Telegram&) override;

};

//A singleton class that represents the DeadKnackered state.
//In this state, the centaur dies from exhaustion.
class DeadKnackeredCentaur : public State<Centaur>{

private:
	//Various constructors.
	DeadKnackeredCentaur(){}
	DeadKnackeredCentaur(const DeadKnackeredCentaur&);
	DeadKnackeredCentaur& operator=(const DeadKnackeredCentaur&);

public:
	//A getter method for the singleton instance of this class.
	static DeadKnackeredCentaur* Instance();
	//A method that is called upon entering the state.
	virtual void Enter(Centaur*) override;
	//A method that is called during the execution of the state.
	virtual void Execute(Centaur*) override;
	//A method that is called before exiting the state.
	virtual void Exit(Centaur*) override;
	//A method that handles messages this state receives from other states.
	virtual bool HandleMessage(Centaur*, const Telegram&) override;

};

//A singleton class that represents the DownAndOut state.
//In this state, the centaur is broke, and the game is over.
class DownAndOutCentaur : public State<Centaur>{

private:
	//Various constructors.
	DownAndOutCentaur(){}
	DownAndOutCentaur(const DownAndOutCentaur&);
	DownAndOutCentaur& operator=(const DownAndOutCentaur&);

public:
	//A getter method for the singleton instance of this class.
	static DownAndOutCentaur* Instance();
	//A method that is called upon entering the state.
	virtual void Enter(Centaur*) override;
	//A method that is called during the execution of the state.
	virtual void Execute(Centaur*) override;
	//A method that is called before exiting the state.
	virtual void Exit(Centaur*) override;
	//A method that handles messages this state receives from other states.
	virtual bool HandleMessage(Centaur*, const Telegram&) override;

};

//A singleton class that represents the GoToThePub state.
//In this state, the centaur goes to the pub with the intention
//of grabbing a drink.
class GoToThePubCentaur : public State<Centaur>{

private:
	//Various constructor.
	GoToThePubCentaur(){}
	GoToThePubCentaur(const GoToThePubCentaur&);
	GoToThePubCentaur& operator=(const GoToThePubCentaur&);

public:
	//A getter method for the singleton instance of this class.
	static GoToThePubCentaur* Instance();
	//A method that is called upon entering the state.
	virtual void Enter(Centaur*) override;
	//A method that is called during the execution of the state.
	virtual void Execute(Centaur*) override;
	//A method that is called before exiting the state.
	virtual void Exit(Centaur*) override;
	//A method that handles messages this state receives from other states.
	virtual bool HandleMessage(Centaur*, const Telegram&) override;

};

//A singleton class that represents the GrabADrink state.
//In this state, the centaur goes to the pub to get some booze.
class GrabADrinkCentaur : public State<Centaur>{

private:
	//Various constructos.
	GrabADrinkCentaur(){}
	GrabADrinkCentaur(const GrabADrinkCentaur&);
	GrabADrinkCentaur& operator=(const GrabADrinkCentaur&);

public:
	//A getter method for the singleton instance of this class.
	static GrabADrinkCentaur* Instance();
	//A method that is called upon entering the state.
	virtual void Enter(Centaur*) override;
	//A method that is called during the execution of the state.
	virtual void Execute(Centaur*) override;
	//A method that is called before exiting the state.
	virtual void Exit(Centaur*) override;
	//A method that handles messages this state receives from other states.
	virtual bool HandleMessage(Centaur*, const Telegram&) override;

};

//A singleton class that represents the PlayPoker state.
//In this state, the centaur goes to the pub to play some poker.
class PlayPokerCentaur : public State<Centaur>{

private:
	//Various constructos.
	PlayPokerCentaur(){}
	PlayPokerCentaur(const PlayPokerCentaur&);
	PlayPokerCentaur& operator=(const PlayPokerCentaur&);

public:
	//A getter method for the singleton instance of this class.
	static PlayPokerCentaur* Instance();
	//A method that is called upon entering the state.
	virtual void Enter(Centaur*) override;
	//A method that is called during the execution of the state.
	virtual void Execute(Centaur*) override;
	//A method that is called before exiting the state.
	virtual void Exit(Centaur*) override;
	//A method that handles messages this state receives from other states.
	virtual bool HandleMessage(Centaur*, const Telegram&) override;

};

//A singleton class that represents the GoToTheInn state.
//In this state, the centaur goes to the inn to get some respite.
class GoToTheInnCentaur : public State<Centaur>{

private:
	//Various constructos.
	GoToTheInnCentaur(){}
	GoToTheInnCentaur(const GoToTheInnCentaur&);
	GoToTheInnCentaur& operator=(const GoToTheInnCentaur&);

public:
	//A getter method for the singleton instance of this class.
	static GoToTheInnCentaur* Instance();
	//A method that is called upon entering the state.
	virtual void Enter(Centaur*) override;
	//A method that is called during the execution of the state.
	virtual void Execute(Centaur*) override;
	//A method that is called before exiting the state.
	virtual void Exit(Centaur*) override;
	//A method that handles messages this state receives from other states.
	virtual bool HandleMessage(Centaur*, const Telegram&) override;

};

//A singleton class that represents the GoToTheBeautySalon state.
//In this state, the centaur goes to the beauty salon to broom his 
//beloved tail.
class GoToTheBeautySalon : public State<Centaur>{

private:
	//Various constructos.
	GoToTheBeautySalon(){}
	GoToTheBeautySalon(const GoToTheBeautySalon&);
	GoToTheBeautySalon& operator=(const GoToTheBeautySalon&);

public:
	//A getter method for the singleton instance of this class.
	static GoToTheBeautySalon* Instance();
	//A method that is called upon entering the state.
	virtual void Enter(Centaur*) override;
	//A method that is called during the execution of the state.
	virtual void Execute(Centaur*) override;
	//A method that is called before exiting the state.
	virtual void Exit(Centaur*) override;
	//A method that handles messages this state receives from other states.
	virtual bool HandleMessage(Centaur*, const Telegram&) override;

};

#endif