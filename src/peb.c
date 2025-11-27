#include "environment.h"
#include "peb.h"

#ifdef ENVIRONMENT_x86_64
    #define PEB_OFFSET 0x60
#elif defined(ENVIRONMENT_I386)
    #define PEB_OFFSET 0x30
#else
    #error Unsupported architecture
#endif // !WIN32

// Returns the current process's PEB pointer
PPEB GetCurrentPEB() {
    PPEB peb;
#ifdef ENVIRONMENT_x86_64
    asm("movq %%gs:%1, %0" : "=r" (peb) : "m" (*(PUINT64)(PEB_OFFSET)));
#else // WIN32
    asm("movl %%fs:%1, %0" : "=r" (peb) : "m" (*(PUINT32)(PEB_OFFSET)));
#endif // WIN32
    return peb;
}

// Custom case-insensitive wide string comparison
static BOOL CompareWideStringIgnoreCase(const WCHAR* str1, const WCHAR* str2) {
	// Loop through each character in both strings
	while (*str1 && *str2) {
		// Convert to lowercase cause-insensitive comparison
		WCHAR c1 = towlower(*str1);
		WCHAR c2 = towlower(*str2);
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

// Get the base address of a module by its name
HMODULE ResolveModuleHandle(PPEB peb, const WCHAR* moduleName) {
	PLIST_ENTRY entry = peb->LoaderData->InMemoryOrderModuleList.Flink; // Getting the first entry in the InMemoryOrderModuleList
	PVOID firstEntry = entry; // Save the first entry to detect when we loop back to it

	do {
		PLDR_MODULE entryData = (PLDR_MODULE)entry; // Cast the entry to a PLDR_MODULE structure
		// Check if the FullDllName.Buffer is NULL
		if (entryData->FullDllName.Buffer == NULL)
			break;
		// Compare the module name with the target module name
		if (CompareWideStringIgnoreCase(entryData->FullDllName.Buffer, moduleName)) {
			return (HMODULE)((PLDR_DATA_TABLE_ENTRY)entry)->DllBase; // Return the base address if a match is found
		}
		entry = entry->Flink; // Move to the next entry in the list
	} while (entry != NULL && entry != firstEntry); // Loop until we either find the module or loop back to the first entry

	return NULL; // Return NULL if the module was not found
}