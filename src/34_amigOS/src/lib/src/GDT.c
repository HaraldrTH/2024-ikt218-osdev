#include "../include/GDT.h"

// Alt i denne filen er generert av ChatGPT
//Prompt: Extend your OS by implementing the Global Descriptor Table (GDT) mechanism. 
//You should at minimum implement the NULL, Data, and Text descriptor.
//How to do in c
// Define GDT descriptor structure
struct gdt_entry {
    int limit_low;     // The lower 16 bits of the limit
    int base_low;      // The lower 16 bits of the base
    int base_middle;    // The next 8 bits of the base
    int access;         // Access flags
    int granularity;
    int base_high;      // The last 8 bits of the base
} __attribute__((packed));

// Define GDT pointer structure
struct gdt_ptr {
    int limit;         // The upper 16 bits of all selector limits
    int base;          // The address of the first gdt_entry_t struct
} __attribute__((packed));

// Define GDT entries
struct gdt_entry gdt[3];

// Initialize GDT pointer
struct gdt_ptr gp;

// Function to set GDT entry
void gdt_set_gate(int num, int base, int limit, int access, int gran) {
    // Set base address
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;

    // Set limit
    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = (limit >> 16) & 0x0F;

    // Set granularity and access flags
    gdt[num].granularity |= (gran & 0xF0);
    gdt[num].access = access;
}

// Function to initialize GDT
void init_gdt() {
    // Set up GDT descriptors
    gp.limit = (sizeof(struct gdt_entry) * 3) - 1;
    gp.base = (int)&gdt;

    // NULL descriptor
    gdt_set_gate(0, 0, 0, 0, 0);

    // Code segment descriptor
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // 0x9A = code segment, read/write, accessed
                                                 // 0xCF = 4kb granularity, 32-bit, 4GB limit

    // Data segment descriptor
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // 0x92 = data segment, read/write, accessed
                                                 // 0xCF = 4kb granularity, 32-bit, 4GB limit

    // Load GDT
    gdt_flush((int)&gp);
}
