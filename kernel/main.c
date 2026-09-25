#include "../include/kernel.h"
#include <stdio.h>
#include <string.h>

void kernel_init(void) {
    printf("====================================================\n");
    printf(" 🚀 AutoAI-OS Pure C Native Bare-Metal Microkernel\n");
    printf("====================================================\n");
    printf("[+] Garbage Collector: REMOVED (Zero-Latency Engine)\n");
    printf("[+] Memory Allocation: Custom Arena Allocator\n");
    printf("[+] Architecture: 64-Bit Pure C Native Stack\n");
    printf("====================================================\n\n");

    hal_init();
    ai_engine_init();

    // Auto-map primary neural NPU and PCIe bus
    hal_register_device("PCIe_BUS_0", "DEV_NEURAL_NPU_01", 0xFF01);
    hal_register_device("Virtual_BUS_1", "DEV_CPU_CORE_0", 0x000F);

    ai_engine_evaluate();
}

int main(void) {
    kernel_init();

    char input[64];
    printf("\nAutoAI-OS Shell Active (Pure C Engine). Type 'help' or 'exit'.\n");

    while (1) {
        printf("\nAutoAI-OS (Native) > ");
        if (!fgets(input, sizeof(input), stdin)) break;

        input[strcspn(input, "\n")] = 0; // Strip newline

        if (strcmp(input, "exit") == 0 || strcmp(input, "quit") == 0) {
            printf("Halting AutoAI-OS Pure C Kernel Safely...\n");
            break;
        } else if (strcmp(input, "hal") == 0) {
            hal_print_matrix();
        } else if (strcmp(input, "status") == 0) {
            printf("[System Status]: OPERATIONAL | Mode: HIGH_PERFORMANCE | GC: NONE\n");
        } else if (strcmp(input, "help") == 0) {
            printf("Available Commands: 'hal', 'status', 'exit'\n");
        } else if (strlen(input) > 0) {
            printf("Unknown Command: '%s'. Type 'help' for options.\n", input);
        }
    }

    return 0;
}
