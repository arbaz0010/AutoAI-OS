#include "../include/kernel.h"
#include <stdio.h>
#include <string.h>

#define MAX_MMIO_MAPPINGS 16
static MMIOMapping mmio_table[MAX_MMIO_MAPPINGS];
static size_t mmio_count = 0;

// Low-Level MMIO Memory Register Operations
uint8_t mmio_read8(uint64_t addr) {
    return *(volatile uint8_t*)addr;
}

void mmio_write8(uint64_t addr, uint8_t val) {
    *(volatile uint8_t*)addr = val;
}

// Map physical bus addresses into direct kernel space
void* mmio_map_region(uint64_t phys_addr, size_t size) {
    if (mmio_count >= MAX_MMIO_MAPPINGS) {
        printf("[MMIO Panic] Direct Bus Mapping Limit Reached!\n");
        return NULL;
    }

    MMIOMapping *map = &mmio_table[mmio_count++];
    map->physical_address = phys_addr;
    map->virtual_address = phys_addr; // Direct Identity Mapping for Microkernel
    map->size = size;
    map->is_io_mapped = 1;

    printf("[Bus Router] Identity Mapped Physical Bus MMIO 0x%016LX (%zu Bytes)\n", phys_addr, size);
    return (void*)map->virtual_address;
}

// Initialize Serial Hardware UART (Universal Asynchronous Receiver-Transmitter)
void uart_init(void) {
    // Map UART Registers for ARM64 & x86_64 Identity Space
    mmio_map_region(ARM_UART_BASE, 0x1000);
    printf("[UART Bus] Bare-Metal Serial Port Driver (COM1 / PL011) Online.\n");
}

void uart_putc(char c) {
    // Direct MMIO write to UART Data Register
    volatile uint32_t *uart_dr = (volatile uint32_t*)ARM_UART_BASE;
    *uart_dr = (uint32_t)c;
}

void uart_puts(const char* str) {
    while (*str) {
        uart_putc(*str++);
    }
}

void mmio_init(void) {
    memset(mmio_table, 0, sizeof(mmio_table));
    mmio_count = 0;
    printf("[MMIO C-Core] Direct Bus Router & Page-Table Mapper Initialized.\n");
    uart_init();
}
