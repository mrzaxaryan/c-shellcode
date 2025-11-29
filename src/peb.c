#include "peb.h"

#if defined(PLATFORM_WINDOWS)

// Returns the current process's PEB pointer
PPEB GetCurrentPEB() {
    PPEB peb;
#if defined(PLATFORM_WINDOWS_AMD64)
    asm("movq %%gs:%1, %0" : "=r" (peb) : "m" (*(PUINT64)(0x60)));
#elif defined(PLATFORM_WINDOWS_I386)
    asm("movl %%fs:%1, %0" : "=r" (peb) : "m" (*(PUINT32)(0x30)));
#elif defined(PLATFORM_WINDOWS_ARM64)
	asm("ldr %0, [x18, #%1]"
        : "=r"(peb)
        : "i"(0x60));
#elif defined(PLATFORM_WINDOWS_ARM32)
	#error ARM32 architecture is not yet supported
#else
	#error Unsupported platform
#endif
    return peb;
}

// Get the base address of a module by its name
PVOID ResolveModuleHandle(PPEB peb, const PWCHAR moduleName) {
	PLIST_ENTRY entry = peb->LoaderData->InMemoryOrderModuleList.Flink; // Getting the first entry in the InMemoryOrderModuleList
	PVOID firstEntry = entry; // Save the first entry to detect when we loop back to it

	do {
		PLDR_MODULE entryData = (PLDR_MODULE)entry; // Cast the entry to a PLDR_MODULE structure
		// Check if the FullDllName.Buffer is NULL
		if (entryData->FullDllName.Buffer == NULL)
			break;
		// Compare the module name with the target module name
		if (CompareWideStringIgnoreCase(entryData->FullDllName.Buffer, moduleName)) {
			return ((PLDR_DATA_TABLE_ENTRY)entry)->DllBase; // Return the base address if a match is found
		}
		entry = entry->Flink; // Move to the next entry in the list
	} while (entry != NULL && entry != firstEntry); // Loop until we either find the module or loop back to the first entry

	return NULL; // Return NULL if the module was not found
}

#endif // PLATFORM_WINDOWS