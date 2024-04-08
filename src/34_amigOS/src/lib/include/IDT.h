#include "libc/stdint.h"
#include "libc/stddef.h"
struct idt_entry_t {
  uint16_t base_low;
  uint16_t selector;
  uint16_t segment;
  uint8_t zero;
  uint8_t flags;
  uint16_t base_high;
} __attribute__((packed));

typedef struct {
	uint16_t	limit;
	uint32_t	base;
} __attribute__((packed)) idtr_t;

// Define the structure for interrupt handlers
struct int_handler {
    void (*handler)(void *);  // Function pointer for interrupt handler
    int num;
    void * data;
};

void init_idt();

// Load the GDT and IDT

void idt_load(idtr_t *idt_ptr);

// Define an interrupt handler
void interrupt_handler();

void register_int_handler(int num, void (*handler)(void *data), void *data);
void default_int_handler(void *data);
void int_handler(int num);
void init_idt();
void idt_load(idtr_t *idt_ptr);