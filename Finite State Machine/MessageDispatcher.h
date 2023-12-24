#ifndef MESSAGE_DISPATCHER_H
#define MESSAGE_DISPATCHER_H

#include <set>

#include "ConsoleUtils.h"
#include "Telegram.h"

#define Dispatcher MessageDispatcher::Instance()

class BaseGameEntity;

//A flag for sending a message without delay.
const double SEND_MESSAGE_IMMEDIATELY = 0.f;
//A flag that indicates the message does not include additional information.
const int NO_ADDITIONAL_INFORMATION = 0;

//A class that represents the component responsibile for delivery of messages.
class MessageDispatcher{

private:
	//A queue of the message to be sent after a certain delay.
	//The messages are sorted by thier delay.
	std::set<Telegram> delayedMessagesQueue;
	//A method that calls the message handling method of the receiver.
	void Dispatch(BaseGameEntity* receiver, const Telegram& message);

	//Various constructors made private in order to turn this class into a singleton.
	MessageDispatcher(){};
	MessageDispatcher(const MessageDispatcher&);
	MessageDispatcher& operator=(const MessageDispatcher&);

public:
	//A getter method for the instance of this singleton class.
	static MessageDispatcher* Instance();
	//A method that sends a message to another agent.
	void DispatchMessage(double delay, int sender, int receiver, int message, void* extraInformation);
	//A method that sends delayed messages.
	void DispatchDelayedMessage();

};

#endif