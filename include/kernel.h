#ifndef KERNEL_H
#define KERNEL_H

#include <stdint.h>
#include <stddef.h>

// System Operating Modes
typedef enum {
    MODE_BALANCED,
    MODE_HIGH_PERFORMANCE,
    MODE_POWER_SAVER
} OperatingMode;

// Hardware Device Structure
typedef struct {
    char device_id[32];
    char bus_id[32];
    uint32_t capabilities;
    uint8_t is_mapped;
} HardwareDevice;

// Custom Arena Memory Allocator (Replaces Garbage Collector)
typedef struct {
    uint8_t *buffer;
    size_t capacity;
    size_t offset;
} MemoryArena;

// Function Declarations
void kernel_init(void);
void* arena_alloc(MemoryArena *arena, size_t size);
void hal_register_device(const char* bus, const char* dev_id);
void ai_engine_evaluate_system(void);

#endif // KERNEL_H
