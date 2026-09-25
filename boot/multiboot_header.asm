section .multiboot
align 4
    dd 0x1BADB002              ; Magic number for Multiboot
    dd 0x00                    ; Flags
    dd - (0x1BADB002 + 0x00)   ; Checksum

section .text
global _start
extern kmain

_start:
    cli                        ; Disable interrupts
    call kmain                 ; Call C entry function
    hlt                        ; Halt CPU if kmain returns
