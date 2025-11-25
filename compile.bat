@echo off
setlocal enabledelayedexpansion

REM === Target directory ===
set MINGW_DIR=mingw64
set INSTALL_SCRIPT=install_mingw.bat
call "%INSTALL_SCRIPT%" || (
        echo Install failed.
        exit /b 1
    )
set "PATH=%CD%\%MINGW_DIR%\bin;%PATH%"

:compile
REM ============================
REM Compile with gcc (all args passed to this .bat)
REM Example:
REM   build.bat main.c -o main.exe
REM ============================
if "%~1"=="" (
    echo No files/arguments passed to gcc. Skipping compilation.
    goto :end
)

gcc -m32 -nostdlib -fno-asynchronous-unwind-tables -fno-unwind-tables -fno-exceptions -Wl,-T script.ld -o raw.exe %*
if errorlevel 1 (
    echo GCC compilation failed.
    goto :end
)
objdump -x raw.exe
:end
endlocal