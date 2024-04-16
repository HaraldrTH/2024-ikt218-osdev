
typedef struct block{
    size_t size;
    struct block* next;
    struct block* prev;
} block_mem;


void init_kernel_memory(uint32_t* end);
void init_paging();
void print_memory_layout();