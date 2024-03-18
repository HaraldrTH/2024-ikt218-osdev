#include "../../../include/libc/stdint.h"

// Define number of descriptors
#define GDT_ENTRIES 5

// Define GDT descriptor structure
struct gdt_entry {
    uint16_t limit_low;     // The lower 16 bits of the limit
    uint16_t base_low;      // The lower 16 bits of the base
    uint8_t base_middle;    // The next 8 bits of the base
    uint8_t access;         // Access flags
    uint8_t granularity;    
    uint8_t base_high;      // The last 8 bits of the base
} __attribute__((packed));

// Define GDT pointer structure
struct gdt_ptr {
    uint16_t limit;         // The upper 16 bits of all selector limits
    uint32_t base;          // The address of the first gdt_entry_t struct
} __attribute__((packed));

// Define GDT entries
struct gdt_entry gdt[GDT_ENTRIES];

// Initialize GDT pointer
struct gdt_ptr gp;

// Initializes all GDT Descriptors
void init_gdt() {
    // Set up GDT descriptors
    gp.limit = (sizeof(struct gdt_entry) * GDT_ENTRIES) - 1;
    gp.base = (uint32_t) &gdt;

    gdt_set_gate(0, 0, 0, 0, 0);    // NULL descriptor
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);    // Code segment descriptor
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);    // Data segment descriptor
    gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);    // User Mode code segment descriptor
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);    // User mode data segment descriptor

    // Load GDT
    gdt_load(&gp);
    // Flush GDT pointer
    gdt_flush((uint32_t)&gp);
}

// Function to load the GDT into the processor
void gdt_load(struct gdt_ptr *gdt_ptr){
    asm volatile("lgdt %0" : : "m" (*gdt_ptr));
}

// Function to set a GDT entry with appropriate values
void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran){
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;

    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = (limit >> 16) & 0x0F;

    gdt[num].granularity |= (gran & 0xF0);
    gdt[num].access = access;
}
