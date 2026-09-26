#!/bin/bash
echo "🔨 Compiling Pure C AutoAI-OS Kernel with Task Scheduler..."
gcc -O3 -Wall -Iinclude \
    kernel/main.c \
    kernel/hal.c \
    kernel/memory.c \
    kernel/ai_engine.c \
    kernel/scheduler.c \
    -o autoai_kernel_native

if [ $? -eq 0 ]; then
    echo "✅ Native Kernel Compiled Successfully: './autoai_kernel_native'"
    echo "🚀 Run with: ./autoai_kernel_native"
else
    echo "❌ Compilation Failed!"
fi
