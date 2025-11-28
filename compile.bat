@echo off
setlocal enabledelayedexpansion

set "PATH=C:\Program Files\LLVM\bin;%PATH%"

mkdir bin 2>nul

clang --verbose -O0 -Qn -fuse-ld=lld ^
    -target %1 ^
	-nostdinc -nostartfiles -nodefaultlibs ^
    -nostdlib -fno-ident -mno-stack-arg-probe -fno-stack-check -ffunction-sections -fdata-sections ^
    -fno-asynchronous-unwind-tables ^
    -fno-unwind-tables ^
    -fno-exceptions ^
    -Wl,/Entry:mainCRTStartup,/SUBSYSTEM:CONSOLE,/ORDER:@orderfile.txt,/BASE:%3 ^
    -o bin\%1.exe ^
    %2

if errorlevel 1 (
    goto :end
)


llvm-objcopy --dump-section=.text=bin\%1.bin bin\%1.exe
llvm-objdump -d -s -j .text bin\%1.exe
llvm-objdump -h bin\%1.exe

call :filesize "%CD%\bin\%1.bin"
echo file size is %size%
goto :eof

:filesize
set "size=0"
for %%A in (%1) do set "size=%%~zA"
goto :eof

:end
endlocal
