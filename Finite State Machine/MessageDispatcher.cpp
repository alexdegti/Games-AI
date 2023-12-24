#include <iostream>

#include "MessageDispatcher.h"
#include "BaseGameEntity.h"
#include "CrudeTimer.h"
#include "EntityManager.h"
#include "Locations.h"
#include "MessageTypes.h"
#include "EntityNames.h"

using std::cout;
using std::endl;
using std::set;

void MessageDispatcher::Dispatch(BaseGameEntity* receiver, const Telegram& message){

	if(!receiver->HandleMessage(message))
		cout << "The MessageDispatcher could not send the following message: " << MessageToString(message.message) << endl;

}

MessageDispatcher* MessageDispatcher::Instance(){

	static MessageDispatcher instance;

	return &instance;

}

void MessageDispatcher::DispatchMessage(double delay, int sender, int receiver, int message, void* extraInformation){

	SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	BaseGameEntity* senderPointer = Manager->GetEntityByID(sender);
	BaseGameEntity* receiverPointer = Manager->GetEntityByID(receiver);

	if(!receiverPointer){
		cout << "The MessageDispatcher was provided with invalid receiver: " << receiver << endl;
		return;
	}
	
	Telegram telegram(sender, receiver, message, 0, extraInformation);

	if(delay <= 0.f){
		cout << "The MessageDispatcher sent the following message: " << MessageToString(message) << endl
			 << "From: " << GetNameOfEntity(senderPointer->GetEntityID()) << " to: " << GetNameOfEntity(receiverPointer->GetEntityID()) << endl
			 << "At: " << Clock->GetCurrentTime() << endl;
		Dispatch(receiverPointer, telegram);
	}
	else{
		telegram.dispatchTime = Clock->GetCurrentTime() + delay;
		delayedMessagesQueue.insert(telegram);
		cout << "The MessageDispatcher queued the following message: " << MessageToString(message) << endl
			 << "From: " << GetNameOfEntity(senderPointer->GetEntityID()) << " to: " << GetNameOfEntity(receiverPointer->GetEntityID()) << endl
			 << "At: " << Clock->GetCurrentTime() << endl;
	}

}

void MessageDispatcher::DispatchDelayedMessage(){

	SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	while((!delayedMessagesQueue.empty()) &&
		 (delayedMessagesQueue.begin()->dispatchTime > 0) &&
		 (delayedMessagesQueue.begin()->dispatchTime < Clock->GetCurrentTime())){
		
		const Telegram& message = *delayedMessagesQueue.begin();
		BaseGameEntity* receiver = Manager->GetEntityByID(message.receiver);

		cout << "The MessageDispatcher sent the following delayed message: " << MessageToString(message.message) << endl
			 << "From: " << GetNameOfEntity(message.sender) << " to: " << GetNameOfEntity(message.receiver) << endl
			 << "At: " << Clock->GetCurrentTime() << endl;

		Dispatch(receiver, message);

		delayedMessagesQueue.erase(delayedMessagesQueue.begin());

	}

}