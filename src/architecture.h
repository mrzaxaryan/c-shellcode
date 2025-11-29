#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#if defined(_WIN32)

    #define PLATFORM_WINDOWS

    #if defined(__x86_64__) || defined(_M_X64)
        #define PLATFORM_WINDOWS_AMD64
        #define ARCHITECTURE_AMD64
    #elif defined(__i386__) || defined(_M_IX86)
        #define PLATFORM_WINDOWS_I386
        #define ARCHITECTURE_I386
    #elif defined(__aarch64__) || defined(_M_ARM64)
        #define PLATFORM_WINDOWS_ARM64
        #define ARCHITECTURE_ARM64
    #elif defined(__arm__) || defined(_M_ARM)
        #define PLATFORM_WINDOWS_ARM32
        #define ARCHITECTURE_ARM32
    #else
        #error "Unknown Windows architecture"
    #endif

#elif defined(__linux__)

    #define PLATFORM_LINUX
    
    #if defined(__x86_64__)
        #define PLATFORM_LINUX_AMD64
        #define ARCHITECTURE_AMD64
    #elif defined(__i386__)
        #define PLATFORM_LINUX_I386
        #define ARCHITECTURE_I386
    #elif defined(__aarch64__)
        #define PLATFORM_LINUX_ARM64
        #define ARCHITECTURE_ARM64
    #elif defined(__arm__)
        #define PLATFORM_LINUX_ARM32
        #define ARCHITECTURE_ARM32
    #else
        #error "Unknown Linux architecture"
    #endif

#else
    #error "Unsupported platform"
#endif

#endif // __PLATFORM_H__

