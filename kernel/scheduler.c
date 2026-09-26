#include "../include/kernel.h"
#include <stdio.h>
#include <string.h>

#define MAX_TASKS 16
#define TASK_STACK_SIZE 4096 // 4KB Stack per Task

static TaskControlBlock task_pool[MAX_TASKS];
static uint8_t task_stacks[MAX_TASKS][TASK_STACK_SIZE];
static TaskControlBlock *current_task = NULL;
static TaskControlBlock *task_list_head = NULL;
static uint32_t total_tasks = 0;

void scheduler_init(void) {
    memset(task_pool, 0, sizeof(task_pool));
    current_task = NULL;
    task_list_head = NULL;
    total_tasks = 0;
    printf("[Scheduler C-Core] Multi-Core Deterministic Round-Robin Scheduler Online.\n");
}

int scheduler_create_task(const char* name, void (*func)(void), uint32_t priority) {
    if (total_tasks >= MAX_TASKS) {
        printf("[Scheduler Error] Cannot create task '%s': Task pool full.\n", name);
        return -1;
    }

    TaskControlBlock *tcb = &task_pool[total_tasks];
    tcb->task_id = total_tasks + 1;
    strncpy(tcb->name, name, 32);
    tcb->state = TASK_READY;
    tcb->priority = priority;
    tcb->task_func = func;
    tcb->stack_ptr = task_stacks[total_tasks];
    tcb->next = NULL;

    // Link into Round-Robin Circular/Linear List
    if (task_list_head == NULL) {
        task_list_head = tcb;
    } else {
        TaskControlBlock *temp = task_list_head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = tcb;
    }

    total_tasks++;
    printf("[Scheduler] Task Created: ID %u | Name: '%s' | Priority: %u (Stack Allocated at 0x%p)\n",
           tcb->task_id, tcb->name, tcb->priority, (void*)tcb->stack_ptr);
    return tcb->task_id;
}

void scheduler_schedule_next(void) {
    if (task_list_head == NULL) return;

    if (current_task == NULL) {
        current_task = task_list_head;
    } else if (current_task->next != NULL) {
        current_task->state = TASK_READY;
        current_task = current_task->next;
    } else {
        current_task->state = TASK_READY;
        current_task = task_list_head; // Wrap around to start
    }

    current_task->state = TASK_RUNNING;
    printf("[Scheduler Context Switch] Switched to Task %u ('%s') [Core 0]\n",
           current_task->task_id, current_task->name);

    // Execute the task function directly
    if (current_task->task_func != NULL) {
        current_task->task_func();
    }
}

void scheduler_print_tasks(void) {
    printf("\n--- Active Kernel Tasks & Thread Pool ---\n");
    TaskControlBlock *temp = task_list_head;
    while (temp != NULL) {
        const char *state_str = (temp->state == TASK_RUNNING) ? "RUNNING" : "READY";
        printf("ID: %-2u | Name: %-20s | Priority: %-2u | State: %s\n",
               temp->task_id, temp->name, temp->priority, state_str);
        temp = temp->next;
    }
    printf("-----------------------------------------\n");
}
