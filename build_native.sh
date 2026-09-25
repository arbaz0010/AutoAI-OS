#!/bin/bash
echo "🧹 Removing Python artifacts and legacy dependencies..."
rm -rf src/*.py

echo "🔨 Compiling Pure C Native AutoAI-OS Kernel..."
gcc -O3 -Wall -Iinclude kernel/main.c kernel/memory.c -o autoai_kernel_native

if [ $? -eq 0 ]; then
    echo "✅ Kernel Compiled Successfully: 'autoai_kernel_native'"
    echo "🚀 Run with: ./autoai_kernel_native"
else
    echo "❌ Compilation Failed!"
fi
