#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    uint64_t memory_address;
    size_t size;
    int is_allocated;
} NativeMemoryBlock;

// Direct Native Fast Memory Allocation
NativeMemoryBlock* c_allocate_fast_buffer(size_t size) {
    NativeMemoryBlock *block = (NativeMemoryBlock*) malloc(sizeof(NativeMemoryBlock));
    if (!block) return NULL;

    void *raw_ptr = malloc(size);
    if (!raw_ptr) {
        free(block);
        return NULL;
    }

    memset(raw_ptr, 0, size);
    block->memory_address = (uint64_t) raw_ptr;
    block->size = size;
    block->is_allocated = 1;

    return block;
}

// C-Speed Direct Bus Data Transfer Bypass
int c_direct_bus_write(uint64_t address, const char* data, size_t length) {
    if (address == 0 || data == NULL) return -1;

    void *ptr = (void*) address;
    memcpy(ptr, data, length);
    return 0; // Success
}

// Free Allocated Buffer
void c_free_fast_buffer(NativeMemoryBlock *block) {
    if (block) {
        if (block->memory_address != 0) {
            free((void*) block->memory_address);
        }
        free(block);
    }
}
