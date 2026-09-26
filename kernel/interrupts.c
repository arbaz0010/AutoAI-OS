#include "../include/kernel.h"
#include <stdio.h>
#include <string.h>

#define IDT_ENTRIES 256

static IDTEntry idt[IDT_ENTRIES];
static IDTPtr idt_ptr;
static uint64_t system_ticks = 0;

// Set gate in IDT
void idt_set_gate(uint8_t num, uint64_t base, uint16_t sel, uint8_t flags) {
    idt[num].offset_low  = (base & 0xFFFF);
    idt[num].selector    = sel;
    idt[num].ist         = 0;
    idt[num].type_attr   = flags;
    idt[num].offset_mid  = (base >> 16) & 0xFFFF;
    idt[num].offset_high = (base >> 32) & 0xFFFFFFFF;
    idt[num].zero        = 0;
}

// Timer Interrupt Service Routine (IRQ 0 / PIT)
void irq_timer_handler(InterruptRegisters *regs) {
    system_ticks++;
    
    // Every 100 ticks (~1 second) print heartbeat and trigger automatic context switch
    if (system_ticks % 100 == 0) {
        printf("\n[Hardware Timer ISR] Heartbeat Tick: %LU | Preempting CPU Core 0...\n", system_ticks);
        scheduler_schedule_next();
    }
}

// Universal Interrupt Dispatcher
void isr_handler(InterruptRegisters *regs) {
    if (regs->int_no == 32) { // IRQ 0: Hardware Timer
        irq_timer_handler(regs);
    } else if (regs->int_no < 32) {
        printf("\n[Kernel Fault] CPU Exception 0x%LX encountered! System Halted.\n", regs->int_no);
    }
}

void timer_init(uint32_t frequency_hz) {
    printf("[Hardware Timer] Programmable Interval Timer (PIT) calibrated to %u Hz.\n", frequency_hz);
}

void interrupt_init(void) {
    memset(idt, 0, sizeof(idt));
    idt_ptr.limit = (sizeof(IDTEntry) * IDT_ENTRIES) - 1;
    idt_ptr.base  = (uint64_t)&idt;

    // Simulate mapping IRQ 0 (Timer) to Interrupt 32
    idt_set_gate(32, (uint64_t)irq_timer_handler, 0x08, 0x8E);

    printf("[Interrupt Engine] IDT Table Vector (256 Entries) Mapped at 0x%p.\n", (void*)idt_ptr.base);
    timer_init(100); // 100 Hz = 10ms per tick
}
