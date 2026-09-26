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

// IDT Entry Structure (x86_64)
typedef struct {
    uint16_t offset_low;    // Offset bits 0..15
    uint16_t selector;      // Code segment selector
    uint8_t  ist;           // Interrupt Stack Table offset
    uint8_t  type_attr;     // Type and attributes
    uint16_t offset_mid;    // Offset bits 16..31
    uint32_t offset_high;   // Offset bits 32..63
    uint32_t zero;          // Reserved
} __attribute__((packed)) IDTEntry;

typedef struct {
    uint16_t limit;
    uint64_t base;
} __attribute__((packed)) IDTPtr;

// Registers state saved during Interrupt
typedef struct {
    uint64_t r15, r14, r13, r12, r11, r10, r9, r8;
    uint64_t rbp, rdi, rsi, rdx, rcx, rbx, rax;
    uint64_t int_no, err_code;
    uint64_t rip, cs, rflags, rsp, ss;
} InterruptRegisters;

// Prototypes
void interrupt_init(void);
void timer_init(uint32_t frequency_hz);
void isr_handler(InterruptRegisters *regs);
void irq_timer_handler(InterruptRegisters *regs);

// Hardware Register Mapping Addresses
#define COM1_PORT 0x3F8            // x86_64 Serial Port COM1 Base
#define ARM_UART_BASE 0x09000000   // ARM64 PL011 UART MMIO Base Address

// Bus Mapping Structure
typedef struct {
    uint64_t physical_address;
    uint64_t virtual_address;
    size_t size;
    uint8_t is_io_mapped;
} MMIOMapping;

// Bus & Driver Prototypes
void mmio_init(void);
void* mmio_map_region(uint64_t phys_addr, size_t size);
void uart_init(void);
void uart_putc(char c);
void uart_puts(const char* str);
uint8_t mmio_read8(uint64_t addr);
void mmio_write8(uint64_t addr, uint8_t val);

#endif // KERNEL_H
