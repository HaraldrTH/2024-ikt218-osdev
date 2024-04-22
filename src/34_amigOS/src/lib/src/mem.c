#include "../include/mem.h"

void custom_memset(void* location, int val, int len)
{
   while(len > 0){
      location = val;
      len--;
      location++;
   }
}


// Define a memory pool size
#define POOL_SIZE 1024

// Structure for a memory block header
typedef struct BlockHeader {
    size_t size;          // Size of the block
    struct BlockHeader* next; // Next block in the list
    int is_free;          // Flag indicating if the block is free
} BlockHeader;

// Memory pool
static uint8_t memory_pool[POOL_SIZE]; // Memory pool
static BlockHeader* free_list = NULL;  // List of free blocks

// Initialize the memory pool and free list
void memory_init() {
    // Initialize the first free block in the memory pool
    free_list = (BlockHeader*)memory_pool;
    free_list->size = POOL_SIZE - sizeof(BlockHeader); // Size available after header
    free_list->next = NULL; // No other free blocks yet
    free_list->is_free = 1; // Mark the block as free
}

// Custom malloc implementation
void* custom_malloc(size_t size) {
    BlockHeader* current = free_list; // Start at the first free block
    BlockHeader* previous = NULL;

    // Traverse the free list to find a suitable block
    while (current) {
        if (current->is_free && current->size >= size) {
            // Split the block if it's large enough
            if (current->size > size + sizeof(BlockHeader)) {
                BlockHeader* new_block = (BlockHeader*)((uint8_t*)current + sizeof(BlockHeader) + size);
                new_block->size = current->size - size - sizeof(BlockHeader);
                new_block->is_free = 1;
                new_block->next = current->next;

                current->size = size; // Set the new block's size
                current->next = new_block; // Link to the new block
            }
            current->is_free = 0; // Mark the block as used
            return (void*)((uint8_t*)current + sizeof(BlockHeader)); // Return the usable memory
        }
        previous = current; // Move to the next block
        current = current->next; // Traverse
    }

    return NULL; // No suitable block found
}

// Custom free implementation
void custom_free(void* ptr) {
    if (ptr == NULL) {
        return; // Nothing to free
    }

    BlockHeader* header = (BlockHeader*)((uint8_t*)ptr - sizeof(BlockHeader)); // Get the block header
    header->is_free = 1; // Mark the block as free

    // Attempt to coalesce adjacent free blocks
    BlockHeader* current = free_list; // Start at the free list
    while (current && current->next) {
        if (current->is_free && current->next->is_free) {
            // Merge adjacent free blocks
            current->size += sizeof(BlockHeader) + current->next->size;
            current->next = current->next->next; // Update the link
        }
        current = current->next; // Move to the next block
    }
}