@echo off
setlocal enabledelayedexpansion

REM ============================================
REM  Configuration
REM ============================================
set "MINGW_DIR=mingw64"

REM Prepend MinGW to PATH (only for this script)
set "PATH=%CD%\%MINGW_DIR%\bin;%PATH%"


REM ============================================
REM  Compile section
REM ============================================
:compile

if "%~1"=="" (
    echo [!] No input files or arguments passed to GCC.
    echo Usage: build.bat file.c [options]
    goto :end
)

mkdir bin 2>nul

gcc -m32 -Os -Qn ^
	-nostdinc ^
    -nostdlib -fno-ident -mno-stack-arg-probe -fno-stack-check ^
    -fno-asynchronous-unwind-tables ^
    -fno-unwind-tables ^
    -fno-exceptions ^
    -Wl,-T script.ld ^
    -o bin\out.exe ^
    %*

if errorlevel 1 (
    echo [!] GCC compilation failed.
    goto :end
)


objcopy -j .text -O binary bin\out.exe bin\out.bin

call :filesize "%CD%\bin\out.bin"
echo file size is %size%
goto :eof

:filesize
set "size=0"
for %%A in (%1) do set "size=%%~zA"
goto :eof

:end
endlocal
