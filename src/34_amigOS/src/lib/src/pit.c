#include "../include/pit.h"
#include "../include/libc/stdint.h"
#include "../include/stdlib.h"
#include "../include/IRQ.h"
#include "../include/ports.h"

uint32_t tick = 0;

static void timer_callback(){
    tick++;
    if (tick % 1000 == 0){
        printf("Tick: %d\n", tick);
    }
};

void init_pit(){
    // Register our timer callback
    register_interrupt_handler(32, &timer_callback);

    uint32_t divisor = DIVIDER;

    // Send the command byte, set the PIT to repeating mode
    outb(0x43,0x36);

    // Divisor has to be sent byte-wise, so split here into upper/lower bytes.
    uint8_t l = (uint8_t)(divisor & 0xFF);
    uint8_t h = (uint8_t)((divisor>>8) & 0xFF);

    outb(0x40, l);
    outb(0x40, h);
};

uint32_t get_current_tick(){
    return tick;
};

void sleep_interrupt(uint32_t milliseconds){
    uint32_t start_tick = get_current_tick();
	uint32_t ticks_to_wait = milliseconds * TICKS_PER_MS;
	int elapsed_ticks = 0;
while((int)elapsed_ticks < (int)ticks_to_wait){
    while (get_current_tick() == start_tick + elapsed_ticks){
            continue; // Do nothing
        }
		elapsed_ticks++;
    }
};

void sleep_busy(uint32_t milliseconds){
    uint32_t current_tick = get_current_tick();
	uint32_t ticks_to_wait = milliseconds * TICKS_PER_MS;
	uint32_t end_ticks = current_tick + ticks_to_wait;
	while(current_tick < end_ticks){
		asm volatile ("sti\n\t"
                      "hlt\n\t");
		current_tick = get_current_tick();
    }
};
