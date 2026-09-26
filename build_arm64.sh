#!/bin/bash
echo "🔨 Building AutoAI-OS for ARM64 (AArch64) Architecture..."

# Check cross compiler
if ! command -v aarch64-linux-gnu-gcc &> /dev/null
then
    echo "⚠️ 'aarch64-linux-gnu-gcc' not found!"
    echo "Install it via: sudo apt install gcc-aarch64-linux-gnu qemu-system-arm"
    exit 1
fi

# Compile ARM64 Assembly Bootstrap
aarch64-linux-gnu-gcc -c boot/arm64_bootloader.S -o boot/arm64_boot.o

# Compile C-Kernel Files for ARM64
aarch64-linux-gnu-gcc -O3 -Wall -ffreestanding -nostdlib -Iinclude \
    -c kernel/main.c -o kernel/main_arm64.o
aarch64-linux-gnu-gcc -O3 -Wall -ffreestanding -nostdlib -Iinclude \
    -c kernel/hal.c -o kernel/hal_arm64.o
aarch64-linux-gnu-gcc -O3 -Wall -ffreestanding -nostdlib -Iinclude \
    -c kernel/memory.c -o kernel/memory_arm64.o
aarch64-linux-gnu-gcc -O3 -Wall -ffreestanding -nostdlib -Iinclude \
    -c kernel/ai_engine.c -o kernel/ai_engine_arm64.o

# Link ARM64 ELF Binary
aarch64-linux-gnu-ld -T boot/linker_arm64.ld \
    boot/arm64_boot.o \
    kernel/main_arm64.o \
    kernel/hal_arm64.o \
    kernel/memory_arm64.o \
    kernel/ai_engine_arm64.o \
    -o autoai_kernel_arm64.elf

echo "✅ ARM64 Kernel Binary Compiled Successfully: 'autoai_kernel_arm64.elf'"
echo "🚀 Test in QEMU ARM64 via:"
echo "   qemu-system-aarch64 -M virt -cpu cortex-a57 -nographic -kernel autoai_kernel_arm64.elf"
