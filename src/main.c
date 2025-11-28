#include "environment.h"

// Function pointer type for WriteConsoleA_t function
typedef BOOL(WINAPI* WriteConsoleA_t)(HANDLE hConsoleOutput, LPCSTR lpBuffer, UINT32 nNumberOfCharsToWrite, UINT32* lpNumberOfCharsWritten, UINT32* lpReserved);
void print(const PCHAR s,  SIZE len) ;
void exitSystemCall(int code);
int mainCRTStartup() {
#if defined(PLATFORM_WINDOWS)
	PPEB peb = GetCurrentPEB(); // Get the current process's PEB pointer

	// Name of the module to resolve
	WCHAR moduleName[13];
	moduleName[0]=L'K'; moduleName[1]=L'e'; moduleName[2]=L'r'; moduleName[3]=L'n';
	moduleName[4]=L'e'; moduleName[5]=L'l'; moduleName[6]=L'3'; moduleName[7]=L'2';
	moduleName[8]=L'.'; moduleName[9]=L'D'; moduleName[10]=L'L'; moduleName[11]=L'L'; moduleName[12]=0;
	// Resolve the module handle
	HANDLE kernel32Base = ResolveModuleHandle(peb,	moduleName);
	// Validate the module handle
	if (kernel32Base == NULL)
		return -2;
		
	// Name of the function to resolve
	CHAR functionName[14];
	functionName[0]='W'; functionName[1]='r'; functionName[2]='i'; functionName[3]='t';
	functionName[4]='e'; functionName[5]='C'; functionName[6]='o'; functionName[7]='n';
	functionName[8]='s'; functionName[9]='o'; functionName[10]='l'; functionName[11]='e';
	functionName[12]='A'; functionName[13]=0;
	// Resolve the function address
	WriteConsoleA_t WriteConsoleAFunc = (WriteConsoleA_t)ResolveFunctionAddress(kernel32Base, functionName);
	// Validate the function address
	if (WriteConsoleAFunc == NULL)
		return -1;
	// Message to print
	CHAR message[15];
	message[0] = 'H'; message[1] = 'e'; message[2] = 'l'; message[3] = 'l';
	message[4] = 'o'; message[5] = ','; message[6] = ' ';
	message[7] = 'W'; message[8] = 'o'; message[9] = 'r'; message[10] = 'l';
	message[11] = 'd'; message[12] = '!'; message[13] = '\n'; message[14] = 0;
	// Call the resolved function to print the message
	WriteConsoleAFunc(peb->ProcessParameters->StandardOutput, message, sizeof(message), NULL, NULL);
	#else
CHAR message[15];
	message[0] = 'H'; message[1] = 'e'; message[2] = 'l'; message[3] = 'l';
	message[4] = 'o'; message[5] = ','; message[6] = ' ';
	message[7] = 'W'; message[8] = 'o'; message[9] = 'r'; message[10] = 'l';
	message[11] = 'd'; message[12] = '!'; message[13] = '\n'; message[14] = 0;
	print(message, sizeof(message));
#endif
	exitSystemCall(0);
	return 0;
}
void print(const PCHAR s,  SIZE len) {
#if defined(PLATFORM_LINUX_X86_64)
    __asm__ volatile(
        "mov $1, %%rax\n" 	  // syscall: write = 1
        "mov $1, %%rdi\n" 	// file descriptor: stdout = 1
        "mov %0, %%rsi\n"  // pointer to the string to write
        "mov %1, %%rdx\n" // length of the string
        "syscall\n"
        :
        : "r"(s), "r"(len)
        : "rax", "rdi", "rsi", "rdx"
    );
#elif defined(PLATFORM_LINUX_ARM64)
	register long x0 __asm__("x0") = 1;      // fd = 1 (stdout)
    register const char *x1 __asm__("x1") = s;
    register long x2 __asm__("x2") = len;
    register long x8 __asm__("x8") = 64;     // SYS_write on aarch64

    __asm__ volatile(
        "svc 0"
        : "+r"(x0)                // x0 = return value (ssize_t)
        : "r"(x1), "r"(x2), "r"(x8)
        : "memory", "cc"
    );
	#elif defined(PLATFORM_LINUX_I386)
	_asm__ volatile(
        "movl $4, %%eax\n"    // SYS_write
        "movl $1, %%ebx\n"    // fd = stdout
        "movl %0, %%ecx\n"    // buffer
        "movl %1, %%edx\n"    // length
        "int $0x80\n"
        :
        : "r"(s), "r"(len)
        : "eax", "ebx", "ecx", "edx"
    );
#endif
}

  void exitSystemCall(int code) {
#if defined(PLATFORM_LINUX_X86_64)
	__asm__ volatile(
		"mov $60, %%rax\n"  // syscall: exit = 60
		"mov %0, %%rdi\n"   // exit code
		"syscall\n"
		:
		: "r"(code)
		: "rax", "rdi"
	);
#elif defined(PLATFORM_LINUX_ARM64)
	register long x0 __asm__("x0") = code; // exit code
	register long x8 __asm__("x8") = 93;    // SYS_exit on aarch64

	__asm__ volatile(
		"svc 0"
		:
		: "r"(x0), "r"(x8)
		: "memory", "cc"
	);
#elif defined(PLATFORM_LINUX_I386)
	__asm__ volatile(
		"movl $1, %%eax\n"   // SYS_exit
		"movl %0, %%ebx\n"   // exit code
		"int $0x80\n"
		:
		: "r"(code)
		: "eax", "ebx"
	);
#endif
}

