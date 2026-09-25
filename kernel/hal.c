#include "../include/kernel.h"
#include <stdio.h>
#include <string.h>

static HardwareDevice device_table[MAX_DEVICES];
static size_t device_count = 0;

void hal_init(void) {
    memset(device_table, 0, sizeof(device_table));
    device_count = 0;
    printf("[HAL C-Core] Zero-Driver Abstraction Engine Initialized.\n");
}

int hal_register_device(const char* bus_id, const char* dev_id, uint32_t caps) {
    if (device_count >= MAX_DEVICES) return -1;

    HardwareDevice *dev = &device_table[device_count++];
    strncpy(dev->bus_id, bus_id, 32);
    strncpy(dev->device_id, dev_id, 32);
    dev->capabilities = caps;
    dev->is_mapped = 1;

    printf("[HAL Direct Map] Mapped %s on %s (Caps: 0x%X)\n", dev_id, bus_id, caps);
    return 0;
}

void hal_print_matrix(void) {
    printf("\n--- Universal HAL Mapped Matrix ---\n");
    for (size_t i = 0; i < device_count; i++) {
        printf("[%zu] Bus: %-12s | Device: %-20s | Mapped: YES\n", 
               i+1, device_table[i].bus_id, device_table[i].device_id);
    }
    printf("-----------------------------------\n");
}
