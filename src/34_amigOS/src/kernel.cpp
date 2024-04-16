#include "lib/include/stdlib.h"
#include "lib/include/memory.h"
#include "../include/libc/stdint.h"

/*
// Existing global operator new overloads
void* operator new(size_t size) {
    return malloc(size);
}

void* operator new[](size_t size) {
    return malloc(size);
}

// Existing global operator delete overloads
void operator delete(void* ptr) noexcept {
    free(ptr);
}

void operator delete[](void* ptr) noexcept {
    free(ptr);
}

// Add sized-deallocation functions
void operator delete(void* ptr, size_t size) noexcept {
    (void)size; // Size parameter is unused, added to match required signature
    free(ptr);
}

void operator delete[](void* ptr, size_t size) noexcept {
    (void)size; // Size parameter is unused, added to match required signature
    free(ptr);
}
*/
extern "C" int kernel_main(void);
int kernel_main(){
    // Allocate some memory using the kernel memory manager
	// THIS IS PART OF THE ASSIGNMENT

    // void* some_memory = malloc(...); 
    // void* memory2 = malloc(...); 
    // void* memory3 = malloc(...);
    // char* memory4 = new char[...]();
	// More code....
    return 0;
}