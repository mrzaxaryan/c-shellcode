@echo off
setlocal enabledelayedexpansion

REM === Target directory ===
set MINGW_DIR=mingw64

REM === Download URL ===
set MINGW_URL=https://github.com/brechtsanders/winlibs_mingw/releases/download/15.2.0posix-13.0.0-ucrt-r3/winlibs-x86_64-posix-seh-gcc-15.2.0-mingw-w64ucrt-13.0.0-r3.zip
set MINGW_ZIP=mingw64.zip



if exist "%MINGW_DIR%" (
    goto :addpath
)


REM ============================
REM Download the ZIP
REM ============================
curl -L -o "%MINGW_ZIP%" "%MINGW_URL%"
if %errorlevel% neq 0 (
    echo ERROR: Download failed.
    if exist "%MINGW_ZIP%" del "%MINGW_ZIP%"
    goto :end
)


REM ============================
REM Extract ZIP
REM ============================
tar -xf "%MINGW_ZIP%" >nul
if %errorlevel% neq 0 (
    echo ERROR: Failed to extract archive.
    echo Performing cleanup...
    if exist "%MINGW_ZIP%" del "%MINGW_ZIP%"
    if exist "%MINGW_DIR%" rmdir /s /q "%MINGW_DIR%"
    goto :end
)

REM ============================
REM Cleanup ZIP after success
REM ============================
del "%MINGW_ZIP%"

:addpath
REM ============================
REM Add MinGW bin to PATH
REM ============================
set "PATH=%CD%\%MINGW_DIR%\bin;%PATH%"
:end
exit /b %errorlevel%
endlocal