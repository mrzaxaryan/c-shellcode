#include "pe.h"

// Custom case-insensitive string comparison
static BOOL CompareStringIgnoreCase(const CHAR* str1, const CHAR* str2) {
	// Loop through each character in both strings
	while (*str1 && *str2) {
		// Convert to lowercase for case-insensitive comparison
		CHAR c1 = tolower(*str1);
		CHAR c2 = tolower(*str2);
		// Compare the characters
		if (c1 != c2) {
			return FALSE; // They differ in case-folded form
		}
		// Move to the next characters
		str1++;
		str2++;
	}
	return (*str1 == *str2); // Both must land on the null terminator together
}

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
