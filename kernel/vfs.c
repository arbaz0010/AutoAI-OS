#include "../include/kernel.h"
#include <stdio.h>
#include <string.h>

#define MAX_VFS_NODES 32

static VFSNode vfs_pool[MAX_VFS_NODES];
static size_t node_count = 0;
static VFSNode *root_node = NULL;

void vfs_init(void) {
    memset(vfs_pool, 0, sizeof(vfs_pool));
    node_count = 0;

    // Root directory Creation
    root_node = &vfs_pool[node_count++];
    strncpy(root_node->name, "/", 32);
    root_node->type = VFS_DIRECTORY;
    root_node->next = NULL;

    printf("[VFS Engine] In-Memory Root Virtual File System Mounted at '/' (RAM Arena).\n");

    // Default System Devices Mapping
    VFSNode *dev_uart = vfs_create_file("dev_uart", VFS_DEVICE);
    if (dev_uart) {
        vfs_write(dev_uart, "UART0: 115200 Baud Rate - Active", 32);
    }

    VFSNode *sys_info = vfs_create_file("sys_status", VFS_FILE);
    if (sys_info) {
        vfs_write(sys_info, "AutoAI-OS Microkernel Active (GC-Free 0ms)", 42);
    }
}

VFSNode* vfs_create_file(const char* name, VFSNodeType type) {
    if (node_count >= MAX_VFS_NODES) {
        printf("[VFS Error] Max file node limit reached!\n");
        return NULL;
    }

    VFSNode *node = &vfs_pool[node_count++];
    strncpy(node->name, name, 32);
    node->type = type;
    node->size = 0;
    node->parent = root_node;
    node->next = NULL;

    // Chain node to root directory list
    VFSNode *curr = root_node;
    while (curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = node;

    printf("[VFS] Created %s Node: '%s' in Memory Arena\n", 
           (type == VFS_DEVICE) ? "Device" : "File", name);

    return node;
}

int vfs_write(VFSNode* node, const void* data, size_t size) {
    if (!node || size > sizeof(node->buffer)) return -1;

    memcpy(node->buffer, data, size);
    node->size = size;
    return (int)size;
}

int vfs_read(VFSNode* node, void* buffer, size_t size) {
    if (!node) return -1;

    size_t read_bytes = (size < node->size) ? size : node->size;
    memcpy(buffer, node->buffer, read_bytes);
    return (int)read_bytes;
}

void vfs_list_dir(void) {
    printf("\n--- In-Memory VFS Directory Listing ('/') ---\n");
    VFSNode *curr = root_node->next;
    while (curr != NULL) {
        const char *type_str = (curr->type == VFS_DEVICE) ? "[DEV]" : "[FIL]";
        printf("%s %-20s | Size: %zu Bytes\n", type_str, curr->name, curr->size);
        curr = curr->next;
    }
    printf("---------------------------------------------\n");
}
