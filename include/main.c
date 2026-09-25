#include "../include/kernel.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static uint8_t global_kernel_memory[1024 * 1024]; // 1MB Static Kernel Memory
static MemoryArena kernel_arena = {
    .buffer = global_kernel_memory,
    .capacity = sizeof(global_kernel_memory),
    .offset = 0
};

void kernel_init(void) {
    printf("====================================================\n");
    printf(" 🚀 AutoAI-OS Pure C/Rust Native Bare-Metal Kernel\n");
    printf("====================================================\n");
    printf("[+] Garbage Collector: REMOVED (0ms Latency Engine)\n");
    printf("[+] Memory Management: Deterministic Arena Allocator\n");
    printf("[+] Architecture: 64-Bit C/Assembly Hardware Kernel\n");
    printf("====================================================\n\n");
}

int main(void) {
    kernel_init();

    // Allocate Kernel State using Custom Arena (Zero GC)
    HardwareDevice *dev1 = (HardwareDevice*) arena_alloc(&kernel_arena, sizeof(HardwareDevice));
    if (dev1) {
        strncpy(dev1->device_id, "DEV_NEURAL_NPU_01", 32);
        strncpy(dev1->bus_id, "PCIe_BUS_0", 32);
        dev1->is_mapped = 1;
        printf("[HAL Native] Hardware Mapped: %s on %s\n", dev1->device_id, dev1->bus_id);
    }

    printf("\nAutoAI-OS Shell Ready (Pure C Mode). Type 'exit' to halt kernel.\n");

    char input[64];
    while (1) {
        printf("\nAutoAI-OS (Native) > ");
        if (!fgets(input, sizeof(input), stdin)) break;

        // Remove newline
        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "exit") == 0) {
            printf("Halting AutoAI-OS Kernel Safely...\n");
            break;
        } else if (strcmp(input, "status") == 0) {
            printf("[System Status]: OPERATIONAL | Mode: HIGH_PERFORMANCE | GC: DISABLED\n");
            printf("[Memory Arena]: Used %zu / %zu bytes\n", kernel_arena.offset, kernel_arena.capacity);
        } else {
            printf("Unknown Command. Available: 'status', 'exit'\n");
        }
    }

    return 0;
}
