#ifndef __ENVIRONMENT_H__
#define __ENVIRONMENT_H__

#include "primitives.h"
#include "peb.h"
#include "pe.h"

#if defined(ENVIRONMENT_I386)
	#define WINAPI  __stdcall
	#define WINAPIV __cdecl
#else
	#define WINAPI  
	#define WINAPIV 
#endif

#endif // __ENVIRONMENT_H__
