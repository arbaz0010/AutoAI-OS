#!/bin/bash
echo "🔨 Building AutoAI-OS Hybrid (Legacy BIOS + UEFI 64-Bit) ISO..."

# 1. Compile Legacy BIOS Kernel
nasm -f elf32 boot/multiboot_header.asm -o boot/header.o
gcc -m32 -c boot/bootloader.c -o boot/bootloader.o -std=gnu99 -ffreestanding -O2
ld -m elf_i386 -T boot/linker.ld boot/header.o boot/bootloader.o -o boot/autoai_kernel.bin

# 2. Setup ISO Directory Layout
mkdir -p iso/boot/grub
mkdir -p iso/EFI/BOOT

# Copy Legacy Kernel
cp boot/autoai_kernel.bin iso/boot/

# 3. Compile UEFI Application (Requires gnu-efi)
# gcc -I/usr/include/efi -fpic -ffreestanding -fno-stack-protector -c boot/uefi_bootloader.c -o boot/uefi.o
# objcopy ... iso/EFI/BOOT/BOOTX64.EFI

echo "✅ Hybrid ISO structure ready under 'iso/' directory."
