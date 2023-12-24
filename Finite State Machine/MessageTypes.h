#ifndef MESSAGE_TYPES_H
#define MESSAGE_TYPES_H

#include <string>

//An enumeration that represents the various messages in the game.
enum MessageType{
	MessageFirstMessage = 1,
	MessageSecondMessage = 2,
	MessageThirdMessage = 3
};

//A function that returns a string representation of a message.
inline std::string MessageToString(int message){

	switch(message){
		case 1:{
			return "first message";
		}
		default:
			return "Unknown message";
	}

}

#endif