#include "pe.h"

#if defined(PLATFORM_WINDOWS)

// Get the address of a function by its name from a module base address
FARPROC ResolveFunctionAddress(HANDLE hModule, const CHAR* functionName) {
	// Getting the export directory from the module base address
	PIMAGE_EXPORT_DIRECTORY exportDirectory = (PIMAGE_EXPORT_DIRECTORY)((PCHAR)hModule + ((PIMAGE_NT_HEADERS)((PCHAR)hModule + ((PIMAGE_DOS_HEADER)hModule)->e_lfanew))->OptionalHeader.DataDirectory[0].VirtualAddress);
	// Loop through the names in the export directory
	for (UINT32 i = 0; i < exportDirectory->NumberOfNames; ++i) {
		// Getting the address of the function name
		PCHAR pszVar = (PCHAR)hModule + ((INT32*)((PCHAR)hModule + exportDirectory->AddressOfNames))[i];
		// Compare the function name with the target function name
		if (CompareStringIgnoreCase(pszVar, functionName)) {
			// Return the address of the function if a match is found
			return (FARPROC)((PCHAR)hModule + ((INT32*)((PCHAR)hModule + exportDirectory->AddressOfFunctions))[((PUINT16)((PCHAR)hModule + exportDirectory->AddressOfNameOrdinals))[i]]);
		}
	}
	return NULL; // Function was not found
}

#endif
