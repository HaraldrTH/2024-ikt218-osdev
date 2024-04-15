#pragma once
#include "registers.h"
#include "libc/stdint.h"

#ifndef IRQ_H
#define IRQ_H

#define IRQ0 32
#define IRQ1 33
#define IRQ2 34
#define IRQ3 35
#define IRQ4 36
#define IRQ5 37
#define IRQ6 38
#define IRQ7 39
#define IRQ8 40
#define IRQ9 41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44
#define IRQ13 45
#define IRQ14 46
#define IRQ15 47
#define IRQ_COUNT 16


typedef void (*isr_t)(registers_t);

// Initialize IRQ handlers
void init_irq();

// Register an IRQ handler

void register_interrupt_handler(uint8_t n, isr_t handler);

// The main IRQ handler
void irq_handler(registers_t regs);


#endif