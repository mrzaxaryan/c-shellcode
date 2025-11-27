#ifndef __STRING_H__
#define __STRING_H__

#include "primitives.h"

// Custom case-insensitive string comparison
BOOL CompareStringIgnoreCase(const CHAR* str1, const CHAR* str2);

// Custom case-insensitive wide string comparison
BOOL CompareWideStringIgnoreCase(const WCHAR* str1, const WCHAR* str2);

// Get the length of a null-terminated string
USIZE GetStringLength(const PCHAR str);

#endif // __STRING_H__