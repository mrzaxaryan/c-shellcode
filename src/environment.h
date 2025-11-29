#ifndef __ENVIRONMENT_H__
#define __ENVIRONMENT_H__

#include "primitives.h"

#if defined(PLATFORM_WINDOWS)
#include "peb.h"
#include "pe.h"

#define ExitWithCode(code)  return code

#elif defined(PLATFORM_LINUX)
VOID ExitWithReturnCode(INT32 code); 
#define ExitWithCode(code)  ExitWithReturnCode(code); return code
#endif

#include "console.h"

#if defined(PLATFORM_WINDOWS_I386)
	#define WINAPI  __stdcall
#else
	#define WINAPI  
#endif

#endif // __ENVIRONMENT_H__
