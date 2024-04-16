#include "../include/MemoryManager.h"
#include "../include/stdlib.h"
#include <stdint.h>
#include <stddef.h>

// Define the NULL pointer, the memory stack size and the memory block size
#define NULL_POINTER ((void*)0)
#define MEMORY_STACK_SIZE 4*1024
#define MEMORY_BLOCK_SIZE sizeof(block_mem_t)

static uint8_t memory_stack_LL[MEMORY_STACK_SIZE];
static block_mem_t* memory_stack_start;

// Function to initialize the memory stack
void init_memory_stack(block_mem_t* end_addr){
    char* addr = (char*)end_addr;

    // Calculate the remainder of the division of the addres by the size of the memory block, in case of missallignment
    size_t remainder = (size_t)addr % sizeof(block_mem_t);

    // If the remainder is not zero, adjust the address to the next memory block
    if (remainder != 0){
        addr += sizeof(block_mem_t) - remainder;
    }

    memory_stack_start = (block_mem_t*)addr;
    memory_stack_start->size = MEMORY_STACK_SIZE - MEMORY_BLOCK_SIZE;
    memory_stack_start->next = NULL_POINTER;
    memory_stack_start->prev = NULL_POINTER;
}

void *find_best_mem_block(block_mem_t *dynamic_mem, size_t size){
    // Initialize the result pointer with NULL and an invalid block size
    block_mem_t *best_block = (block_mem_t *) NULL_POINTER;
    uint_t best_block_size = MEMORY_STACK_SIZE + 1;

    // Start looking for the best (smallest unused) block at the beginning of the memory stack
    block_mem_t *current_block = dynamic_mem;
    while (current_block){
        // Check if block can be used and is smaller than the current best block
        if ((!current_block->used) &&
            (current_block->size >= (size + MEMORY_BLOCK_SIZE)) &&
            (current_block->size <= best_block_size)){
                // Update the best block pointer and size
                best_block = current_block;
                best_block_size = current_block->size;
        }
        // Move to the next block
        current_block = current_block->next;
    }
    return best_block;
}

void malloc(uint32_t size){
    block_mem_t *best_block = (block_mem_t*)find_best_mem_block(memory_stack_start, size);

    // Check if "find_best_mem_block" actually found a block
    if (best_block != NULL_POINTER){
        // Subtract newly allocated memory (including size of the block) from the selected block
        best_block->size -= (size + MEMORY_BLOCK_SIZE);
        // Create a new mem block after the selected one, splitting the memory up in two
        block_mem_t *mem_block_allocate = (block_mem_t*)(((uint8_t*)best_block) + MEMORY_BLOCK_SIZE + best_block->size);
        mem_block_allocate->size = size;
        mem_block_allocate->used = true;
        mem_block_allocate->next = best_block->next;
        mem_block_allocate->prev = best_block;

        // Reconnect the doubly linked list
        if (best_block->next != NULL_POINTER){
            best_block->next->prev = mem_block_allocate;
        }
        best_block->next = mem_block_allocate;

        // Return pointer to newly allocated memory
        return (void*)((uint8_t*) mem_block_allocate + MEMORY_BLOCK_SIZE);
    }
    // Return NULL if no memory block was found
    return NULL_POINTER;
}

void *merge_with_next_block(block_mem_t *current_mem_block){
    block_mem_t *next_mem_block = current_mem_block->next;
    // Check if the next block is unused
    if (next_mem_block != NULL_POINTER && !next_mem_block->used){
        // add the size of the next block to the current one
        current_mem_block->size += current_mem_block->next->size;
        current_mem_block->size += MEMORY_BLOCK_SIZE;

        // Remove the next block from the linked list
        current_mem_block->next = current_mem_block->next->next;
        if (current_mem_block->next != NULL_POINTER){
            current_mem_block->next->prev = current_mem_block;
        }
    }
    return current_mem_block;
}

void *merge_with_previous_block(block_mem_t *current_mem_block){
    block_mem_t *prev_mem_block = current_mem_block->prev;
    // Check if the previous block is unused
    if (prev_mem_block != NULL_POINTER && !prev_mem_block->used){
        // add the size of the previous block to the current one
        prev_mem_block->size += current_mem_block->size;
        prev_mem_block->size += MEMORY_BLOCK_SIZE;

        // Remove the current block from the linked list
        prev_mem_block->next = current_mem_block->next;
        if (current_mem_block->next != NULL_POINTER){
            current_mem_block->next->prev = prev_mem_block;
        }
    }
}

void free(uint32_t* ptr){
    if (ptr == NULL_POINTER){
        return;
    }
    // Get block_mem associated with pointer
    block_mem_t *current_mem_block = (block_mem_t*)((uint8_t*)ptr - MEMORY_BLOCK_SIZE);

    // If no such mem_block exists, return
    if (current_mem_block == NULL_POINTER){
        // Maybe print error message
        return;
    }

    // Mark the block as unused
    current_mem_block->used = false;

    // Merge with unused blocks
    current_mem_block = merge_with_next_block(current_mem_block);
    merge_with_previous_block(current_mem_block);
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
