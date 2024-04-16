#include "../include/MemoryManager.h"
#include "../include/stdlib.h"
#include <stdint.h>
#include <stddef.h>

#define NULL_POINTER ((void*)0)
#define MEMORY_STACK_SIZE 4*1024
#define MEMORY_BLOCK_SIZE sizeof(block_mem_t)

static uint8_t memory_stack_LL[MEMORY_STACK_SIZE];
static block_mem_t* memory_stack_start;

// Function to initialize the memory stack
void init_memory_stack() {
    memory_stack_start = (block_mem_t*)memory_stack_LL;
    memory_stack_start->size = MEMORY_STACK_SIZE - MEMORY_BLOCK_SIZE;
    memory_stack_start->next = NULL_POINTER;
    memory_stack_start->prev = NULL_POINTER;
}

void malloc(uint32_t size){
    continue;
}


void free(uint32_t* ptr){
    continue;
}


void init_kernel_memory(uint32_t* end){
    continue;
}

void init_paging(){
    continue;
}

void print_memory_layout(){
    continue;
}
