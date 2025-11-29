#include "console.h"
#include "environment.h"

#if defined(PLATFORM_WINDOWS)

// Function pointer type for WriteConsoleA_t function
typedef BOOL(WINAPI* WriteConsoleA_t)(PVOID hConsoleOutput, LPCSTR lpBuffer, UINT32 nNumberOfCharsToWrite, UINT32* lpNumberOfCharsWritten, UINT32* lpReserved);

VOID WriteConsole(const PCHAR output,  USIZE outputLength){
	PPEB peb = GetCurrentPEB(); // Get the current process's PEB pointer

	// Name of the module to resolve
	WCHAR moduleName[13];
	moduleName[0]=L'K'; moduleName[1]=L'e'; moduleName[2]=L'r'; moduleName[3]=L'n';
	moduleName[4]=L'e'; moduleName[5]=L'l'; moduleName[6]=L'3'; moduleName[7]=L'2';
	moduleName[8]=L'.'; moduleName[9]=L'D'; moduleName[10]=L'L'; moduleName[11]=L'L'; moduleName[12]=0;
	// Resolve the module handle
	PVOID kernel32Base = ResolveModuleHandle(peb,	moduleName);
	// Validate the module handle
	if (kernel32Base == NULL)
		return;
		
	// Name of the function to resolve
	CHAR functionName[14];
	functionName[0]='W'; functionName[1]='r'; functionName[2]='i'; functionName[3]='t';
	functionName[4]='e'; functionName[5]='C'; functionName[6]='o'; functionName[7]='n';
	functionName[8]='s'; functionName[9]='o'; functionName[10]='l'; functionName[11]='e';
	functionName[12]='A'; functionName[13]=0;
	// Resolve the function address
	WriteConsoleA_t writeConsoleAFunc = (WriteConsoleA_t)ResolveFunctionAddress(kernel32Base, functionName);
	// Validate the function address
	if (writeConsoleAFunc == NULL)
		return;
	// Call the WriteConsoleA function
	writeConsoleAFunc(peb->ProcessParameters->StandardOutput, output, outputLength, NULL, NULL);
}

#endif