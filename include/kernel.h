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

// Task States
typedef enum {
    TASK_READY,
    TASK_RUNNING,
    TASK_BLOCKED,
    TASK_TERMINATED
} TaskState;

// Task Control Block (TCB)
typedef struct TaskControlBlock {
    uint32_t task_id;
    char name[32];
    TaskState state;
    uint32_t priority;
    void (*task_func)(void);    // Function Pointer to Task Logic
    uint8_t *stack_ptr;         // Dedicated Stack for this task
    struct TaskControlBlock *next;
} TaskControlBlock;

// Scheduler Prototypes
void scheduler_init(void);
int scheduler_create_task(const char* name, void (*func)(void), uint32_t priority);
void scheduler_schedule_next(void);
void scheduler_print_tasks(void);

#endif // KERNEL_H
