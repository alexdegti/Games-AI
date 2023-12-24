#ifndef TELEGRAM_H
#define TELEGRAM_H

#include <iostream>
#include <math.h>

//A struct that represents a telegram that can be exchanged between entities.
struct Telegram{

	//The entity that sent this telegram.
	int sender;
	//The entity that shall receive this telegram.
	int receiver;
	//The message being sent.
	int message;
	//The optional delay time for the telgram to be sent at.
	double dispatchTime;
	//A void pointer which enables adding any extra information should the need to do so arise.
	void* extraInformation = NULL;

	//A default constructor that sets default values to the data members.
	Telegram(): sender(-1), receiver(-1), message(-1), dispatchTime(-1){}

	//A constructor which takes the data members as arguments.
	Telegram(int sender, int receiver, int message, double dispatchTime, void* extraInformation = NULL):
		sender(sender), 
		receiver(receiver), 
		message(message),
		dispatchTime(dispatchTime),
		extraInformation(extraInformation){}

};

//A constant that defines the minimal time gap between telegrams.
const double SMALLEST_DELAY = 0.25f;

//Overloads the '==' operator in order to define equality between two telegrams.
inline bool operator==(const Telegram& firstTelegram, const Telegram& secondTelegram){

	return (fabs(firstTelegram.dispatchTime - secondTelegram.dispatchTime) < SMALLEST_DELAY) &&
		   (firstTelegram.sender == secondTelegram.sender) &&
		   (firstTelegram.receiver == secondTelegram.receiver) &&
		   (firstTelegram.message == secondTelegram.message);

}

//Overloads the '<' operator in order to define when one telegram is strictly less than another one.
inline bool operator<(const Telegram& firstTelegram, const Telegram& secondTelegram){

	if(firstTelegram == secondTelegram)
		return false;

	return firstTelegram.dispatchTime < secondTelegram.dispatchTime;

}

//Overloads the '<<' operator.
inline std::ostream& operator<<(std::ostream& outputStream, const Telegram& telegram){

	outputStream << "sender: " << telegram.sender << " receiver: " << telegram.receiver
				 << " message: " << telegram.message << " dispatch time: " << telegram.dispatchTime;

	return outputStream;

}

//An auxiliary function that "makes" the extraInformation data member usable.
template <class T>
inline T DereferenceExtraInformation(void* extraInformation){return *(T*)extraInformation;}

#endif