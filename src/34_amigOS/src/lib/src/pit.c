#include "../include/pit.h"
#include "../include/libc/stdint.h"
#include "../include/stdlib.h"

uint32_t tick = 0;

static void timer_callback(){
    tick++;
    printf("Tick: ");
    char* arg = int_to_string(tick, 0);
    printf(arg);
    printf("\n");
};


void init_pit(){
    return 0;
};

void sleep_interrupt(uint32_t milliseconds){
    /*
    start_tick = get_current_tick();
	ticks_to_wait = milliseconds * TICKS_PER_MS;
	elapsed_ticks = 0;
	while(elapsed_ticks < than ticks_to_wait){
		while (get_current_tick() = start_tick + elapsed_ticks){
            continue; // Do nothing
        }
		elapsed_ticks++;
    }
    */
};

void sleep_busy(uint32_t milliseconds){
    /*
    current_tick = get_current_tick();
	ticks_to_wait = milliseconds * TICKS_PER_MS;
	end_ticks = current_tick + ticks_to_wait;
	While (current_tick < end_ticks){
		Execute the following assembly instructions:
			i. Enable interrupts (sti)
			ii. Halt the CPU until the next interrupt (hlt)
		currrent_tick = get_current_tick();
    }
    */
};
