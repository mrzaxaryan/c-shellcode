@echo off
setlocal enabledelayedexpansion

rmdir /s /q bin 2>nul
mkdir bin\windows 2>nul
mkdir bin\linux 2>nul

call compile-linux.bat i386-unknown-linux-gnu src\*.c
if errorlevel 1 goto :end

call compile-linux.bat x86_64-unknown-linux-gnu src\*.c
if errorlevel 1 goto :end

call compile-linux.bat aarch64-unknown-linux-gnu src\*.c
if errorlevel 1 goto :end

call compile-windows.bat i386-unknown-windows-msvc src\*.c 0x400000
if errorlevel 1 goto :end

call compile-windows.bat x86_64-unknown-windows-msvc src\*.c 0x140000000
if errorlevel 1 goto :end

call compile-windows.bat aarch64-unknown-windows-msvc src\*.c 0x0000000140000000
if errorlevel 1 goto :end

:end
endlocal
