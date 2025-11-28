@echo off
setlocal enabledelayedexpansion

set "PATH=C:\Program Files\LLVM\bin;%PATH%"

clang -O0 -Qn -fuse-ld=lld ^
    -target %1 ^
	-nostdinc -nostartfiles -nodefaultlibs ^
    -nostdlib -fno-ident -mno-stack-arg-probe -fno-stack-check -ffunction-sections -fdata-sections ^
    -fno-asynchronous-unwind-tables ^
    -fno-unwind-tables ^
    -fno-exceptions ^
    -Wl,/Entry:mainCRTStartup,/SUBSYSTEM:CONSOLE,/ORDER:@orderfile.txt,/BASE:%3 ^
    -o bin\windows\%1.exe ^
    %2

if errorlevel 1 (
    goto :end
)


llvm-objcopy --dump-section=.text=bin\windows\%1.bin bin\windows\%1.exe
llvm-objdump -d -s -j .text bin\windows\%1.exe > bin\windows\%1_disasm.txt
llvm-objdump -h bin\windows\%1.exe > bin\windows\%1_sections.txt

call :filesize "%CD%\bin\windows\%1.bin"
echo file size is %size%
goto :eof

:filesize
set "size=0"
for %%A in (%1) do set "size=%%~zA"
goto :eof

:end
endlocal
