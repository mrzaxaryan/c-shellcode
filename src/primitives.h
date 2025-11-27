#ifndef __PRIMITIVES_H__
#define __PRIMITIVES_H__

#include "architecture.h"

#define TRUE    ((BOOL)1)
#define FALSE   ((BOOL)0)
#define towlower(c) (((c) >= L'A' && (c) <= L'Z') ? ((c) + (L'a' - L'A')) : (c))
#define tolower(c) (((c) >= 'A' && (c) <= 'Z') ? ((c) + ('a' - 'A')) : (c))
#define NULL ((PVOID)0)

typedef void VOID, * PVOID,** PPVOID;

typedef signed char INT8, * PINT8;
typedef unsigned char UINT8, * PUINT8, ** PPUINT8;

typedef signed short int INT16, * PINT16;
typedef unsigned short int UINT16, * PUINT16;

typedef signed long int INT32, * PINT32;
typedef unsigned long int UINT32, * PUINT32, ** PPUINT32;

typedef signed long long int INT64, * PINT64;
typedef unsigned long long int UINT64, * PUINT64,** PPUINT64;

typedef char CHAR, * PCHAR, ** PPCHAR;
typedef unsigned char UCHAR, * PUCHAR;

typedef UINT16 WCHAR, * PWCHAR, ** PPWCHAR;

typedef UINT8 BOOL, * PBOOL,** PPBOOL;


#if defined(ENVIRONMENT_x86_64)
    typedef UINT64 USIZE , * PUSIZE;
    typedef INT64 SIZE , * PSIZE;
#else
    typedef UINT32 USIZE , * PUSIZE;
    typedef INT32 SIZE , * PSIZE;
#endif 

typedef PVOID HANDLE;
typedef HANDLE* PHANDLE;
typedef HANDLE HMODULE;

typedef const CHAR* LPCSTR, * PCSTR;
typedef PVOID FARPROC, * PFARPROC;

#endif // __PRIMITIVES_H__
