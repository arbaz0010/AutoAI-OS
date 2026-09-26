/* AutoAI-OS ARM64 Bare-Metal Startup Code */
.section ".text.boot"
.global _start

_start:
    /* Read CPU core ID (MPIDR_EL1) */
    mrs     x0, mpidr_el1
    and     x0, x0, #0xFF
    cbz     x0, master_core        /* Only primary core (Core 0) boots */

halt_loop:
    wfe                            /* Put secondary cores to sleep */
    b       halt_loop

master_core:
    /* Set stack pointer below kernel image */
    ldr     x0, =_start
    mov     sp, x0

    /* Clear BSS section */
    ldr     x0, =__bss_start
    ldr     x1, =__bss_end
    sub     x1, x1, x0
    cbz     x1, run_c_kernel

clear_bss:
    str     xzr, [x0], #8
    subs    x1, x1, #8
    b.gt    clear_bss

run_c_kernel:
    /* Jump into C Kernel main() entry point */
    bl      main

    /* Hang CPU if main() exits */
    b       halt_loop
