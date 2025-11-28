@echo off
setlocal enabledelayedexpansion

call compile.bat i386-pc-windows-msvc src\*.c 0x400000
if errorlevel 1 goto :end

call compile.bat x86_64-pc-windows-msvc src\*.c 0x140000000
if errorlevel 1 goto :end

call compile.bat aarch64-pc-windows-msvc src\*.c 0x0000000140000000
if errorlevel 1 goto :end

:end
endlocal
