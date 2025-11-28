#ifndef __PLATFORM_H__
#define __PLATFORM_H__

// ====================== WINDOWS ======================
#if defined(_WIN32)
#define PLATFORM_WINDOWS
    #if defined(__x86_64__) || defined(_M_X64)
        #define PLATFORM_WINDOWS_AMD64
        #define ARCHITECTURE_AMD64
    #elif defined(__i386__) || defined(_M_IX86)
        #define PLATFORM_WINDOWS_X86
        #define ARCHITECTURE_X86    
    #elif defined(__aarch64__) || defined(_M_ARM64)
        #define PLATFORM_WINDOWS_ARM64
        #define ARCHITECTURE_ARM64
    #elif defined(__arm__) || defined(_M_ARM)
        #define PLATFORM_WINDOWS_ARM32
        #define ARCHITECTURE_ARM32
    #else
        #define PLATFORM_WINDOWS_UNKNOWN
    #endif

// ====================== LINUX ======================
#elif defined(__linux__)
#define PLATFORM_LINUX
    #if defined(__x86_64__)
        #define PLATFORM_LINUX_AMD64
        #define ARCHITECTURE_AMD64
    #elif defined(__i386__)
        #define PLATFORM_LINUX_X86
        #define ARCHITECTURE_X86
    #elif defined(__aarch64__)
        #define PLATFORM_LINUX_ARM64
        #define ARCHITECTURE_ARM64
    #elif defined(__arm__)
        #define PLATFORM_LINUX_ARM32
        #define ARCHITECTURE_ARM32
    #else
        #define PLATFORM_LINUX_UNKNOWN
    #endif



// ====================== ANDROID ======================
#elif defined(__ANDROID__)
#error "Android platform detectio is not yet supported"
    #if defined(__aarch64__)
        #define PLATFORM_ANDROID_ARM64
        #define ARCHITECTURE_ARM64
    #elif defined(__arm__)
        #define PLATFORM_ANDROID_ARM32
        #define ARCHITECTURE_ARM32
    #elif defined(__x86_64__)
        #define PLATFORM_ANDROID_AMD64
        #define ARCHITECTURE_AMD64
    #elif defined(__i386__)
        #define PLATFORM_ANDROID_X86
        #define ARCHITECTURE_X86
    #else
        #define PLATFORM_ANDROID_UNKNOWN
    #endif



// ====================== APPLE (macOS/iOS) ======================
#elif defined(__APPLE__) && defined(__MACH__)
#error "Apple platform detection is not yet supported"
    #if TARGET_OS_IPHONE || TARGET_OS_IOS || TARGET_OS_SIMULATOR
        #if defined(__aarch64__)
            #define PLATFORM_IOS_ARM64
            #define ARCHITECTURE_ARM64
        #elif defined(__arm__)
            #define PLATFORM_IOS_ARM32
            #define ARCHITECTURE_ARM32
        #else
            #define PLATFORM_IOS_UNKNOWN
        #endif

    #else // macOS
        #if defined(__x86_64__)
            #define PLATFORM_MACOS_AMD64
            #define ARCHITECTURE_AMD64
        #elif defined(__aarch64__)
            #define PLATFORM_MACOS_ARM64
            #define ARCHITECTURE_ARM64
        #else
            #define PLATFORM_MACOS_UNKNOWN
        #endif
    #endif


// ====================== WASM ======================
#elif defined(__EMSCRIPTEN__)
#error "WASM platform detection is not yet supported"
    #if defined(__wasm32__)
        #define PLATFORM_WASM32
        #define ARCHITECTURE_WASM32
    #elif defined(__wasm64__)
        #define PLATFORM_WASM64
        #define ARCHITECTURE_WASM64
    #else
        #define PLATFORM_WASM_UNKNOWN
    #endif


// ====================== FALLBACK ======================
#else
    #define PLATFORM_UNKNOWN
#endif

#endif // __PLATFORM_H__

