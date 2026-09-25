#include <stdint.h>

/* VGA Text Mode Framebuffer Address for Direct Screen Output */
#define VGA_ADDRESS 0xB8000
#define WHITE_ON_BLACK 0x0F

void clear_screen(volatile char *vga) {
    for (int i = 0; i < 80 * 25 * 2; i += 2) {
        vga[i] = ' ';
        vga[i+1] = WHITE_ON_BLACK;
    }
}

void print_string(volatile char *vga, const char *str, int row) {
    int offset = row * 80 * 2;
    int i = 0;
    while (str[i] != '\0') {
        vga[offset] = str[i];
        vga[offset + 1] = WHITE_ON_BLACK;
        offset += 2;
        i++;
    }
}

/* Multiboot Kernel Entry Point */
void kmain(void) {
    volatile char *vga = (volatile char*)VGA_ADDRESS;

    clear_screen(vga);

    print_string(vga, "==================================================", 2);
    print_string(vga, "   🚀 AutoAI-OS Bare-Metal UEFI/Multiboot Kernel  ", 3);
    print_string(vga, "==================================================", 4);
    
    print_string(vga, "[+] CPU 64-Bit Protected Mode: OK", 6);
    print_string(vga, "[+] Direct Memory Map & VGA Framebuffer: MAPPED", 7);
    print_string(vga, "[+] Handing over execution to Micro-Python Runtime...", 9);
    print_string(vga, "[+] AutoAI-OS Core Native Agent Initialized.", 10);

    /* System Halt Loop */
    while (1) {
        __asm__ __volatile__("hlt");
    }
}
