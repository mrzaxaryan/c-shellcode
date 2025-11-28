#include "environment.h"

// Function pointer type for WriteConsoleA_t function
typedef BOOL(WINAPI* WriteConsoleA_t)(HANDLE hConsoleOutput, LPCSTR lpBuffer, UINT32 nNumberOfCharsToWrite, UINT32* lpNumberOfCharsWritten, UINT32* lpReserved);

int mainCRTStartup() {

	PPEB peb = GetCurrentPEB(); // Get the current process's PEB pointer

	// Name of the module to resolve
	WCHAR moduleName[13];
	moduleName[0]=L'K'; moduleName[1]=L'e'; moduleName[2]=L'r'; moduleName[3]=L'n';
	moduleName[4]=L'e'; moduleName[5]=L'l'; moduleName[6]=L'3'; moduleName[7]=L'2';
	moduleName[8]=L'.'; moduleName[9]=L'D'; moduleName[10]=L'L'; moduleName[11]=L'L'; moduleName[12]=0;
	// Resolve the module handle
	HANDLE kernel32Base = ResolveModuleHandle(peb,	moduleName);
	// Validate the module handle
	if (kernel32Base == NULL)
		return -2;
		
	// Name of the function to resolve
	CHAR functionName[14];
	functionName[0]='W'; functionName[1]='r'; functionName[2]='i'; functionName[3]='t';
	functionName[4]='e'; functionName[5]='C'; functionName[6]='o'; functionName[7]='n';
	functionName[8]='s'; functionName[9]='o'; functionName[10]='l'; functionName[11]='e';
	functionName[12]='A'; functionName[13]=0;
	// Resolve the function address
	WriteConsoleA_t WriteConsoleAFunc = (WriteConsoleA_t)ResolveFunctionAddress(kernel32Base, functionName);
	// Validate the function address
	if (WriteConsoleAFunc == NULL)
		return -1;
	// Message to print
	CHAR message[15];
	message[0] = 'H'; message[1] = 'e'; message[2] = 'l'; message[3] = 'l';
	message[4] = 'o'; message[5] = ','; message[6] = ' ';
	message[7] = 'W'; message[8] = 'o'; message[9] = 'r'; message[10] = 'l';
	message[11] = 'd'; message[12] = '!'; message[13] = '\n'; message[14] = 0;
	// Call the resolved function to print the message
	WriteConsoleAFunc(peb->ProcessParameters->StandardOutput, message, sizeof(message), NULL, NULL);

	return 0;
}

