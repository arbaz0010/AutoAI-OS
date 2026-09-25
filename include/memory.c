#include "../include/kernel.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Allocate raw buffer from custom static arena memory block
void* arena_alloc(MemoryArena *arena, size_t size) {
    // Align to 8 bytes boundary
    size_t aligned_size = (size + 7) & ~7;

    if (arena->offset + aligned_size > arena->capacity) {
        printf("[Kernel Panic] Native Memory Arena Out of Memory!\n");
        return NULL;
    }

    void *ptr = &arena->buffer[arena->offset];
    arena->offset += aligned_size;
    memset(ptr, 0, aligned_size);
    
    printf("[Native Memory] Allocated %zu bytes at offset 0x%ZX (No GC Overhead)\n", aligned_size, arena->offset);
    return ptr;
}
