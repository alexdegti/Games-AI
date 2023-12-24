#ifndef ELF_OWNED_STATES
#define ELF_OWNED_STATES

#include "State.h"

class Elf;
struct Telegram;

//The various states the elf can be in.

//A singleton class that represents the elf's global state.
class ElfsGlobalState : public State<Elf>{

private:
	//Various constructors.
	ElfsGlobalState(){}
	ElfsGlobalState(const ElfsGlobalState&);
	ElfsGlobalState& operator=(const ElfsGlobalState&);

public:
	//A getter method for the singleton instance of this class.
	static ElfsGlobalState* Instance();
	//A method that is called upon entering the state.
	virtual void Enter(Elf*) override;
	//A method that is called during the execution of the state.
	virtual void Execute(Elf*) override;
	//A method that is called before exiting the state.
	virtual void Exit(Elf*) override;
	//A method that handles messages this state receives from other states.
	virtual bool HandleMessage(Elf*, const Telegram&) override;

};

//A singleton class that represents the ExploreDungeon state.
//In this state the elf explores the dungeon and either encounters a monster,
//or a treasure chest.
class ExploreDungeonElf : public State<Elf>{

private:
	//Various constructors.
	ExploreDungeonElf(){}
	ExploreDungeonElf(const ExploreDungeonElf&);
	ExploreDungeonElf& operator=(const ExploreDungeonElf&);

public:
	//A getter method for the singleton instance of this class.
	static ExploreDungeonElf* Instance();
	//A method that is called upon entering the state.
	virtual void Enter(Elf*) override;
	//A method that is called during the execution of the state.
	virtual void Execute(Elf*) override;
	//A method that is called before exiting the state.
	virtual void Exit(Elf*) override;
	//A method that handles messages this state receives from other states.
	virtual bool HandleMessage(Elf*, const Telegram&) override;

};

//A singleton class that represents the BattleMonster state.
//In this state the elf battles with a monster.
class BattleMonsterElf : public State<Elf>{

private:
	//Various constructors.
	BattleMonsterElf(){}
	BattleMonsterElf(const BattleMonsterElf&);
	BattleMonsterElf& operator=(const BattleMonsterElf&);

public:
	//A getter method for the singleton instance of this class.
	static BattleMonsterElf* Instance();
	//A method that is called upon entering the state.
	virtual void Enter(Elf*) override;
	//A method that is called during the execution of the state.
	virtual void Execute(Elf*) override;
	//A method that is called before exiting the state.
	virtual void Exit(Elf*) override;
	//A method that handles messages this state receives from other states.
	virtual bool HandleMessage(Elf*, const Telegram&) override;

};

//A singleton class that represents the OpenTreasureChest state.
//In this state the elf opens a treasure chest.
class OpenTreasureChestElf : public State<Elf>{

private:
	//Various constructors.
	OpenTreasureChestElf(){}
	OpenTreasureChestElf(const OpenTreasureChestElf&);
	OpenTreasureChestElf& operator=(const OpenTreasureChestElf&);

public:
	//A getter method for the singleton instance of this class.
	static OpenTreasureChestElf* Instance();
	//A method that is called upon entering the state.
	virtual void Enter(Elf*) override;
	//A method that is called during the execution of the state.
	virtual void Execute(Elf*) override;
	//A method that is called before exiting the state.
	virtual void Exit(Elf*) override;
	//A method that handles messages this state receives from other states.
	virtual bool HandleMessage(Elf*, const Telegram&) override;

};

//A singleton class that represents the Die state.
//In this state, the elf dies.
class DieElf : public State<Elf>{

private:
	//Various constructors.
	DieElf(){}
	DieElf(const DieElf&);
	DieElf& operator=(const DieElf&);

public:
	//A getter method for the singleton instance of this class.
	static DieElf* Instance();
	//A method that is called upon entering the state.
	virtual void Enter(Elf*) override;
	//A method that is called during the execution of the state.
	virtual void Execute(Elf*) override;
	//A method that is called before exiting the state.
	virtual void Exit(Elf*) override;
	//A method that handles messages this state receives from other states.
	virtual bool HandleMessage(Elf*, const Telegram&) override;

};

//A singleton class that represents the DieFromDehydration state.
//In this state, the elf dies from dehydration.
class DieFromDehydrationElf : public State<Elf>{

private:
	//Various constructors.
	DieFromDehydrationElf(){}
	DieFromDehydrationElf(const DieFromDehydrationElf&);
	DieFromDehydrationElf& operator=(const DieFromDehydrationElf&);

public:
	//A getter method for the singleton instance of this class.
	static DieFromDehydrationElf* Instance();
	//A method that is called upon entering the state.
	virtual void Enter(Elf*) override;
	//A method that is called during the execution of the state.
	virtual void Execute(Elf*) override;
	//A method that is called before exiting the state.
	virtual void Exit(Elf*) override;
	//A method that handles messages this state receives from other states.
	virtual bool HandleMessage(Elf*, const Telegram&) override;

};

