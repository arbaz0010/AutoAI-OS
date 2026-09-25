#include "../include/kernel.h"
#include <stdio.h>
#include <string.h>

static uint8_t global_arena_buffer[MEMORY_ARENA_SIZE];
static MemoryArena kernel_arena = {
    .buffer = global_arena_buffer,
    .capacity = MEMORY_ARENA_SIZE,
    .offset = 0
};

void* arena_alloc(MemoryArena *arena, size_t size) {
    if (!arena) arena = &kernel_arena;

    // 8-byte Alignment
    size_t aligned_size = (size + 7) & ~7;

    if (arena->offset + aligned_size > arena->capacity) {
        printf("[Kernel Panic] Native Memory Arena Exhausted!\n");
        return NULL;
    }

    void *ptr = &arena->buffer[arena->offset];
    arena->offset += aligned_size;
    memset(ptr, 0, aligned_size);

    return ptr;
}
