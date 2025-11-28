#!/usr/bin/env bash

set -e  # stop on any error (equiv. to "if errorlevel goto :end")

# ------------------------
# Cleanup + directory setup
# ------------------------
rm -rf bin 2>/dev/null || true

mkdir -p bin/windows
mkdir -p bin/linux

# ------------------------
# Compile Linux targets
# ------------------------
./compile-linux.sh i386-pc-linux-gnu     src/*.c
./compile-linux.sh x86_64-pc-linux-gnu   src/*.c
./compile-linux.sh aarch64-pc-linux-gnu  src/*.c

# ------------------------
# Compile Windows targets
# ------------------------
./compile-windows.sh i386-pc-windows-msvc    "src/*.c" 0x400000
./compile-windows.sh x86_64-pc-windows-msvc  "src/*.c" 0x140000000
./compile-windows.sh aarch64-pc-windows-msvc "src/*.c" 0x0000000140000000
