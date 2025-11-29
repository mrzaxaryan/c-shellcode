#ifndef __ENVIRONMENT_H__
#define __ENVIRONMENT_H__

#include "primitives.h"

#if defined(PLATFORM_WINDOWS)
#include "peb.h"
#include "pe.h"
#endif

#include "console.h"

#if defined(PLATFORM_WINDOWS_I386)
	#define WINAPI  __stdcall
#else
	#define WINAPI  
#endif

#endif // __ENVIRONMENT_H__