//A singleton class that represents the DeadKnackered state.
//In this state, the elf dies from exhaustion.
class DeadKnackeredElf : public State<Elf>{

private:
	//Various constructors.
	DeadKnackeredElf(){}
	DeadKnackeredElf(const DeadKnackeredElf&);
	DeadKnackeredElf& operator=(const DeadKnackeredElf&);

public:
	//A getter method for the singleton instance of this class.
	static DeadKnackeredElf* Instance();
	//A method that is called upon entering the state.
	virtual void Enter(Elf*) override;
	//A method that is called during the execution of the state.
	virtual void Execute(Elf*) override;
	//A method that is called before exiting the state.
	virtual void Exit(Elf*) override;
	//A method that handles messages this state receives from other states.
	virtual bool HandleMessage(Elf*, const Telegram&) override;

};

//A singleton class that represents the DownAndOut state.
//In this state, the elf is broke, and the game is over.
class DownAndOutElf : public State<Elf>{

private:
	//Various constructors.
	DownAndOutElf(){}
	DownAndOutElf(const DownAndOutElf&);
	DownAndOutElf& operator=(const DownAndOutElf&);

public:
	//A getter method for the singleton instance of this class.
	static DownAndOutElf* Instance();
	//A method that is called upon entering the state.
	virtual void Enter(Elf*) override;
	//A method that is called during the execution of the state.
	virtual void Execute(Elf*) override;
	//A method that is called before exiting the state.
	virtual void Exit(Elf*) override;
	//A method that handles messages this state receives from other states.
	virtual bool HandleMessage(Elf*, const Telegram&) override;

};

//A singleton class that represents the GoToThePub state.
//In this state, the elf goes to the pub with the intention
//of grabbing a drink.
class GoToThePubElf : public State<Elf>{

private:
	//Various constructor.
	GoToThePubElf(){}
	GoToThePubElf(const GoToThePubElf&);
	GoToThePubElf& operator=(const GoToThePubElf&);

public:
	//A getter method for the singleton instance of this class.
	static GoToThePubElf* Instance();
	//A method that is called upon entering the state.
	virtual void Enter(Elf*) override;
	//A method that is called during the execution of the state.
	virtual void Execute(Elf*) override;
	//A method that is called before exiting the state.
	virtual void Exit(Elf*) override;
	//A method that handles messages this state receives from other states.
	virtual bool HandleMessage(Elf*, const Telegram&) override;

};

//A singleton class that represents the GrabADrink state.
//In this state, the elf goes to the pub to get some booze.
class GrabADrinkElf : public State<Elf>{

private:
	//Various constructos.
	GrabADrinkElf(){}
	GrabADrinkElf(const GrabADrinkElf&);
	GrabADrinkElf& operator=(const GrabADrinkElf&);

public:
	//A getter method for the singleton instance of this class.
	static GrabADrinkElf* Instance();
	//A method that is called upon entering the state.
	virtual void Enter(Elf*) override;
	//A method that is called during the execution of the state.
	virtual void Execute(Elf*) override;
	//A method that is called before exiting the state.
	virtual void Exit(Elf*) override;
	//A method that handles messages this state receives from other states.
	virtual bool HandleMessage(Elf*, const Telegram&) override;

};

//A singleton class that represents the PlayPoker state.
//In this state, the elf goes to the pub to play some poker.
class PlayPokerElf : public State<Elf>{

private:
	//Various constructos.
	PlayPokerElf(){}
	PlayPokerElf(const PlayPokerElf&);
	PlayPokerElf& operator=(const PlayPokerElf&);

public:
	//A getter method for the singleton instance of this class.
	static PlayPokerElf* Instance();
	//A method that is called upon entering the state.
	virtual void Enter(Elf*) override;
	//A method that is called during the execution of the state.
	virtual void Execute(Elf*) override;
	//A method that is called before exiting the state.
	virtual void Exit(Elf*) override;
	//A method that handles messages this state receives from other states.
	virtual bool HandleMessage(Elf*, const Telegram&) override;

};

//A singleton class that represents the GoToTheInn state.
//In this state, the elf goes to the inn to get some respite.
class GoToTheInnElf : public State<Elf>{

private:
	//Various constructos.
	GoToTheInnElf(){}
	GoToTheInnElf(const GoToTheInnElf&);
	GoToTheInnElf& operator=(const GoToTheInnElf&);

public:
	//A getter method for the singleton instance of this class.
	static GoToTheInnElf* Instance();
	//A method that is called upon entering the state.
	virtual void Enter(Elf*) override;
	//A method that is called during the execution of the state.
	virtual void Execute(Elf*) override;
	//A method that is called before exiting the state.
	virtual void Exit(Elf*) override;
	//A method that handles messages this state receives from other states.
	virtual bool HandleMessage(Elf*, const Telegram&) override;

};

//A singleton class that represents the GoToTheLibrary state.
//In this state, the elf goes to the library in order to stimulate
//her brain.
class GoToTheLibrary : public State<Elf>{

private:
	//Various constructors.
	GoToTheLibrary() {}
	GoToTheLibrary(const GoToTheLibrary&);
	GoToTheLibrary& operator=(const GoToTheLibrary&);

public:
	//A getter method for the singleton instance of this class.
	static GoToTheLibrary* Instance();
	//A method that is called upon entering the state.
	virtual void Enter(Elf*) override;
	//A method that is called during the execution of the state.
	virtual void Execute(Elf*) override;
	//A method that is called before exiting the state.
	virtual void Exit(Elf*) override;
	//A method that handles messages this state receives from other states.
	virtual bool HandleMessage(Elf*, const Telegram&) override;

};

#endif