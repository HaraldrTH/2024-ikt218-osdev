#include "../include/IRQ.h"
#include "libc/stddef.h"
#include "../include/ports.h"


void init_irq() {
  for (int i = 0; i < IRQ_COUNT; i++) {
    irq_handlers[i] = NULL;
  }
}
void register_irq_handler(int irq, void (*handler)(void)) {
  irq_handlers[irq] = handler;
}

// The main IRQ handler
void irq_handler(int irq) {
  // Check if a handler is registered for this IRQ
  if (irq_handlers[irq] != NULL) {
    irq_handlers[irq]();
  }

  // Send an EOI (End of Interrupt) signal to the PIC (Programmable Interrupt Controller)
  if (irq >= 8) {
    // Send EOI to the slave PIC
    outb(0xA0, 0x20);
  }
  // Send EOI to the master PIC
  outb(0x20, 0x20);
}