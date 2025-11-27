#include "environment.h"
#include "primitives.h"
#include "peb.h"
#include "pe.h"

// Function pointer type for WriteConsoleA_t function
typedef BOOL(WINAPI* WriteConsoleA_t)(HANDLE hConsoleOutput, LPCSTR lpBuffer, UINT32 nNumberOfCharsToWrite, UINT32* lpNumberOfCharsWritten, UINT32* lpReserved);

int mainCRTStartup() {

	PPEB peb = GetCurrentPEB(); // Get the current process's PEB pointer

	// Name of the module to resolve
	WCHAR moduleName[] = {L'K',L'e',L'r',L'n',L'e',L'l',L' ',L'3',L'2',L'.',L'd',L'l',L'l',0};
	// Resolve the module handle
	HANDLE kernel32Base = ResolveModuleHandle(peb,	moduleName);
	// Validate the module handle
	if (kernel32Base == NULL)
		return -2;
		
	// Name of the function to resolve
	CHAR functionName[] = {'W','r','i','t','e','C','o','n','s','o','l','e','A',0};
	// Resolve the function address
	WriteConsoleA_t WriteConsoleAFunc = (WriteConsoleA_t)ResolveFunctionAddress(kernel32Base, functionName);
	// Validate the function address
	if (WriteConsoleAFunc == NULL)
		return -1;
	// Message to print
	CHAR message[] = {'H','e','l','l','o',',',' ','W','o','r','l','d','!','\n',0};
	// Call the resolved function to print the message
	WriteConsoleAFunc(peb->ProcessParameters->StandardOutput, message, sizeof(message), NULL, NULL);

	return 0;
}

