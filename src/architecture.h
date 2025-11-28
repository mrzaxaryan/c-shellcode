#ifndef __ARCHITECTURE_H__
#define __ARCHITECTURE_H__

// Check Compiler
#if !defined(__clang__ )
	#error Unsupported compiler
#endif

#if defined(__x86_64__) || defined(_M_X64) || defined(_M_AMD64) 
    #define ENVIRONMENT_X86_64
#elif defined(__i386__) || defined(_M_IX86)
    #define ENVIRONMENT_I386
#elif defined(__arm__) || defined(_M_ARM) 
	#define ENVIRONMENT_ARM32
	#error ARM32 architecture is not supported yet
#elif defined(__aarch64__) || defined(_M_ARM64) || defined(_M_ARM64EC)
    #define ENVIRONMENT_ARM64
#else
    #error Unsupported architecture
#endif



#if defined(ENVIRONMENT_I386)
	#define WINAPI  __stdcall
	#define WINAPIV __cdecl
#else
	#define WINAPI 
	#define WINAPIV 
#endif

#endif // __ARCHITECTURE_H__