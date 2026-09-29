#!/bin/bash
echo "🔨 Building AutoAI-OS for ARM64 (AArch64) Architecture..."

# Check cross compiler
if ! command -v aarch64-linux-gnu-gcc &> /dev/null
then
    echo "⚠️ 'aarch64-linux-gnu-gcc' not found!"
    echo "Install it via: sudo apt install gcc-aarch64-linux-gnu qemu-system-arm"
    exit 1
fi

# Flags for Bare-Metal GCC
FLAGS="-O3 -Wall -Wno-format -ffreestanding -nostdlib -Iinclude"

# Compile ARM64 Assembly Bootstrap
aarch64-linux-gnu-gcc -c boot/arm64_bootloader.S -o boot/arm64_boot.o

# Compile C-Kernel Files for ARM64
aarch64-linux-gnu-gcc $FLAGS -c kernel/main.c -o kernel/main_arm64.o
aarch64-linux-gnu-gcc $FLAGS -c kernel/hal.c -o kernel/hal_arm64.o
aarch64-linux-gnu-gcc $FLAGS -c kernel/memory.c -o kernel/memory_arm64.o
aarch64-linux-gnu-gcc $FLAGS -c kernel/ai_engine.c -o kernel/ai_engine_arm64.o
aarch64-linux-gnu-gcc $FLAGS -c kernel/scheduler.c -o kernel/scheduler_arm64.o
aarch64-linux-gnu-gcc $FLAGS -c kernel/interrupts.c -o kernel/interrupts_arm64.o
aarch64-linux-gnu-gcc $FLAGS -c kernel/bus_driver.c -o kernel/bus_driver_arm64.o
aarch64-linux-gnu-gcc $FLAGS -c kernel/vfs.c -o kernel/vfs_arm64.o

# Link ARM64 ELF Binary
aarch64-linux-gnu-ld -T boot/linker_arm64.ld \
    boot/arm64_boot.o \
    kernel/main_arm64.o \
    kernel/hal_arm64.o \
    kernel/memory_arm64.o \
    kernel/ai_engine_arm64.o \
    kernel/scheduler_arm64.o \
    kernel/interrupts_arm64.o \
    kernel/bus_driver_arm64.o \
    kernel/vfs_arm64.o \
    -o autoai_kernel_arm64.elf

if [ $? -eq 0 ]; then
    echo "✅ ARM64 Kernel Binary Compiled Successfully: 'autoai_kernel_arm64.elf'"
fi
