#!/usr/bin/env bash

# Usage: ./build.sh <target-triple> "<sources>" <baseaddr>
# Example:
#   ./build.sh x86_64-pc-windows-msvc "src/main.c src/peb.c" 0x140001000

set -u  # treat unset vars as error

# Adjust this path for your environment (MSYS2 / WSL / native Linux with LLVM installed)
export PATH="/usr/lib/llvm-21/bin:$PATH"

TARGET="$1"   # e.g. x86_64-pc-windows-msvc
SOURCES="$2"  # e.g. "src/main.c src/pe.c"
BASEADDR="$3" # e.g. 0x140001000

OUT_DIR="bin/windows"
mkdir -p "$OUT_DIR"

OUT_EXE="${OUT_DIR}/${TARGET}.exe"
OUT_BIN="${OUT_DIR}/${TARGET}.bin"
OUT_DISASM="${OUT_DIR}/${TARGET}_disasm.txt"
OUT_SECTIONS="${OUT_DIR}/${TARGET}_sections.txt"
OUT_STRINGS="${OUT_DIR}/${TARGET}_strings.txt"

# -----------------------------
# Compile & link with clang/lld
# -----------------------------
clang -O0 -Qn -fuse-ld=lld \
    -target "$TARGET" \
    -nostdinc -nostartfiles -nodefaultlibs \
    -nostdlib -fno-ident -mno-stack-arg-probe -fno-stack-check -ffunction-sections -fdata-sections \
    -fno-asynchronous-unwind-tables \
    -fno-unwind-tables \
    -fno-exceptions \
    -Wl,/Entry:mainCRTStartup,/SUBSYSTEM:CONSOLE,/ORDER:@orderfile.txt,/BASE:"$BASEADDR" \
    -o "$OUT_EXE" \
    $SOURCES

# If clang failed, stop here (similar to `if errorlevel 1 goto :end`)
if [[ $? -ne 0 ]]; then
    echo "clang failed, aborting."
    exit 1
fi

# -----------------------------
# Post-processing
# -----------------------------
llvm-objcopy --dump-section=.text="$OUT_BIN" "$OUT_EXE"
llvm-objdump -d -s -j .text "$OUT_EXE" > "$OUT_DISASM"
llvm-objdump -h "$OUT_EXE" > "$OUT_SECTIONS"
llvm-strings "$OUT_BIN" > "$OUT_STRINGS"

# -----------------------------
# filesize function (like :filesize in .bat)
# -----------------------------
filesize() {
    local file="$1"
    if [[ -f "$file" ]]; then
        # On GNU coreutils (Linux / MSYS2)
        stat -c%s "$file"
    else
        echo 0
    fi
}

SIZE=$(filesize "$(pwd)/$OUT_BIN")
echo "file size is $SIZE"
