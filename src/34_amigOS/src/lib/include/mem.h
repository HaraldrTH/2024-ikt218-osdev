#pragma once
#include "libc/stdint.h"
#include "libc/stddef.h"
void custom_memset(void* location, int val, int len);
void memory_init();
void* custom_malloc(size_t size);
void custom_free(void* ptr);