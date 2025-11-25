# c-shellcode

## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Usage](#usage)
- [Files](#files)
- [Requirements](#requirements)
- [Detection & Ethics Note](#detection--ethics-note)
- [References](#references)

A minimal C project demonstrating manual Windows API resolution and shellcode techniques.

## Overview
This project shows how to:
- Manually locate the Process Environment Block (PEB)
- Enumerate loaded modules to find the base address of `Kernel32.dll`
- Parse PE headers to resolve the address of exported functions (e.g., `WriteConsoleA`)
- Print a message to the console using only resolved addresses, without standard library calls

## Features
- No reliance on standard Windows headers or libraries
- Custom type definitions and PE/NT structures
- Works on x86 and x64 Windows
- Demonstrates techniques useful for shellcode and low-level Windows internals

## Usage
1. Build the project using the provided batch files:
   - `build.bat` or `compile.bat`
2. Run the resulting executable. It should print:
   ```
   Hello world!
   ```

## Files
- `src/main.c`: Main logic for module/function resolution and message printing
- `src/types.h`: Custom type and structure definitions for Windows internals
- `build.bat`, `compile.bat`, `install_mingw.bat`: Build and setup scripts

## Requirements
- Windows (x86 or x64)
- MinGW or compatible C compiler

## Detection & Ethics Note

**Research-only.**
- This technique does not guarantee stealth. Security products may detect hardware breakpoint usage, VEH patterns, or emulator behavior.
- Do not use to evade detection, run untrusted code, or break laws/policies.
- Always test in isolated, offline VMs and follow responsible disclosure and research ethics.

## References
Add references to documentation, articles, or resources here.