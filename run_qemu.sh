#!/bin/bash

echo "===================================================="
echo " 🚀 AutoAI-OS Bare-Metal QEMU Emulation Runner"
echo "===================================================="
echo "1) Run x86_64 Native Kernel in QEMU"
echo "2) Run ARM64 (AArch64) Native Kernel in QEMU"
echo "3) Exit"
echo "----------------------------------------------------"
read -p "Select Architecture to Emulate [1-3]: " choice

case $choice in
    1)
        echo "🔥 Building & Launching x86_64 Kernel on QEMU System..."
        ./build_native.sh
        if [ $? -eq 0 ]; then
            qemu-system-x86_64 -m 512M -nographic -kernel autoai_kernel_native
        fi
        ;;
    2)
        echo "🔥 Building & Launching ARM64 Kernel on QEMU Virt Board..."
        ./build_arm64.sh
        if [ $? -eq 0 ]; then
            qemu-system-aarch64 -M virt -cpu cortex-a57 -m 512M -nographic -kernel autoai_kernel_arm64.elf
        fi
        ;;
    3)
        echo "Exiting QEMU Runner."
        exit 0
        ;;
    *)
        echo "Invalid choice!"
        ;;
esac
