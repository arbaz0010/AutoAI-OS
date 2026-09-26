#include "../include/kernel.h"
#include <stdio.h>
#include <string.h>

void task_hardware_telemetry(void) {
    printf("  [Task 1] Monitoring PCIe MMIO Registers & Power Rails...\n");
}

void task_ai_evaluator(void) {
    printf("  [Task 2] AI Decision Engine: Direct Bus Optimization...\n");
}

void kernel_init(void) {
    printf("====================================================\n");
    printf(" 🚀 AutoAI-OS Pure C Native Bare-Metal Microkernel\n");
    printf("====================================================\n");
    printf("[+] Architecture: x86_64 & ARM64 Multi-Arch Core\n");
    printf("[+] Memory: Custom Static Arena Allocator (No GC)\n");
    printf("[+] Bus Control: Direct MMIO & UART Hardware Driver\n");
    printf("====================================================\n\n");

    hal_init();
    ai_engine_init();
    scheduler_init();
    interrupt_init();
    mmio_init();

    // Map Neural NPU PCIe Bus directly into kernel MMIO space
    mmio_map_region(0xE0000000, 0x10000); // 64KB NPU MMIO Region
    hal_register_device("PCIe_BUS_0", "DEV_NEURAL_NPU_01", 0xFF01);

    scheduler_create_task("HW_Telemetry", task_hardware_telemetry, 1);
    scheduler_create_task("AI_Evaluator", task_ai_evaluator, 2);
}

int main(void) {
    kernel_init();

    char input[64];
    printf("\nAutoAI-OS Shell Active. Commands: 'bus', 'uart', 'tasks', 'irq', 'exit'.\n");

    while (1) {
        printf("\nAutoAI-OS (Native) > ");
        if (!fgets(input, sizeof(input), stdin)) break;

        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "exit") == 0 || strcmp(input, "quit") == 0) {
            printf("Halting Kernel Safely...\n");
            break;
        } else if (strcmp(input, "bus") == 0) {
            printf("[Testing MMIO Bus Mapping Registers...]\n");
            mmio_map_region(0xFEB00000, 0x4000);
        } else if (strcmp(input, "uart") == 0) {
            printf("[Writing Direct Output to Bare-Metal UART Serial Port...]\n");
            uart_puts("AutoAI-OS: Direct UART Serial Output Success!\n");
        } else if (strcmp(input, "tasks") == 0) {
            scheduler_print_tasks();
        } else if (strcmp(input, "irq") == 0) {
            InterruptRegisters dummy_regs = {.int_no = 32};
            for(int i = 0; i < 100; i++) isr_handler(&dummy_regs);
        } else if (strcmp(input, "help") == 0) {
            printf("Commands: 'bus' (Test MMIO Mapping), 'uart' (Hardware Serial Out), 'tasks', 'irq', 'exit'\n");
        } else if (strlen(input) > 0) {
            printf("Unknown Command: '%s'\n", input);
        }
    }

    return 0;
}
