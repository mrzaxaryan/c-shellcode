#include "environment.h"


VOID exitWithCode(INT32 code);
INT32 mainCRTStartup() {

	// Message to print
	CHAR message[15];
	message[0] = 'H'; message[1] = 'e'; message[2] = 'l'; message[3] = 'l';
	message[4] = 'o'; message[5] = ','; message[6] = ' ';
	message[7] = 'W'; message[8] = 'o'; message[9] = 'r'; message[10] = 'l';
	message[11] = 'd'; message[12] = '!'; message[13] = '\n'; message[14] = 0;

	WriteConsole(message, sizeof(message));

#if defined(PLATFORM_LINUX)
	exitWithCode(0);
#endif
	
	return 0;
}


VOID exitWithCode(INT32 code) {
#if defined(PLATFORM_LINUX_AMD64)
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

