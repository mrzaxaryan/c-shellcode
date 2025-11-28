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
    -Wl,-T,linker.script,-e,mainCRTStartup ^
    -o bin\linux\%1.elf ^
    %2

if errorlevel 1 (
    goto :end
)


llvm-objcopy --dump-section=.text=bin\linux\%1.bin bin\linux\%1.elf
llvm-objdump -d -s -j .text bin\linux\%1.elf > bin\linux\%1_disasm.txt
llvm-objdump -h bin\linux\%1.elf > bin\linux\%1_sections.txt
llvm-strings bin\linux\%1.bin > bin\linux\%1_strings.txt

call :filesize "%CD%\bin\linux\%1.bin"
echo file size is %size%
goto :eof

:filesize
set "size=0"
for %%A in (%1) do set "size=%%~zA"
goto :eof

:end
endlocal
