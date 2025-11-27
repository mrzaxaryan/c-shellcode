#ifndef __ENVIRONMENT_H__
#define __ENVIRONMENT_H__

// Check Compiler
#if !defined(__GNUC__)
	#error Unsupported compiler
#endif

#if defined(__x86_64__) || defined(__amd64__) || defined(_M_X64)
	#define ENVIRONMENT_x86_64
#elif defined(__i386__) || defined(_M_IX86)
	#define ENVIRONMENT_I386
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

#endif // __ENVIRONMENT_H__
