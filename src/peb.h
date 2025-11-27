#ifndef PEB_STRUCTS_H
#define PEB_STRUCTS_H

#include "primitives.h"

#ifdef ENVIRONMENT_x86_64
    #define PEB_OFFSET 0x60
#elif defined(ENVIRONMENT_I386)
    #define PEB_OFFSET 0x30
#else
    #error Unsupported architecture
#endif // !WIN32

// Unicode string structure
typedef struct _UNICODE_STRING {
    UINT16 Length;
    UINT16 MaximumLength;
    PWCHAR Buffer;
} UNICODE_STRING, *PUNICODE_STRING;

// List entry structure for linked lists
typedef struct _LIST_ENTRY {
    struct _LIST_ENTRY* Flink;
    struct _LIST_ENTRY* Blink;
} LIST_ENTRY, *PLIST_ENTRY;

// Loader data table entry structure
typedef struct _LDR_DATA_TABLE_ENTRY {
    LIST_ENTRY InLoadOrderLinks;
    PVOID Reserved2[2];
    PVOID DllBase;
    UNICODE_STRING FullDllName;
} LDR_DATA_TABLE_ENTRY, *PLDR_DATA_TABLE_ENTRY;

// Loader module structure
typedef struct _LDR_MODULE {
    LIST_ENTRY InMemoryOrderModuleList;
    LIST_ENTRY InLoadOrderModuleList;
    LIST_ENTRY InInitializationOrderModuleList;
    PVOID BaseAddress;
    PVOID EntryPoint;
    UINT32 SizeOfImage;
    UNICODE_STRING FullDllName;
    UNICODE_STRING BaseDllName;
    UINT32 Flags;
    INT16 LoadCount;
    INT16 TlsIndex;
    LIST_ENTRY HashTableEntry;
    UINT32 TimeDateStamp;
} LDR_MODULE, *PLDR_MODULE;

// Process Environment Block Loader Data
typedef struct _PEB_LDR_DATA {
    UINT32 Length;
    UINT32 Initialized;
    PVOID SsHandle;
    LIST_ENTRY InLoadOrderModuleList;
    LIST_ENTRY InMemoryOrderModuleList;
    LIST_ENTRY InInitializationOrderModuleList;
} PEB_LDR_DATA, *PPEB_LDR_DATA;

// Process parameters structure
typedef struct _RTL_USER_PROCESS_PARAMETERS {
    UINT32 MaximumLength;
    UINT32 Length;
    UINT32 Flags;
    UINT32 DebugFlags;
    HANDLE ConsoleHandle;
    UINT32 ConsoleFlags;
    HANDLE StandardInput;
    HANDLE StandardOutput;
    HANDLE StandardError;
} RTL_USER_PROCESS_PARAMETERS, *PRTL_USER_PROCESS_PARAMETERS;

// Process Environment Block
typedef struct _PEB {
    BOOLEAN InheritedAddressSpace;
    BOOLEAN ReadImageFileExecOptions;
    BOOLEAN BeingDebugged;
    BOOLEAN Spare;
    HANDLE Mutant;
    PVOID ImageBase;
    PPEB_LDR_DATA LoaderData;
    PRTL_USER_PROCESS_PARAMETERS ProcessParameters;
} PEB, *PPEB;

#endif // PEB_STRUCTS_H
