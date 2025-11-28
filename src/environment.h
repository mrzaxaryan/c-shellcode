#ifndef __ENVIRONMENT_H__
#define __ENVIRONMENT_H__

#include "primitives.h"

#if defined(PLATFORM_WINDOWS)
#include "peb.h"
#include "pe.h"
#endif

#if defined(PLATFORM_WINDOWS_X86) 
	#define WINAPI  __stdcall
	#define WINAPIV __cdecl
#else
	#define WINAPI  
	#define WINAPIV 
#endif

#endif // __ENVIRONMENT_H__
