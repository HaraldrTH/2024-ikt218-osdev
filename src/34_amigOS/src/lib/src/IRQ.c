#include "../include/IRQ.h"
#include "libc/stddef.h"
#include "../include/ports.h"
#include "../include/stdlib.h"

// Array to store IRQ handlers
//void (*irq_handlers[IRQ_COUNT])(void);
isr_t interrupt_handlers[256];

void init_irq() {
  for (int i = 0; i < IRQ_COUNT; i++) {
    interrupt_handlers[i] = NULL;
  }
}
void register_interrupt_handler(uint8_t n, isr_t handler)
{
  interrupt_handlers[n] = handler;
}

// The main IRQ handler
void irq_handler(registers_t regs)
{
   // Send an EOI (end of interrupt) signal to the PICs.
   // If this interrupt involved the slave.
   if (regs.int_no >= 40)
   {
       // Send reset signal to slave.
       outb(0xA0, 0x20);
   }
   // Send reset signal to master. (As well as slave, if necessary).
   outb(0x20, 0x20);

   if (interrupt_handlers[regs.int_no] != 0)
   {
       isr_t handler = interrupt_handlers[regs.int_no];
       handler(regs);
   }
   else{
    char* str = '\0';
    int_to_string(regs.int_no, str);
    printf("interrupt recieved: ");
    printf(str);
    putchar('\n');
   }
}