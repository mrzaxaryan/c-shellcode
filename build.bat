@echo off
setlocal enabledelayedexpansion

call compile-linux.bat i386-pc-linux-gnu src\*.c
if errorlevel 1 goto :end

call compile-linux.bat x86_64-pc-linux-gnu src\*.c
if errorlevel 1 goto :end

call compile-linux.bat aarch64-pc-linux-gnu src\*.c
if errorlevel 1 goto :end

call compile-windows.bat i386-pc-windows-msvc src\*.c 0x400000
if errorlevel 1 goto :end

call compile-windows.bat x86_64-pc-windows-msvc src\*.c 0x140000000
if errorlevel 1 goto :end

call compile-windows.bat aarch64-pc-windows-msvc src\*.c 0x0000000140000000
if errorlevel 1 goto :end

:end
endlocal
