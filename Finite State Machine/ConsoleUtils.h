#ifndef CONSOLE_UTILS_H
#define CONSOLE_UTILS_H

#include <windows.h>
#include <conio.h>
#include <iostream>

//A function that sets the text's colour.
inline void SetTextColor(WORD colors){

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, colors);

}

//A function that prompets the user to press any key in order to continue.
inline void PressAnyKeyToContinue(){

	//Sets text's colour to white.
	SetTextColor(FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);

	std::cout << "Press any key to continue." << std::endl;

	while(!_kbhit()){}

}

#endif