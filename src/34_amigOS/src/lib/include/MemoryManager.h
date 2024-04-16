
typedef struct block{
    uint32_t size;
    bool used;
    struct block* next;
    struct block* prev;
} block_mem_t;


void init_kernel_memory(uint32_t* end);
void init_paging();
void print_memory_layout();
void malloc(uint32_t size);
void free(uint32_t* ptr);