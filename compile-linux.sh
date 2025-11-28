#!/usr/bin/env bash

# Usage:
#   ./build_linux.sh <target-triple> "<sources>"
# Example:
#   ./build_linux.sh x86_64-pc-linux-gnu "src/main.c src/peb.c"

set -u  # error on unset vars

export PATH="/usr/lib/llvm-21/bin:$PATH"

TARGET="$1"    # e.g. x86_64-pc-linux-gnu
SOURCES="$2"   # e.g. "src/main.c src/pe.c"

OUT_DIR="bin/linux"
mkdir -p "$OUT_DIR"

OUT_ELF="${OUT_DIR}/${TARGET}.elf"
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
    -Wl,-T,linker.script,-e,mainCRTStartup \
    -o "$OUT_ELF" \
    $SOURCES

# If clang failed, stop (like `if errorlevel 1 goto :end`)
if [[ $? -ne 0 ]]; then
    echo "clang failed, aborting."
    exit 1
fi

# -----------------------------
# Post-processing
# -----------------------------
llvm-objcopy --dump-section=.text="$OUT_BIN" "$OUT_ELF"
llvm-objdump -d -s -j .text "$OUT_ELF" > "$OUT_DISASM"
llvm-objdump -h "$OUT_ELF" > "$OUT_SECTIONS"
llvm-strings "$OUT_BIN" > "$OUT_STRINGS"

# -----------------------------
# filesize function (like :filesize)
# -----------------------------
filesize() {
    local file="$1"
    if [[ -f "$file" ]]; then
        # GNU coreutils stat (Linux / MSYS2 / WSL)
        stat -c%s "$file"
    else
        echo 0
    fi
}

SIZE=$(filesize "$(pwd)/$OUT_BIN")
echo "file size is $SIZE"
