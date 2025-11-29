#include "environment.h"

INT32 mainCRTStartup() {

	// Message to print to the console "Hello, World!" as an array of CHARs
	CHAR message[15];

	message[0] = 'H'; message[1] = 'e'; message[2] = 'l'; message[3] = 'l';
	message[4] = 'o'; message[5] = ','; message[6] = ' ';
	message[7] = 'W'; message[8] = 'o'; message[9] = 'r'; message[10] = 'l';
	message[11] = 'd'; message[12] = '!'; message[13] = '\n'; message[14] = 0;

	WriteConsole(message, sizeof(message));

	ExitWithCode(0);

}
